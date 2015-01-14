#pragma config(Sensor, dgtl9,  quadRight,      sensorQuadEncoder)
#pragma config(Sensor, dgtl11, quadLeft,       sensorQuadEncoder)
#pragma config(Motor,  port2,           left1,         tmotorVex393, openLoop)
#pragma config(Motor,  port3,           right1,        tmotorVex393, openLoop)
#pragma config(Motor,  port4,           left2,         tmotorVex393, openLoop)
#pragma config(Motor,  port5,           right2,        tmotorVex393, openLoop)
#pragma config(Motor,  port7,			lift1,		   tmotorVex393, openLoop)
#pragma config(Motor,  port8,			lift2,		   tmotorVex393, openLoop)
#pragma config(Motor,  port9, 		claw, 			 tmotorVex269, openLoop)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const float L_FACTOR = 0.35;
const int LIFT_SPEED = 96;

void setR(int speed)
{
	motor[right1] = motor[right2] = speed;
}

void setL(int speed)
{

	motor[left1] = motor[left2] = speed * L_FACTOR;
}

//Set lift speeds
void lift(int speed)
{
	motor[lift1] = motor[lift2] = speed;
}

void openClaw(int speed)
{
	motor[claw] = speed;
}


task main()
{

	while (1)
	{
		setL(vexRT[Ch3]);
		setR(vexRT[Ch2]);
		if(vexRT[Btn6U] && !vexRT[Btn6D])
		{
			lift(LIFT_SPEED);
		}
		else if(vexRT[Btn6D] && !vexRT[Btn6U])
		{
			lift(-LIFT_SPEED);
		}
		else
		{
			lift(15);
		}

		if(vexRT[Btn8U] && !vexRT[Btn8D])
		{
			openClaw(48);
		}
		else if(vexRT[Btn8D] && !vexRT[Btn8U])
		{
			openClaw(-48);
		}
		else
		{
			openClaw(1);
		}
	}

}
