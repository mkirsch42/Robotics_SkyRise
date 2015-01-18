const int LIFT_SPEED = 96;
const bool UP = 1;
const bool DOWN = 0;
const float LIFT_IN_PER_ROT = 7.25;

const float AUTON_DRIVE_CORRECT = 12.0/13.0;

const float IME_S_TICKS = 392;
const float IME_T_TICKS = 627.2;
const float WHEEL_CIRCUMFERENCE = 4.0 * PI;
const float tickPerIn = (1.0/WHEEL_CIRCUMFERENCE)*IME_S_TICKS;
const float WHEEL_BASE = 14;

const int DRIVE_F = 0;
const int DRIVE_L =	1;
const int DRIVE_R	= 2;

int getDriveIme()
{
	return (abs(SensorValue(ime_left)) + abs(SensorValue(ime_right))) / 2;
}

void resetDriveIme()
{
	SensorValue[ime_left] = 0;
	SensorValue[ime_right] = 0;
}

void setR(int speed)
{
	motor[right1] = motor[right2] = speed*0.91;
}

void setL(int speed)
{
	motor[left1] = motor[left2] = speed;
}

void fwd(int speed)
{
	setL(speed);
	setR(speed);
}

void lift(int speed, bool up = true)
{
	motor[lift1] = motor[lift2] = motor[lift3] = motor[lift4] = speed * (up?1:-1);
}

void driveMotors( float dist, int speed = 70, int drive = DRIVE_F )
{
		dist *= tickPerIn;
		dist *= AUTON_DRIVE_CORRECT;

    // Drive motor until encoder has moved a number counts or
    // timeout_in_seconds seconds have passed

    // Zero the encoder
    resetDriveIme();

    // Run the motor forwards or backwards
    if ( dist > 0 )
    {
    	if (drive == DRIVE_F || drive == DRIVE_L)
      	{setL(speed);}
      if (drive == DRIVE_F || drive == DRIVE_R)
      	{setR(speed);}
    }
    else
    {
      if (drive == DRIVE_F || drive == DRIVE_L)
      	{setL(-speed);}
      if (drive == DRIVE_F || drive == DRIVE_R)
      	{setR(-speed);}
    }

    // run loop until encoder hits encoder_count counts or timeout reached

    while(abs(getDriveIme())<abs(dist)){}

    // Stop the motor
    fwd(-64); // Prevent coasting
    wait1Msec(25);
    fwd(0);
}

void turn(float deg, int speed, int dir)
{
	float dist = (WHEEL_BASE * PI) * (deg / 360);
	driveMotors(dist==DRIVE_L?DRIVE_R:DRIVE_L, speed, dir);
}

void pointTurn(float deg, int speed, int dir)
{
	resetDriveIme();
	float dist = ((WHEEL_BASE * PI) * (deg / 360)) * tickPerIn * AUTON_DRIVE_CORRECT;
	if (dir == DRIVE_L ^ deg<0)
	{
		speed *= -1;
	}
	setL(speed);
	setR(-speed);
	while(abs(getDriveIme())<abs(dist)){}
	// Stop the motor
  setL(dir == DRIVE_L ^ deg<0?32:-32);
  setR(dir == DRIVE_L ^ deg<0?-32:32);
  wait1Msec(100);
  fwd(0);
}

void liftDist(float dist, int speed, bool up)
{
	SensorValue[ime_lift] = 0;
	dist /= LIFT_IN_PER_ROT;
	dist *= IME_T_TICKS;
	lift(speed, up);
	while(abs(SensorValue[ime_lift])<abs(dist)){}
	lift(10, true);
}

void claw(bool open)
{
	SensorValue[piston] = !open;
}


const int driveMotors_ = 0;
const int turn_ = 1;
const int pointTurn_ = 2;
const int liftDist_ = 3;

int RUN_;
float DIST_;
int SPEED_;
int DIR_;
bool isThreadDone;

task runThread()
{
	isThreadDone=false;
	switch(RUN_)
	{
		case driveMotors_:
			driveMotors(DIST_, SPEED_, DIR_);
			break;
		case turn_:
			turn(DIST_, SPEED_, DIR_);
			break;
		case pointTurn_:
			pointTurn(DIST_, SPEED_, DIR_);
			break;
		case liftDist_:
			liftDist(DIST_, SPEED_, DIR_);
			break;
	}
	isThreadDone=true;
}

void driveInThread(int run, float dist, int speed, int dir)
{
	RUN_ = run;
	DIST_ = dist;
	SPEED_ = speed;
	DIR_ = dir;
	StartTask(runThread);
}
