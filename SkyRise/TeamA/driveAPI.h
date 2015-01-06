const int CLAW_OPEN = 140;
const int LIFT_HIGH = 3050;
const int LIFT_LOW = 5;
const int LIFT_SPEED = 96;
const bool UP = 1;
const bool DOWN = 0;
const double IME_S_TICKS = 392;
const double IME_T_TICKS = 627.2;

void setR(int speed)
{
	motor[right1] = motor[right2] = speed;
}

void setL(int speed)
{
	motor[left1] = motor[left2] = speed;
}

void lift(int speed, bool up = true)
{
	motor[lift1] = motor[lift2] = motor[lift3] = motor[lift4] = speed * (up?1:-1);
}

void lift(bool dir)
{
	if (dir)
	{
		while (SensorValue[ime_lift] <= LIFT_HIGH)
		{
			motor[lift1] = motor[lift2] = motor[lift3] = motor[lift4] = LIFT_SPEED;
		}
		motor[lift1] = motor[lift2] = motor[lift3] = motor[lift4] = 3;
		return;
		//SensorValue[ime_lift] = LIFT_HIGH;
	}
	else
	{
		while (SensorValue[ime_lift] >= LIFT_LOW)
		{
			motor[lift1] = motor[lift2] = motor[lift3] = motor[lift4] = -LIFT_SPEED;
		}
		motor[lift1] = motor[lift2] = motor[lift3] = motor[lift4] = 3;
		SensorValue[ime_lift] = 0;
		return;
	}

}

void clawControl(int speed)
{
	motor[claw] = speed;
}

int getEncoder()
{
	return (nMotorEncoder[right2]+nMotorEncoder[left2])/2;
}

void fwd(int inches)
{
	nMotorEncoder[right2] = nMotorEncoder[left2] = 0;
	setL(127);
	setR(127);
	while(getEncoder()<(inches / (4*3.14))*IME_S_TICKS){}
	setL(0);
	setR(0);
}
