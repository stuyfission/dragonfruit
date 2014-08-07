#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Motor,  mtr_S1_C1_2,     driveL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     driveR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     slideL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     slideR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_1,     screwL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_2,     screwR,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C2_2,    boxL,                   tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    boxR,                   tServoNone)
#pragma config(Servo,  srvo_S2_C2_3,    lockL,                  tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    lockR,                  tServoNone)
#pragma config(Servo,  srvo_S2_C3_5,    auton,                  tServoNone)

#include "JoystickDriver.c"

// DEPRECATED, use teleop.c

/*
PER AUTONOMOUS
void clearEncoders () {
	nMotorEncoder[driveL] = 0;
	nMotorEncoder[driveR] = 0;
}

void driveMotors (int distance, int power) {
	clearEncoders();
	while (nMotorEncoder[driveL] < distance && nMotorEncoder[driveR] < distance) {
		motor[motorL] = power;
		motor[motorR] = power;
	}
	motor[motorL] = 0;
	motor[motorR] = 0;
}
*/



/**************************************************
 **************************************************
 ***************INSTRUCTIONS***********************
 **************************************************
 **************************************************

 -Eat ALL of Sarah

 Left and right joysticks control drive in a self-explanatory way.
 9 and 10 buttons toggle the joysticks between controlling the drivetrain and the lead screws.
 9 = drive
 10 = lead screwyness
 Joystick buttons 5 and 7 control the linear slide motors to bring the slides up and down in
 a self-explanatory way.
 5 = up
 7 = down (in a controlled sane case)
 The auton arm is controlled by buttons 1 and 4 to either erect or go flaccid.
 The box is controlled by buttons 6 and 8 but since the values that they are set to are not
 determined to be accurate, it will 100% fuck up.

 **************************************************
 **************************************************
 **************************************************
 **************************************************
 **************************************************
 */
task main () {

	//Toggles joysticks between lead screw and drivetrain control
	bool toggle = true;

	while (true) {

		getJoystickSettings(joystick);

		x1 = joystick.joy1_x1;
		y1 = joystick.joy1_y1;
		x2 = joystick.joy1_x2;
		y2 = joystick.joy1_y2;

		//Toggle controlled by buttons 9 and 10
		if (joy1Btnj(9)) {
			toggle = true;
		}
		if (joy1Btn(10)) {
			toggle = false;
		}

		//Drive control via joystick
		if (abs(x1) > 15) {
			if (toggle) {
				motor[motorL] = x1;
			}
			else {
				motor[screwL] = x1;
			}
		}
		if (abs(x2) > 15) {
			if (toggle) {
				motor[motorR] = x2;
			}
			else {
				motor[screwR] = x2;
			}
		}

		//Linear slide actuation
		if (joy1Btn(5)) {
			motor[slideL] = 100;
			motor[slideR] = 100;
		}
		else {
			motor[slideL] = 0;
			motor[slideR] = 0;
		}
		if (joy1Btn(7)) {
			motor[slideL] = -100;
			motor[slideR] = -100;
		}
		else {
			motor[slideL] = 0;
			motor[slideR] = 0;
		}

		//Auton arm
		if (joy1Btn(4)) {
			servo[auton] = 155;
		}
		if (joy1Btn(1)) {
			servo[auton] = 0;
		}
		//servos up
		//DO NOT REMEMBER THE CONSTANTS
		//CHANGE THE NUMBERS
		if (joy1Btn(6)) {
			servo[boxL] = 100;
			servo[boxR] = 200;
		}
		//servos down
		if (joy1Btn(8)) {
			servo[boxL] = 200;
			servo[boxR] = 100;
		}
	}
}
