#include <Servo.h>
#include "Drive.h"
#include "Potentiometer.h"
#include "Timer.h"
#include "HeartBeat.h"
#include "PS2X_lib.h"
#include "Controller.h"
#include "Debug.h"
#include "Elevator.h"
/*
 *  Pin map on Leonardo 
 *  in out motor- 7, up down motor - 6, right drive - 5, left drive - 4, heartbeat LED - 2, 13, 12, 11, 10,
 *  0-Serial
 *  1-Serial
 *  2-In Limit----set high by default(INPUT PULLUP)
 *  3-Out Limit -----set high by default(INPUT PULLUP)
 *  4- LeftDrive
 *  5-RightDrive
 *  6-UpDown Motor
 *  7-InOutMotor
 *  8-Up Limit------ set high by default (INPUTPULLUP)
 *  9-Down Limit---- set high by default (INPUTPULLUP)
 *  10-Controller 
 *  11-Controller 
 *  12-Controller 
 *  13-Controller 
 *  14-A0-HeartBeatLed
 *  15-A1-unused
 *  16-A2-unused
 *  17-A3-unused
 *  18-A4-unused
 *  19-A5-unused
 */
void setup() {
  Serial.begin(230400);
  ControllerSetup();
  DriveSetup();
  TimerSetup();
  HeartBeatSetup();
  ElevatorSetup();
  //PitcherSetup();
  
}

void loop() 
{
  static bool runController = true;
  static bool runRobot = false;
  
#if 0
  if (TimerCheck(){
    HeartBeatLoop();
    
  }
#else
  if (TimerCheck()) {
    if (runController) {
      ControllerLoop();
    }

    if (runRobot) {
      //Serial.println(SwitchPressed());
      if (ControllerGetL2State())
      {
        HeartBeatLoop();
        DriveWithStick();
        ElevatorDrive();
        
      }
      else
      {
        DriveStop();
      }
    }

    // Alternate between getting data from the controller and updating the robot
    
    runController = !runController;
    runRobot = !runRobot;
  }
#endif
}
