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
// MotorLeftClaw        motor         5               
// MotorRightClaw       motor         6               
// MotorUp              motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
timer Timer;
competition Competition;

int32_t leftMotorPct;
int32_t rightMotorPct;
int32_t MAX_FORWARD = 80.0;
double MAX_TURN = 60.0;
double TURN_K = 0.7;
double preOrientation;
double targetOrientation;
bool isTurning = false;
bool isTurningBack = false;

void autonomous(void) {
  task::sleep(3000);
  MotorFL.spin(directionType::fwd, 50, velocityUnits::pct);MotorBL.spin(directionType::fwd, 50, velocityUnits::pct);
  MotorFR.spin(directionType::fwd, 50, velocityUnits::pct);MotorBR.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(1200);
  MotorFL.spin(directionType::fwd, 0, velocityUnits::pct);MotorBL.spin(directionType::fwd, 0, velocityUnits::pct);
  MotorFR.spin(directionType::fwd, 0, velocityUnits::pct);MotorBR.spin(directionType::fwd, 0, velocityUnits::pct);
  task::sleep(200);
  MotorFL.spin(directionType::fwd, 50, velocityUnits::pct);MotorBL.spin(directionType::fwd, 50, velocityUnits::pct);
  MotorFR.spin(directionType::fwd, -50, velocityUnits::pct);MotorBR.spin(directionType::fwd, -50, velocityUnits::pct);
  task::sleep(900);
  MotorFL.spin(directionType::fwd, 50, velocityUnits::pct);MotorBL.spin(directionType::fwd, 50, velocityUnits::pct);
  MotorFR.spin(directionType::fwd, 50, velocityUnits::pct);MotorBR.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(1400);
  MotorFL.spin(directionType::fwd, -50, velocityUnits::pct);MotorBL.spin(directionType::fwd, -50, velocityUnits::pct);
  MotorFR.spin(directionType::fwd, -50, velocityUnits::pct);MotorBR.spin(directionType::fwd, -50, velocityUnits::pct);
  task::sleep(100);
  MotorFL.spin(directionType::fwd, 0, velocityUnits::pct);MotorBL.spin(directionType::fwd, 0, velocityUnits::pct);
  MotorFR.spin(directionType::fwd, 0, velocityUnits::pct);MotorBR.spin(directionType::fwd, 0, velocityUnits::pct);
  MotorLeftClaw.spin(directionType::fwd, 100, velocityUnits::pct);
  MotorRightClaw.spin(directionType::fwd, 100, velocityUnits::pct);
  MotorUp.spin(directionType::fwd, 100, velocityUnits::pct);
  task::sleep(1500);
  MotorLeftClaw.spin(directionType::fwd, -100, velocityUnits::pct);
  MotorRightClaw.spin(directionType::fwd, -100, velocityUnits::pct);
  MotorUp.spin(directionType::fwd, -100, velocityUnits::pct);
  task::sleep(1000);
  MotorLeftClaw.spin(directionType::fwd, 100, velocityUnits::pct);
  MotorRightClaw.spin(directionType::fwd, 100, velocityUnits::pct);
  MotorUp.spin(directionType::fwd, 100, velocityUnits::pct);
  task::sleep(1500);
  MotorLeftClaw.spin(directionType::fwd, 0, velocityUnits::pct);
  MotorRightClaw.spin(directionType::fwd, 0, velocityUnits::pct);
  MotorUp.spin(directionType::fwd, 0, velocityUnits::pct);
}

void usercontrol(void) {
  while(1) {
    leftMotorPct = round(Controller1.Axis3.position(percent) * MAX_FORWARD / 100.0);
    rightMotorPct = leftMotorPct;

    if (Controller1.ButtonDown.pressing() && !isTurning) {
      preOrientation = Inertial.rotation(degrees);
      isTurning = true;
      isTurningBack = true;
    }
    if (abs(Controller1.Axis1.position(percent)) > 1 && !isTurning) {
      preOrientation = Inertial.rotation(degrees);
      isTurning = true;
    }

    if (isTurning) {
      if (isTurningBack) {
        targetOrientation = preOrientation + 180.0;
      } else {
        targetOrientation = preOrientation + Controller1.Axis1.position(percent) / 100.0 * MAX_TURN;
      }
      leftMotorPct += round((targetOrientation - Inertial.rotation(degrees)) * TURN_K);
      rightMotorPct -= round((targetOrientation - Inertial.rotation(degrees)) * TURN_K);
    }

    if (isTurningBack) {
      if (abs(targetOrientation - Inertial.rotation(degrees)) < 5.0) {
        isTurning = false;
        isTurningBack = false;
      }
    } else {
      if (abs(Controller1.Axis1.position(percent)) <= 1) {
        isTurning = false;
      }
    }

    MotorFL.spin(directionType::fwd, leftMotorPct, velocityUnits::pct);
    MotorBL.spin(directionType::fwd, leftMotorPct, velocityUnits::pct);
    MotorFR.spin(directionType::fwd, rightMotorPct, velocityUnits::pct);
    MotorBR.spin(directionType::fwd, rightMotorPct, velocityUnits::pct);

    MotorLeftClaw.spin(directionType::fwd, 0, velocityUnits::pct);
    MotorRightClaw.spin(directionType::fwd, 0, velocityUnits::pct);
    MotorUp.spin(directionType::fwd, 0, velocityUnits::pct);
    if (!(Controller1.ButtonR2.pressing() & Controller1.ButtonL2.pressing())) {
      if (Controller1.ButtonR2.pressing()) {
        MotorLeftClaw.spin(directionType::fwd, 100, velocityUnits::pct);
        MotorRightClaw.spin(directionType::fwd, 100, velocityUnits::pct);
      }
      if (Controller1.ButtonL2.pressing()) {
        MotorLeftClaw.spin(directionType::fwd, -100, velocityUnits::pct);
        MotorRightClaw.spin(directionType::fwd, -100, velocityUnits::pct);
      }
    }

    if (!(Controller1.ButtonR1.pressing() & Controller1.ButtonL1.pressing())) {
      if (Controller1.ButtonR1.pressing()) {
        MotorUp.spin(directionType::fwd, 100, velocityUnits::pct);
      }
      if (Controller1.ButtonL1.pressing()) {
        MotorUp.spin(directionType::fwd, -100, velocityUnits::pct);
      }
    }

    wait(100, msec);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Inertial.calibrate();
  Brain.Screen.clearLine(4, color::black);
  Brain.Screen.setCursor(4,0);
  Brain.Screen.print("Calibrating...");
  while(Inertial.isCalibrating()){
  }
  Brain.Screen.clearLine(4, color::black);

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  while(1) {
    wait(100, msec);
  }
}
