void autonRedPole()
{
	setL(-127);
	setR(-127);
	wait1Msec(750);
	setL(0);
	setR(0);
	clawControl(80);
	wait1Msec(500);
	clawControl(-40);

	wait1Msec(1000);
	clawControl(0);
}

void autonBluPole()
{
	setL(-127);
	setR(-127);
	wait1Msec(750);
	setL(0);
	setR(0);
	clawControl(80);
	wait1Msec(500);
	clawControl(-40);

	wait1Msec(1000);
	clawControl(0);
}

void autonRedAuto()
{
	setL(-127);
	setR(-127);
	wait1Msec(750);
	setL(0);
	setR(0);
	clawControl(80);
	wait1Msec(500);
	clawControl(-40);

	wait1Msec(1000);
	clawControl(0);
}

void autonBluAuto()
{
	setL(-127);
	setR(-127);
	wait1Msec(750);
	setL(0);
	setR(0);
	clawControl(80);
	wait1Msec(500);
	clawControl(-40);
	wait1Msec(1000);
	clawControl(0);
}
