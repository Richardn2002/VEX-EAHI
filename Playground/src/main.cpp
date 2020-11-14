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
// Inertial             inertial      11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
timer Timer;
competition Competition;

void autonomous(void) {
  while(1) {
  }
}

void usercontrol(void) {
  Inertial.calibrate();
  Brain.Screen.clearLine(4, color::black);
  Brain.Screen.setCursor(4,0);
  Brain.Screen.print("Calibrating...");
  while(Inertial.isCalibrating()){
  }
  Brain.Screen.clearLine(4, color::black);

  while(1) {
    MotorFL.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    MotorBL.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    MotorFR.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    MotorBR.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);

    Brain.Screen.clearLine(1, color::black);
    Brain.Screen.clearLine(2, color::black);
    Brain.Screen.clearLine(3, color::black);
    Brain.Screen.setCursor(1,0);
    Brain.Screen.print("Roll: ", Inertial.orientation(roll, degrees));
    Brain.Screen.setCursor(2,0);
    Brain.Screen.print("Pitch: ", Inertial.orientation(pitch, degrees));
    Brain.Screen.setCursor(3,0);
    Brain.Screen.print("Yaw: ", Inertial.orientation(yaw, degrees));
    wait(100, msec);
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
