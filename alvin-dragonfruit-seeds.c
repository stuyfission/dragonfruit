#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S2_C3_1,     leadL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_2,     leadR,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     LED,           tmotorTetrix, openLoop)
//MANUAL LINEAR SLIDE CONTROL FOR WAFFLEBOT

task main () {
	while (true) {
		eraseDisplay();
		nxtDisplayString(3, "%d", "Left-down, right-up, maybe...");
		if (nNxtButtonPressed == 2) { //down
			motor[leadL] = -100;
			motor[leadR] = -100;
		}
		else {
			motor[leadL] = 0;
			motor[leadR] = 0;
		}
		if (nNxtButtonPressed == 1) { //up
			motor[leadL] = 100;
			motor[leadR] = 100;
		}
		else {
			motor[leadL] = 0;
			motor[leadR] = 0;
		}
	}
}
