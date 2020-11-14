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

int32_t leftMotorPct;
int32_t rightMotorPct;
int32_t MAX_FORWARD = 80.0;
double MAX_TURN = 90.0;
double TURN_K = 0.7;
double preOrientation;
double targetOrientation;
bool isTurning = false;

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
    leftMotorPct = round(Controller1.Axis3.position(percent) * MAX_FORWARD / 100.0);
    rightMotorPct = leftMotorPct;

    if (abs(Controller1.Axis1.position(percent)) > 1 && !isTurning) {
      preOrientation = Inertial.rotation(degrees);
      isTurning = true;
    }
    if (isTurning) {
      targetOrientation = preOrientation + Controller1.Axis1.position(percent) / 100.0 * MAX_TURN;
      leftMotorPct += round((targetOrientation - Inertial.rotation(degrees)) * TURN_K);
      rightMotorPct -= round((targetOrientation - Inertial.rotation(degrees)) * TURN_K);
    }
    if (abs(Controller1.Axis1.position(percent)) <= 1) {
      isTurning = false;
    }

    MotorFL.spin(directionType::fwd, leftMotorPct, velocityUnits::pct);
    MotorBL.spin(directionType::fwd, leftMotorPct, velocityUnits::pct);
    MotorFR.spin(directionType::fwd, rightMotorPct, velocityUnits::pct);
    MotorBR.spin(directionType::fwd, rightMotorPct, velocityUnits::pct);
    wait(100, msec);
  }
}

void turnBack(void) {
  preOrientation = Inertial.rotation(degrees);
  targetOrientation = preOrientation + 180.0;
  while (abs(Inertial.rotation(degrees) - targetOrientation) > 5.0) {
    MotorFL.spin(directionType::fwd, round((targetOrientation - Inertial.rotation(degrees)) * TURN_K), velocityUnits::pct);
    MotorBL.spin(directionType::fwd, round((targetOrientation - Inertial.rotation(degrees)) * TURN_K), velocityUnits::pct);
    MotorFR.spin(directionType::fwd, -round((targetOrientation - Inertial.rotation(degrees)) * TURN_K), velocityUnits::pct);
    MotorBR.spin(directionType::fwd, -round((targetOrientation - Inertial.rotation(degrees)) * TURN_K), velocityUnits::pct);
    wait(100, msec);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Controller1.ButtonDown.pressed(turnBack);

  while(1) {
    wait(100, msec);
  }
}
