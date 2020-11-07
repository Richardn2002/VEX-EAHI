/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Richardn                                                  */
/*    Created:      Sat Nov 07 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Controller1          controller                    
// Motor2               motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
competition Competition;

void autonomous(void) {
  while(1) {
    Motor1.spin(directionType::fwd, 1.0f, velocityUnits::pct);
    Motor2.spin(directionType::fwd, 1.0f, velocityUnits::pct);
  }
}

void usercontrol(void) {
  while(1) {
    Motor1.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    Motor2.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  while(1) {
    wait(100, msec);
  }
}
