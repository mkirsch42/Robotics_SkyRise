#pragma config(Sensor, dgtl1,  piston,         sensorDigitalOut)
#pragma config(Motor,  port6,           leftGear,      tmotorVex393, openLoop)
#pragma config(Motor,  port7,           rightGear,     tmotorVex393, openLoop)
#pragma config(Motor,  port8,           eleLeft,       tmotorVex393, openLoop)
#pragma config(Motor,  port9,           eleRight,      tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!



const tSensors kGyroPort = in1; // gyroscopic sensor port/name

bool doUseGyro = true; // enable gyroscopic sensor
float gyroOffset = 90.0; // degrees CCW from +x axis robot faces at gyro=0

void calibrateGyro()
{
  // completely clear out any previous sensor readings by setting the port to "sensorNone"
  SensorType[kGyroPort] = sensorNone;
  wait1Msec(1000);
  SensorType[kGyroPort] = sensorGyro; // reconfigure as sensorGyro
  wait1Msec(2000); // wait for calibration: ROBOT MUST STAY STILL

  SensorScale[kGyroPort] = 138; // adjust SensorScale to correct the scaling for your gyro
  SensorFullCount[kGyroPort] = 3599; // fix rollover to be "...3598, 3599, 0, 1..."
}

task userDriveHolo() {
  const TVexJoysticks kChTranslate = Ch1; // Translation Control
  const TVexJoysticks kChYaw = Ch4; //Rotating control
  const TVexJoysticks kChFrwrd = Ch2; //Forward Movement
  const short kDelay = 25; // milliseconds for loop delay
  const ubyte kNumWheels = 4; // number of drive wheels
  const ubyte kNumMotorsPerWheel = 2; // max number of motors per wheel
  const tMotor kNone = -1; // used for indicating the lack of an additional motor
  const tMotor kMotorPort[kNumWheels][kNumMotorsPerWheel] = { // drive motor ports/names
    {port2, kNone}, // front-left
    {port3, kNone}, // front-right
    {port4, port6}, // back-left
    {port5, port7}  // back-right
  };

  word x,y,r;
  float gyro,radius,theta,a,b,wheelSpeed[kNumWheels],topSpeed;
	int btnDown = 5;
  while(true) {
    // ==== collect joystick & sensor values ====
    x = vexRT[kChTranslate]; // x component
    y = vexRT[kChYaw]; // y component
    r = vexRT[kChFrwrd]; // rotation
    setXWheelMovement(x, y, r);

    if(vexRT[Btn6U] && !vexRT[Btn6D])
    {
    	motor[eleLeft] = 96;
    	motor[eleRight] = 96;
    }
    else if(!vexRT[Btn6U] && vexRT[Btn6D])
    {
    	motor[eleLeft] = -96;
    	motor[eleRight] = -96;
    }
    else
    {
    	motor[eleLeft] = 15;
    	motor[eleRight] = 15;
    }

    if(vexRT[Btn5D] && !vexRT[Btn5U])
    {
    	motor[rightGear] = 96;
    	motor[leftGear] = 96;
    }
    else if(!vexRT[Btn5D] && vexRT[Btn5U])
    {
    	motor[rightGear] = -96;
    	motor[leftGear] = -96;
    }
    else
    {
    	//Default Pressure
    	motor[rightGear] = -15;
    	motor[leftGear] = -15;
    }

    if(!vexRT[Btn8D] && btnDown==0)
    {
    	btnDown=5;
    	SensorValue[piston]=!SensorValue[piston];
    }
    else if(vexRT[Btn8D] && btnDown>0)
    {
    	btnDown--;
    }
    wait1Msec(kDelay);


  }
}

void pre_auton()
{
  bStopTasksBetweenModes = true;
}

task autonomous()
{
   setXWheelMovement(0, 0, 1);
   wait1Msec(1000);
   setXWheelMovement(0, 0, -1);
   wait1Msec(1000);
   setXWheelMovement(0, 0, 0);
}

void setXWheelMovement(int x, int y, int r)
{
	    gyro = gyroOffset + (doUseGyro ? SensorValue[kGyroPort]/10.0 : 0.0); // if using gyro, scale its value to degrees

    // ==== convert joystick values to polar ====
    radius = sqrt(pow(x,2) + pow(y,2)); // r = sqrt(x^2 + y^2)
    theta = atan2(y,x)*180.0/PI; // t = arctan(y/x) [converted from radians to degrees]

    theta -= gyro; // adjust for gyro angle

    // ==== calculate opposite-side speeds ====
    a = (cosDegrees(theta + 90.0) + sinDegrees(theta + 90.0))*radius; // front-left and back-right
    b = (cosDegrees(theta) + sinDegrees(theta))*radius; // front-right and back-left

    // ==== set speeds, including rotation ====
    wheelSpeed[0] = a + r; // front-left
    wheelSpeed[1] = b - r; // front-right
    wheelSpeed[2] = b + r; // back-left
    wheelSpeed[3] = a - r; // back-right

    // ==== normalize speeds ====
    topSpeed = 0.0;
    for(ubyte i=0; i<kNumWheels; i++)
      if(abs(wheelSpeed[i]) > topSpeed)
        topSpeed = abs(wheelSpeed[i]); // find highest desired speed
    if(topSpeed > 127.0)
      for(ubyte i=0; i<kNumWheels; i++)
        wheelSpeed[i] /= topSpeed/127.0; // downscale all speeds so none are above 127

    // ==== update motor powers ====
    for(ubyte i=0; i<kNumWheels; i++) // cycle through all wheels
      for(ubyte j=0; j<kNumMotorsPerWheel; j++) // cycle through all motors for each wheel
        if(kMotorPort[i][j] != kNone) // check existence of motor
          motor[kMotorPort[i][j]] = (word)wheelSpeed[i]; // update motor power
}

task usercontrol()
{
  calibrateGyro();
  StartTask(userDriveHolo);

  while(true)
    wait1Msec(100);
}
