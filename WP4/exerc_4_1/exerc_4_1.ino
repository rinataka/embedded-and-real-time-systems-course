// (C) Lina Boman, Graciela Coate Cano, Jina Dawood,
// Group: 13 (2022)
// Work package 4
// Exercise 1: INTERRUPTS ON TIMER.
// Submission code: 754-Cc
// https://www.tinkercad.com/things/gJIF4AyILgy-ex-41/editel?sharecode=F2ToBDSfwd4wRMsGfSaWvdAZ-kDtQfB5pPWHKi30d_k

#ifndef TIMERONE_h
#define TIMERONE_h

#include <avr/io.h>
#include <avr/interrupt.h>

#define RESOLUTION 65536 // Timer1 is 16 bit

class TimerOne
{
public:
  // properties
  unsigned int pwmPeriod;
  unsigned char clockSelectBits;
  char oldSREG; // To hold Status Register while ints disabled

  // methods
  void initialize(long microseconds = 1000000);
  void start();
  void stop();
  void restart();
  void resume();
  unsigned long read();
  void pwm(char pin, int duty, long microseconds = -1);
  void disablePwm(char pin);
  void attachInterrupt(void (*isr)(), long microseconds = -1);
  void detachInterrupt();
  void setPeriod(long microseconds);
  void setPwmDuty(char pin, int duty);
  void (*isrCallback)();
};

extern TimerOne Timer1;
#endif

#ifndef TIMERONE_cpp
#define TIMERONE_cpp

// #include "TimerOne.h"

TimerOne Timer1; // preinstatiate

ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  Timer1.isrCallback();
}

void TimerOne::initialize(long microseconds)
{
  TCCR1A = 0;          // clear control register A
  TCCR1B = _BV(WGM13); // set mode 8: phase and frequency correct pwm, stop the timer
  setPeriod(microseconds);
}

void TimerOne::setPeriod(long microseconds) // AR modified for atomic access
{

  long cycles = (F_CPU / 2000000) * microseconds; // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
  if (cycles < RESOLUTION)
    clockSelectBits = _BV(CS10); // no prescale, full xtal
  else if ((cycles >>= 3) < RESOLUTION)
    clockSelectBits = _BV(CS11); // prescale by /8
  else if ((cycles >>= 3) < RESOLUTION)
    clockSelectBits = _BV(CS11) | _BV(CS10); // prescale by /64
  else if ((cycles >>= 2) < RESOLUTION)
    clockSelectBits = _BV(CS12); // prescale by /256
  else if ((cycles >>= 2) < RESOLUTION)
    clockSelectBits = _BV(CS12) | _BV(CS10); // prescale by /1024
  else
    cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10); // request was out of bounds, set as maximum

  oldSREG = SREG;
  cli();                     // Disable interrupts for 16 bit register access
  ICR1 = pwmPeriod = cycles; // ICR1 is TOP in p & f correct pwm mode
  SREG = oldSREG;

  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
  TCCR1B |= clockSelectBits; // reset clock select register, and starts the clock
}

void TimerOne::setPwmDuty(char pin, int duty)
{
  unsigned long dutyCycle = pwmPeriod;

  dutyCycle *= duty;
  dutyCycle >>= 10;

  oldSREG = SREG;
  cli();
  if (pin == 1 || pin == 9)
    OCR1A = dutyCycle;
  else if (pin == 2 || pin == 10)
    OCR1B = dutyCycle;
  SREG = oldSREG;
}

void TimerOne::pwm(char pin, int duty, long microseconds) // expects duty cycle to be 10 bit (1024)
{
  if (microseconds > 0)
    setPeriod(microseconds);
  if (pin == 1 || pin == 9)
  {
    DDRB |= _BV(PORTB1);   // sets data direction register for pwm output pin
    TCCR1A |= _BV(COM1A1); // activates the output pin
  }
  else if (pin == 2 || pin == 10)
  {
    DDRB |= _BV(PORTB2);
    TCCR1A |= _BV(COM1B1);
  }
  setPwmDuty(pin, duty);
  resume(); // Lex - make sure the clock is running.  We don't want to restart the count, in case we are starting the second WGM
            // and the first one is in the middle of a cycle
}

void TimerOne::disablePwm(char pin)
{
  if (pin == 1 || pin == 9)
    TCCR1A &= ~_BV(COM1A1); // clear the bit that enables pwm on PB1
  else if (pin == 2 || pin == 10)
    TCCR1A &= ~_BV(COM1B1); // clear the bit that enables pwm on PB2
}

void TimerOne::attachInterrupt(void (*isr)(), long microseconds)
{
  if (microseconds > 0)
    setPeriod(microseconds);
  isrCallback = isr;   // register the user's callback with the real ISR
  TIMSK1 = _BV(TOIE1); // sets the timer overflow interrupt enable bit
                       // might be running with interrupts disabled (eg inside an ISR), so don't touch the global state
                       //  sei();
  resume();
}

void TimerOne::detachInterrupt()
{
  TIMSK1 &= ~_BV(TOIE1); // clears the timer overflow interrupt enable bit
                         // timer continues to count without calling the isr
}

void TimerOne::resume() // AR suggested
{
  TCCR1B |= clockSelectBits;
}

void TimerOne::restart() // Depricated - Public interface to start at zero - Lex 10/9/2011
{
  start();
}

void TimerOne::start() // AR addition, renamed by Lex to reflect it's actual role
{
  unsigned int tcnt1;

  TIMSK1 &= ~_BV(TOIE1); // AR added
  GTCCR |= _BV(PSRSYNC); // AR added - reset prescaler (NB: shared with all 16 bit timers);

  oldSREG = SREG; // AR - save status register
  cli();          // AR - Disable interrupts
  TCNT1 = 0;
  SREG = oldSREG; // AR - Restore status register
  resume();
  do
  { // Nothing -- wait until timer moved on from zero - otherwise get a phantom interrupt
    oldSREG = SREG;
    cli();
    tcnt1 = TCNT1;
    SREG = oldSREG;
  } while (tcnt1 == 0);

  //  TIFR1 = 0xff;              		// AR - Clear interrupt flags
  //  TIMSK1 = _BV(TOIE1);              // sets the timer overflow interrupt enable bit
}

void TimerOne::stop()
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12)); // clears all clock selects bits
}

unsigned long TimerOne::read() // returns the value of the timer in microseconds
{                              // rember! phase and freq correct mode counts up to then down again
  unsigned long tmp;           // AR amended to hold more than 65536 (could be nearly double this)
  unsigned int tcnt1;          // AR added

  oldSREG = SREG;
  cli();
  tmp = TCNT1;
  SREG = oldSREG;

  char scale = 0;
  switch (clockSelectBits)
  {
  case 1: // no prescalse
    scale = 0;
    break;
  case 2: // x8 prescale
    scale = 3;
    break;
  case 3: // x64
    scale = 6;
    break;
  case 4: // x256
    scale = 8;
    break;
  case 5: // x1024
    scale = 10;
    break;
  }

  do
  { // Nothing -- max delay here is ~1023 cycles.  AR modified
    oldSREG = SREG;
    cli();
    tcnt1 = TCNT1;
    SREG = oldSREG;
  } while (tcnt1 == tmp); // if the timer has not ticked yet

  // if we are counting down add the top value to how far we have counted down
  tmp = ((tcnt1 > tmp) ? (tmp) : (long)(ICR1 - tcnt1) + (long)ICR1); // AR amended to add casts and reuse previous TCNT1
  return ((tmp * 1000L) / (F_CPU / 1000L)) << scale;
}

#endif

// pins
#define RED_LED 13
#define ORANGE_LED 11
#define GREEN_LED 9
#define BLUE_LED 7
#define WHITE_LED 5
#define TEMP_PIN A0

int tempSensor = 0;   // variable to store read value from A0
double tempC = 0.0;   // variable to store calculated temp in celsius
double voltage = 0.0; // variable to store calculated voltage

// initializing variables with different temperatures
int const minusTen = -10;

int const zero = 0;

int const ten = 10;

int const twenty = 20;

int const thirty = 30;

int const fourty = 40;

void setup()
{
  // Open the serial port at 9600 bps (bits per second),
  // To use Serial.println()
  Serial.begin(9600);

  // Configure temp pin to input
  pinMode(TEMP_PIN, INPUT);
  // Configure led pins to output
  pinMode(RED_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  Timer1.initialize(100000);                 // Initialize timer with 1 second period
  Timer1.attachInterrupt(check_temperature); // attaches check_temperature() as a timer overflow interrupt
}

void loop()
{
  turn_led(); // calling function to turn on leds based on temperature
  delay(500); // Wait for 500 millisecond(s)
}

void turn_led()
{
  // when temperature is -10 - 0
  if (tempC >= minusTen && tempC <= zero)
  {
    digitalWrite(WHITE_LED, HIGH); // first white led will turn on and the rest will turn off
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > zero && tempC <= ten)
  {
    // when temperature is 1-10
    digitalWrite(WHITE_LED, HIGH); // white led will turn on
    digitalWrite(BLUE_LED, HIGH);  // blue led will turn on and the rest will turn off
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > ten && tempC <= twenty)
  {
    // when temperature is 11-20
    digitalWrite(WHITE_LED, HIGH); // white led will turn on
    digitalWrite(BLUE_LED, HIGH);  // blue led will turn on
    digitalWrite(GREEN_LED, HIGH); // green led will turn on and the rest will turn off
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > twenty && tempC <= thirty)
  {
    // when temperature is 21 - 30
    digitalWrite(WHITE_LED, HIGH);  // white led will turn on
    digitalWrite(BLUE_LED, HIGH);   // blue led will turn on
    digitalWrite(GREEN_LED, HIGH);  // green led will turn on
    digitalWrite(ORANGE_LED, HIGH); // orange led will turn on and the rest will turn off
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > thirty && tempC <= fourty)
  {
    // when temperature is 31 - 40
    // all lights will turn on 
    digitalWrite(WHITE_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(ORANGE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  }
  else
  {
    // when temperature is outside range which is -10 - 40
    // all light will be turned off
    digitalWrite(RED_LED, LOW);
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(WHITE_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
}

void check_temperature()
{
  // read temp sensor value
  tempSensor = analogRead(TEMP_PIN);
  // calculate voltage
  voltage = tempSensor * (5019.5 / 1024.0); // 5000 to get millivots.
                                            // convert millivolts into temperature
  tempC = (voltage - 500.0) / 10.0;         // 500 is the offset
  // print out the temperature
  Serial.print(tempC);
  Serial.println(" degrees in C");
}