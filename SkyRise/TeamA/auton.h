void autonRedPole()
{
	resetDriveIme();
	driveMotors(24, 70, DRIVE_F);
}

void autonBluPole()
{
	pointTurn(90, 70, DRIVE_L);
	/*setL(-127);
	setR(-127);
	wait1Msec(750);
	setL(0);
	setR(0);
	clawControl(80);
	wait1Msec(500);
	clawControl(-40);

	wait1Msec(1000);
	clawControl(0);*/
}

void autonRedAuto()
{
	/*setL(-127);
	setR(-127);
	wait1Msec(750);
	setL(0);
	setR(0);
	clawControl(80);
	wait1Msec(500);
	clawControl(-40);

	wait1Msec(1000);
	clawControl(0);*/
}

void autonBluAuto()
{
	// SETUP
	//liftDist(7, 70, UP);
	//claw(true);
	//wait1Msec(1000);

	// GRAB SKYRISE
	claw(false);
	wait1Msec(50);
	liftDist(6, 70, UP);

	// SCORE SKYRISE
	pointTurn(90,45,DRIVE_R);
	wait1Msec(100);
	liftDist(4,60,DOWN);
	claw(true);

	// CUBE SETUP
	driveMotors(-3, 50);
	wait1Msec(100);
	pointTurn(150,50,DRIVE_R);
	wait1Msec(100);
	driveMotors(-5, 50);
	liftDist(9, 70, DOWN);
	claw(false);

	// GRAB CUBE
	driveMotors(14, 60);
	claw(true);
	liftDist(20, 70, UP);
	wait1Msec(100);
	driveMotors(-9, 60);

	// PLACE CUBE
	pointTurn(150, 50, DRIVE_L);
	driveMotors(9, 50);
	liftDist(9, 70, DOWN);

	// RELEASE CUBE
	claw(false);
	driveMotors(-9, 60);

	// FINISH
	setL(60);
	wait1Msec(2000);
	setL(0);
	claw(true);
}
