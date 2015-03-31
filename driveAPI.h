const bool doUseGyro = false; // enable gyroscopic sensor
bool isGyroCalibrated = false;
float gyroOffset = 90.0; // degrees CCW from +x axis robot faces at gyro=0

//DPI
bool isSlowActive = false; //Is slow mode active
float multiplierSlow = 0.3;
byte debounceSlow = 0; //Debouncer for it (If 0 can switch)

//XDrive Settings
const TVexJoysticks kChTranslate = Ch1; // Translation Control
const TVexJoysticks kChYaw = Ch4; //Rotating control
const TVexJoysticks kChFrwrd = Ch2; //Forward Movement
const short kDelay = 25; // milliseconds for loop delay
const ubyte kNumWheels = 4; // number of drive wheels
const ubyte kNumMotorsPerWheel = 2; // max number of motors per wheel
const tMotor kNone = -1; // used for indicating the lack of an additional motor
const tMotor kMotorPort[kNumWheels][kNumMotorsPerWheel] = { // drive motor ports/names
    {port3, kNone}, // front-left
    {port2, kNone}, // front-right
    {port4, kNone}, // back-left
    {port5, kNone}  // back-right
};
/*
const tMotor kMotorPort[kNumWheels][kNumMotorsPerWheel] = { // drive motor ports/names
    {port2, kNone}, // front-left
    {port3, kNone}, // front-right
    {port4, kNone}, // back-left
    {port5, kNone}  // back-right
};*/

void calibrateGyro()
{
	if (doUseGyro && !isGyroCalibrated) {
    writeDebugStreamLine("Gyro Calibrated");
    isGyroCalibrated = true;

    // completely clear out any previous sensor readings by setting the port to "sensorNone"
    SensorType[kGyroPort] = sensorNone;
    wait1Msec(1000);
    SensorType[kGyroPort] = sensorGyro; // reconfigure as sensorGyro
    wait1Msec(2000); // wait for calibration: ROBOT MUST STAY STILL

    SensorScale[kGyroPort] = 138; // adjust SensorScale to correct the scaling for your gyro
    SensorFullCount[kGyroPort] = 3599; // fix rollover to be "...3598, 3599, 0, 1..."
	}
}

void setXDrive(word sideways, word rotate, word forward) {
	//sideways = Left Joystick 4
	//rotate = Right Joystick 1
	//forward = Right Joystick 2
	//127^2 = 16129
  float gyro,radius,theta,wheelSpeed[kNumWheels],topSpeed;

  	gyro = gyroOffset + (doUseGyro ? SensorValue[kGyroPort]/10.0 : 0.0); // if using gyro, scale its value to degrees

    // ==== convert joystick values to polar ====
    radius = sqrt(pow(sideways,2) + pow(forward,2)); // forward = sqrt(sideways^2 + rotate^2)
    theta = atan2(forward,sideways)*180.0/PI; // t = arctan(rotate/sideways) [converted from radians to degrees]

    theta -= gyro; // adjust for gyro angle

    // ==== calculate opposite-side speeds ====
    //float a,b;
    //a = (cosDegrees(theta + 90.0) + sinDegrees(theta + 90.0))*radius; // front-left and back-right
    //b = (cosDegrees(theta) + sinDegrees(theta))*radius; // front-right and back-left

    // ==== set speeds, including rotation ====
    //wheelSpeed[0] = a + forward; // front-left
    //wheelSpeed[1] = b - forward; // front-right
    //wheelSpeed[2] = b + forward; // back-left
    //wheelSpeed[3] = a - forward; // back-right


    float x,y;
    x = radius * cosDegrees(theta);
    y = radius * sinDegrees(theta);

    // ==== set speeds, including rotation ====
    wheelSpeed[0] = x + y + rotate; // front-left
    wheelSpeed[1] = x - y - rotate; // front-right
    wheelSpeed[2] = x - y + rotate; // back-left
    wheelSpeed[3] = x + y - rotate; // back-right


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
