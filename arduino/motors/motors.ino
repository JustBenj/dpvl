#include <SPI.h>

// You will need to find these libraries
// I believe they are all bundled together
#include <A4988.h>
#include <BasicStepperDriver.h> // USE VERSION 1.0.6
#include <DRV8825.h> // This is the specific driver we are using

///////////////////////////////////////////////////////////////
//Variables
// Yaw Stepper Motor Pins
const int YDIR = 22; // Direction Pin
const int YSTEP = 23; // Step Pin
const int YENABLE = 24; // Enable Pin
const int YM0 = 25; // Mode0
const int YM1 = 26; // Mode1
const int YM2 = 27; // Mode2

// Pitch Stepper Motor Pins
const int PDIR = 32; // Direction Pin
const int PSTEP = 33; // Step Pin
const int PENABLE = 34; // Enable Pin
const int PM0 = 35; // Mode0
const int PM1 = 36; // Mode1
const int PM2 = 37; // Mode2

// Declare Stepper Motors
DRV8825 yawMotor(200, YDIR, YSTEP, YENABLE, YM0, YM1, YM2);
DRV8825 pitchMotor(200, PDIR, PSTEP, PENABLE, PM0, PM1, PM2);

// There are 200 steps in a stepper motor, each being 1.8+++++
// Microsteps = Number of steps per step (must be multiple of 2)
// 16 is usually good (32 can be overkill)
// NOTE: The higher the number, the lower the output torque, but the
//        quieter the motor
const int MICROSTEPS = 16;
const int RPM = 100;

/*
 * Possible funcstions0for stepper motors:
 * 
 * motor.setRPM(int rpm) // You need to do this one
 * motor.setMicrostep(int microsteps) // You need to do this one
 * motor.disable()
 * motor.enable()
 * motor.move(int numMicrosteps)
 * 
  */

void setup()
{
  //yawMotor.begin(RPM, MICROSTEPS);
  yawMotor.setRPM(RPM);
  yawMotor.setMicrostep(MICROSTEPS);
  yawMotor.enable();
}

void loop()
{
  yawMotor.rotate(180);
  delay(1000);
}
