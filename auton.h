const int BLU_AUTO=0;
const int RED_AUTO=1;
const int BLU_POLE=2;
const int RED_POLE=3;
int Program=0;

void autonRedPole()
{

	motor[release]=127;
	wait1Msec(500);
	motor[release]=0;
	claw(false);

	// Drop claw
	driveMotors(20, 70);
	liftDist(10, 90, UP);
	claw(true);
	driveMotors(-20, 70);
	liftDist(23, 90, UP);
	pointTurn(135, 60, Program==RED_POLE?DRIVE_L:DRIVE_R);
	liftDist(-10, 70, UP);
	driveMotors(-10, 90);
	pointTurn(180, 90, DRIVE_L);

}

void autonBluPole()
{
	autonRedPole();
}

void autonRedAuto()
{
	// SETUP
	//driveInThread(driveMotors_, -.75, 80, DRIVE_F);
	motor[release]=127;
	claw(true);
	liftDist(5.5, 127, UP);
	//while(!isThreadDone){}
	wait1Msec(250);
	motor[release]=0;
	//driveMotors(1, 98);

	// GRAB SKYRISE
	claw(false);
	//driveInThread(driveMotors_, -1, 65, DRIVE_F);
	wait1Msec(100);
	liftDist(10, 127, UP);
	wait1Msec(100);
	//while(!isThreadDone){}

	// SCORE SKYRISE
	driveInThread(pointTurn_, 85, 75, Program?DRIVE_L:DRIVE_R);
	wait1Msec(1000);
	liftDist(11,65,DOWN);
	while(!isThreadDone){}
	driveMotors(-2,98);
	//driveMotors(-1, 60);
	claw(true);
	driveMotors(2,98);
	wait1Msec(100);

	// RESET
	driveInThread(liftDist_, 13, 127, UP);
	pointTurn(85, 45, Program?DRIVE_R:DRIVE_L);
	while(!isThreadDone){}
	wait1Msec(100);
	//driveMotors(1, 60, DRIVE_F);
	driveMotors(-2, 60);
	liftDist(10, 90, DOWN);
	driveMotors(2, 60);
	wait1Msec(100);

	// GRAB SKYRISE
	claw(false);
	wait1Msec(100);
	liftDist(11, 90, UP);
	wait1Msec(100);

	// SCORE SKYRISE
	pointTurn(85,55,Program?DRIVE_L:DRIVE_R);
	wait1Msec(100);
	claw(true);

	// FINISH
	liftDist(3, 127, UP);
	pointTurn(90, 127, Program?DRIVE_R:DRIVE_L);
	wait1Msec(500);
	driveInThread(liftDist_, 8, 127, DOWN);
}

void autonBluAuto()
{
	autonRedAuto();
}
