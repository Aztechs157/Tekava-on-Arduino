  /*=======================================================================================
Original code by:                        Noah Stahl
                                          5/7/2011
                                       Arduino Mega 2560
Modified by: WCarr 2017-05-25  -  Convert to Uno, make interrupt fire every 10ms.

=======================================================================================*/
#include <Arduino.h>

volatile bool fired;               //indicates if timer fired, and whether its been checked

#if defined(__AVR_ATmega32U4__)
/*
The timer overflow interrupt fires every 10ms by setting the prescaler to 128 and
loading Timer4's compare C with 625. Timer4 is 10-bits so the max number it can count to
is 1023. The Leonardo has a clock of 16MHz so:
(1/16E6) * 625 * 128 = 5.0 ms (Note that we want 10ms, however, reading the data sheet and
searching the web left no good explanation as to why we are off by a factor of 2.  The code
actually generates a 10ms interrupt.  Go figure.) 
*/
#define TOP_COUNT 625
#define TOP_COUNT_H ((TOP_COUNT >> 8) & 0b00000011)
#define TOP_COUNT_L (TOP_COUNT & 0xFF)
//Timer4 Overflow Interrupt Vector, called when timer overflows or matches OCR4C
ISR(TIMER4_OVF_vect) {
  fired = true;
  TC4H = TOP_COUNT_H;
  OCR4C = TOP_COUNT_L;
  TIFR4 = 0x00;         //Timer INT Flag Reg: Clear Timer Overflow Flag
}; 

void TimerSetup(void) {
  //Setup Timer4 to fire
  TCCR4B = 0x00;        //Disbale Timer while we set it up
  TC4H = 0;
  TCNT4 = 0;
  TC4H = TOP_COUNT_H;
  OCR4C = TOP_COUNT_L;
  TIFR4  = 0x00;        //Timer INT Flag Reg: Clear Timer Overflow Flag
  TIMSK4 = (1 << TOIE4);//Timer INT Reg: Timer4 Overflow Interrupt Enable
  TCCR4A = 0x00;        //Timer Control Reg A: Wave Gen Mode normal
  TCCR4B = 0b1000;      //Timer Control Reg B: Timer Prescaler set to 128
  fired = false;
}
#else /* assume it supports TIMER2 */
/*
The timer overflow interrupt fires every 10ms by setting the prescaler to 1024 and
preloading Timer2's counter with 99. Timer2 is 8-bits so the max number it can count to
is 255, this leaves 156 cycles left to count. The Arduino has a clock of 16MHz so:
(1/16E6) * 156 * 1024 = 9.984 ms (approx 10ms) 
*/
#define START_COUNT 99
//Timer2 Overflow Interrupt Vector, called when timer overflows (exceeds 255)
ISR(TIMER2_OVF_vect) {
  fired = true;
  TCNT2 = START_COUNT;   //Reset Timer
  TIFR2 = 0x00;          //Timer2 INT Flag Reg: Clear Timer Overflow Flag
}; 

void TimerSetup(void) {
  //Setup Timer2 to fire
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2 = START_COUNT;  //Reset Timer
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x07;        //Timer2 Control Reg B: Timer Prescaler set to 1024

  fired = false;
}
#endif  

void TimerLoop(void) {
}

bool TimerCheck(void)  {
  uint8_t old_sreg = SREG;        // **** save away the current state of interrupts
  bool prevFired;

  // turn off inteerupts so the state of fired doesn't chnage to avaoid conflict at timer reset
  noInterrupts();
  prevFired = fired;
  fired = false;
  SREG = old_sreg;  // return interrupts to previous state 
  return prevFired;
}

