#include <Arduino.h>
#include <Servo.h>
#include "PS2X_lib.h"
#include "Potentiometer.h"
#include "Drive.h"
#include "Controller.h"
#include "Heartbeat.h"
int UpDownPin = 6; //motor on pin 6
int OpenClosePin = 7; //motor on pin 7
/*int SwitchPin = 3;*/
Servo UpDown;
Servo OpenClose;
#define NUMBERLIMITSWITCHES 4
#define LIMITSWITCHUP 0
#define LIMITSWITCHDOWN 1
#define LIMITSWITCHIN 2
#define LIMITSWITCHOUT 3
unsigned int[NUMBERLIMITSWITCHES] limitPins= {999, 999, 999, 999};
/*
 * HIGH: pressed
 * LOW: unpressed
 */
void ElevatorSetup(void)
{
  for (int i = 0; i < NUMBERLIMITSWITCHES; i++)
  {
    pinMode(limitPins[i], INPUT_PULLUP)
  }
  UpDown.attach(UpDownPin);
  OpenClose.attach(OpenClosePin);
  /*pinMode(SwitchPin,INPUT_PULLUP);*/
 
}
bool SwitchPressed (void)
{
  int limitSwitch = digitalRead(LimitPin);
  return limitSwitch == HIGH ? true : false;
}
void ElevatorUp (void)
{
  UpDown.write(68);
}

void ElevatorDown (void)
{
  UpDown.write(122);
}

void ElevatorOpen (void)
{
  OpenClose.write(68);
}

void ElevatorClose (void)
{
  OpenClose.write(122);
}

void ElevatorStop (void)
{
  UpDown.write(93);
  OpenClose.write(93);
}
void ElevatorDrive(void)
{
  if (ControllerGetL1State())
  {
    ElevatorClose();
  }
  else if(ControllerGetR1State())
  {
    ElevatorOpen();
  }
  else
  {
    ElevatorStop();
  }
}
