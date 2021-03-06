#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S1_C1_1,     driveR,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     driveL,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     slideR,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     slideL,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     motorH,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     LED,           tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C3_1,     screwL,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C3_2,     screwR,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    boxR,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    boxL,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    lockL,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    lockR,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    auton,                tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//motorH is unused, empty port

#include "JoystickDriver.c"

// DEPRECATED, use teleop.c

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

		//Unimplemented
		int x1 = joystick.joy1_x1;
		int x2 = joystick.joy1_x2;

		//Implemented
		int y1 = joystick.joy1_y1;
		int y2 = joystick.joy1_y2;

		//Drive and screw toggle
		//LEDs indicate lift mode
		if (joy1Btn(9)) {
			toggle = true;
			motor[LED] = 0;
		}
		if (joy1Btn(10)) {
			toggle = false;
			motor[LED] = 100;
		}

		//Drive control via joystick
		if (abs(y1) > 15) {
			if (toggle) {
				motor[driveL] = y1;
			}
			else {
				motor[screwL] = y1;
			}
		}
		else {
		  motor[driveL] = 0;
		  motor[screwL] = 0;
		}
		if (abs(y2) > 15) {
			if (toggle) {
				motor[driveR] = y2;
			}
			else {
				motor[screwR] = y2;
			}
		}
		else {
		  motor[driveR] = 0;
		  motor[screwR] = 0;
		}

		//Linear slide actuation
		//Do not do if 5 go else stop
		//          if 7 go else stop
	  //stop with be called along with go and cancel action
		if (joy1Btn(6)) {
			motor[slideL] = 100;
			motor[slideR] = -100;
		}
		else if (joy1Btn(8)) {
			motor[slideL] = -100;
			motor[slideR] = 100;
		}
		else {
			motor[slideL] = 0;
			motor[slideR] = 0;
		}

		//Auton arm
		if (joy1Btn(1)) {
			servo[auton] = 25;
		}
		if (joy1Btn(4)) {
			servo[auton] = 155;
		}
		if (joy1Btn(3)) {
		  servo[auton] = 235;
		}

		//Servos up
		if (joy1Btn(5)) {
			servo[boxL] = 155;
			servo[boxR] = 15;
		}
		//Servos down
		if (joy1Btn(7)) {
			servo[boxL] = 0;
			servo[boxR] = 255;
		}

		//Release lift arms
		if (joy1Btn(2) && (servo[auton] > 130 && servo[auton] < 180)) {
		  servo[lockL] = 255;
		  servo[lockR] = 0;
		}
		else {
		  servo[lockL] = 110;
		  servo[lockR] = 145;
		}
	}
}
