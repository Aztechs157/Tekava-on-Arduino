#ifndef CONTROLLER_H
#define CONTROLLER_H

void ControllerSetup(void);
void ControllerLoop(void);
byte ControllerGetRY(void);
byte ControllerGetLY(void);
bool ControllerGetCircle(void);
bool ControllerGetCircleReleased(void);
bool ControllerGetTriangle(void);
bool ControllerGetL1State(void);
bool ControllerGetL2(void);
bool ControllerGetL2State(void);
bool ControllerGetL3State(void);
bool ControllerGetR1State(void);
bool ControllerGetR2(void);
bool ControllerGetR2Released(void);
bool ControllerGetX(void);
bool ControllerConnected(void);
bool ControllerGetDebugState(void);
#endif /* CONTROLLER_H */

