const int BLU_AUTO=0;
const int RED_AUTO=1;
const int BLU_POLE=2;
const int RED_POLE=3;
int Program=0;

void autonRedPole()
{

}

void autonBluPole()
{

}

void autonRedAuto()
{
	// SETUP
	liftDist(7, 90, UP);
	claw(true);
	motor[release]=127;
	wait1Msec(500);
	motor[release]=0;

	// GRAB SKYRISE
	claw(false);
	wait1Msec(100);
	liftDist(7.5, 90, UP);
	wait1Msec(100);

	// SCORE SKYRISE
	driveInThread(pointTurn_, 85, 50, Program?DRIVE_R:DRIVE_L);
	wait1Msec(1000);
	liftDist(9,90,DOWN);
	while(!isThreadDone){}
	driveMotors(-1, 60);
	claw(true);
	wait1Msec(100);

	// RESET
	driveInThread(liftDist_, 14, 127, UP);
	pointTurn(82.5, 45, Program?DRIVE_L:DRIVE_R);
	while(!isThreadDone){}
	wait1Msec(100);
	liftDist(14, 90, DOWN);
	wait1Msec(100);
	driveMotors(1.5, 60);

	// GRAB SKYRISE
	claw(false);
	wait1Msec(100);
	liftDist(7.5, 90, UP);
	wait1Msec(100);

	// SCORE SKYRISE
	pointTurn(85,45,Program?DRIVE_R:DRIVE_L);
	wait1Msec(100);
	claw(true);

	// FINISH
	liftDist(3, 127, UP);
	pointTurn(90, 127, Program?DRIVE_L:DRIVE_R);
	wait1Msec(500);
	driveInThread(liftDist_, 8, 127, DOWN);
}

void autonBluAuto()
{
	autonRedAuto();
}
