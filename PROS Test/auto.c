/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
int target;
int motor_output;
float error;
float kP = 0.7;
float kI = 0.1; //add a value;
float kD = 1.1;
float integral;
float derivitive;
float prevError;
void drivePID(){
  {

    while(true)
    {
      error = target - encoderGet(encoder);
      integral = integral + error;
      if((error = 0) || (error > target))
       {
         integral = 0;
       }
       else if (error >10000)
         {
           integral = 0;
         }
     derivitive = error - prevError;
     prevError = error;
      motor_output = error * kP + integral * kI + derivitive * kD;
      wait(15);
   }
  }
}
void BasicMove(float target)
{
  encoderReset(encoder);
  while(encoderGet(encoder) < target)
  {
    // left drive
    motorSet(9,motor_output);
    motorSet(8,motor_output);

    // right drive
    motorSet(2,motor_output);
    motorSet(3,motor_output);
  }
  // left drive
  motorSet(9,0);
  motorSet(8,0);

  // right drive
  motorSet(2,0);
  motorSet(3,0);
}
/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
  TaskHandle PID = taskRunLoop(drivePID, 50);
  BasicMove(50);
  taskDelete(PID);
}
