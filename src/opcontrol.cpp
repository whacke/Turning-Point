#include "main.h"

//Motor section begins
Motor intake = 2_mtr;
Motor puncher = 1_mtr;
Motor angler = 4_mtr;
Motor scraper = 6_rmtr;

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
//Button section begins
ControllerButton intakeInButton(ControllerDigital::L2);
ControllerButton puncherDoubleButton(ControllerDigital::L1);
ControllerButton puncherUp(ControllerDigital::R1);
ControllerButton puncherDown(ControllerDigital::R2);
ControllerButton intakeOutButton(ControllerDigital::B);
ControllerButton scraperButton(ControllerDigital::A);
ControllerButton xToDoubt(ControllerDigital::X);


//globals
bool ballIntake, ballPuncher;
const int intakeThresh = 2350;
const int puncherThresh = 1700;
//end globals

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 auto drive = ChassisControllerFactory::create(
   {9, 10}, {7, 8},
   AbstractMotor::gearset::green,
   {4.125_in, 13.75_in}
 );


void opcontrol() {
	Controller controller;
  bool rollBack = false;
  angler.tarePosition();
  scraper.tarePosition();
  gearingChanges();
  bool scraperSelect = true;
while(true)
{
scraperBrakeHold();
printf("Puncher val at: %d ", puncherSense.get_value());
printf("Intake val at: %d \n", intakeSense.get_value());


	drive.arcade(controller.getAnalog(ControllerAnalog::rightX),
  controller.getAnalog(ControllerAnalog::leftY));

  if (intakeInButton.isPressed()) {
              intakeBrakeHold();
              if((puncherSense.get_value() < puncherThresh) && (intakeSense.get_value() < intakeThresh))
              {
                  rollBack = true;
                  intake.moveVelocity(0);
              }
              else
              {
                  while(rollBack == true)
                  {
                     intake.moveRelative(-200, 300);
                      /*intake.moveVelocity(-600);
                      pros::delay(100);
                      intake.moveVelocity(0); */
                      rollBack = false;
                      pros::delay(20);
                  }
                  intake.moveVelocity(600);
              }
          }
          else if(intakeOutButton.isPressed())
           {
             intake.moveVelocity(-400);
           }
           else
           {
               intake.moveVelocity(0);
           }
  if(puncherUp.isPressed())
          {
            //angler.moveVoltage(-200);

      if(angler.getPosition() < 299)
          {
              angler.moveAbsolute(730, 600);
              pros::delay(100);
              puncher.moveVelocity(-200);
              pros::delay(300);
              puncher.moveVelocity(0);
          }
      else
              {
                puncher.moveVelocity(-200);
                pros::delay(300);
                puncher.moveVelocity(0);
              }
          }
   else if(puncherDown.isPressed())
      {
          //  angler.moveVelocity(200);

        if(angler.getPosition() > 300)
          {
              angler.moveAbsolute(0, 600);
              pros::delay(100);
              puncher.moveVelocity(-200);
              pros::delay(300);
              puncher.moveVelocity(0);
          }
        else
          {
                  //Puncher.spin(vex::directionType::fwd,200,vex::velocityUnits::pct);
                  puncher.moveVelocity(-200);
                  pros::delay(300);
                  puncher.moveVelocity(0);
          }
      }
      if(puncherDoubleButton.isPressed())
     {
            /*LeftFront.setStopping(vex::brakeType::hold);
            LeftBack.setStopping(vex::brakeType::hold);
            RightFront.setStopping(vex::brakeType::hold);
            RightBack.setStopping(vex::brakeType::hold);*/
        //puncher.moveRelative(-175, 200);
        puncher.moveVelocity(-200);
        pros::delay(300);
        puncher.moveVelocity(0);
        intake.moveVelocity(600);
        puncher.moveVelocity(-200);
        if(angler.getPosition() < 299 && puncherDoubleButton.isPressed())
          {
            angler.moveAbsolute(730, 600);

          }
          else if(angler.getPosition() > 300 && puncherDoubleButton.isPressed())
          {
             angler.moveAbsolute(0, 600);
          }
              pros::delay(500);
              puncher.moveVelocity(0);
     }
     else if(puncherSwitch.isPressed())
     {
         puncher.moveVelocity(0);
     }
        else
      {
      puncher.moveVelocity(-200);
      }

      if(scraperButton.isPressed())
      {
        if(scraperSelect == true)
        {
        scraper.moveAbsolute(400, 200);
        pros::delay(500);
        scraperSelect = false;
        }
        else if(scraperSelect == false)
        {
          scraper.moveAbsolute(0, 200);
          pros::delay(500);
          scraperSelect = true;
        }
      }
      else
      {
        scraper.moveVelocity(0);
      }

pros::Task::delay(10);
	}
}
