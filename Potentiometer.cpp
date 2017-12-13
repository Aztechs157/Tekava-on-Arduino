#include <Arduino.h>

int PotPin= A0;
int PotVal;
int DPotVal;
int PotLoop()
{
  PotVal = analogRead(PotPin);
  DPotVal = map(PotVal, 0, 1023, 0, 180);
  Serial.print("Pot value = ");
  Serial.print(PotVal);
  Serial.print("Digital pot value = ");
  Serial.println(DPotVal);
  // input value , scale to zeroe , negate and resccale. f(x)= (-(x-90))+90 or f(x)= 180-x
  return DPotVal;
}


