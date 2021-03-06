using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MotorFL;
extern controller Controller1;
extern motor MotorBL;
extern motor MotorFR;
extern motor MotorBR;
extern inertial Inertial;
extern motor MotorLeftClaw;
extern motor MotorRightClaw;
extern motor MotorUp;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );