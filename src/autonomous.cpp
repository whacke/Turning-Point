#include "main.h"
/*
Motor intake = 2_mtr;
Motor puncher = 1_mtr;
Motor angler = 4_mtr;
Motor scraper = 6_rmtr;
*/
Motor leftFront = 9_mtr;
Motor leftBack = 10_mtr;
Motor rightFront = 7_mtr;
Motor rightBack = 8_mtr;

/*
void gearingChanges() {
intake.setGearing(AbstractMotor::gearset::blue);
angler.setGearing(AbstractMotor::gearset::blue);
puncher.setGearing(AbstractMotor::gearset::green);
scraper.setGearing(AbstractMotor::gearset::green);
}

void intakeBrakeHold(){
  intake.setBrakeMode(AbstractMotor::brakeMode::brake);
}
void scraperBrakeHold(){
  scraper.setBrakeMode(AbstractMotor::brakeMode::brake);
}
//Motor section ends
//Section sensor begins
pros::ADILineSensor intakeSense('G');
pros::ADILineSensor puncherSense('F');
ADIButton puncherSwitch('B');

//globals
bool ballIntake, ballPuncher;
const int intakeThresh = 2350;
const int puncherThresh = 1700;
//end globals
*/
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 auto autonDrive = ChassisControllerFactory::create(
   {leftFront, leftBack}, {rightFront, rightBack},
   AbstractMotor::gearset::green,
   {4.125_in, 13.75_in}
 );

 auto profileController = AsyncControllerFactory::motionProfile(
   1.0,  // Maximum linear velocity of the Chassis in m/s
   2.0,  // Maximum linear acceleration of the Chassis in m/s/s
   10.0, // Maximum linear jerk of the Chassis in m/s/s/s
   autonDrive // Chassis Controller
 );


void autonomous() {

  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 0_deg}}, "A");
  pros::delay(500);
  profileController.setTarget("A");
  profileController.waitUntilSettled();




}
