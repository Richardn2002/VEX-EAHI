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
// MotorFL              motor         1               
// Controller1          controller                    
// MotorBL              motor         2               
// MotorFR              motor         3               
// MotorBR              motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
competition Competition;

void autonomous(void) {
  while(1) {
  }
}

void usercontrol(void) {
  while(1) {
    MotorFL.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    MotorBL.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    MotorFR.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    MotorBR.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
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
