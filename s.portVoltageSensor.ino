// this is a really simple voltage sensor that is small and light weight for your models.
// to use it you will need to wire a voltage divider up to the A2 pin on the arduino
// for my builds I use 22K  and 2K for the divider.  This will allow a working lipo
// voltage of up to 30v with no issues.  You can of course use different values as long as
// you drive A2 at lower than 3v.  I have found any higher and the 'dfrobot beetle' boards
// dont like it.

// this code relies heavily on this up-stream s.port project
// https://github.com/RealTadango/FrSky/blob/master/examples/SimpleSensor/SimpleSensor.ino
// you will need to add his libraries to your arduoino environment for it to work.

#define SPORT_PIN 9  //digital pin 9
#define VOLTAGE_PIN A2  //analog pin a2
#define SENSOR_ID 0x5900  //unique id number for sensor

#include <SPort.h>                  //Include the SPort library

SPortHub hub(0x12, SPORT_PIN);              //Hardware ID 0x12, Software serial pin 9
SimpleSPortSensor sensor(SENSOR_ID);   //Sensor with ID 0x5900


double kalman_q= 0.05;   
double kalman_r= 150;   
float dividerRatio = 6.065;
float sensorValue;

void setup() {
  hub.registerSensor(sensor);       //Add sensor to the hub
  analogReference(INTERNAL);
  hub.begin();                      //Start listening
}

void loop() {
  
      //simple read of the values from the analog port.. and then send it to the hub.
      sensorValue =  kalman_update(analogRead(VOLTAGE_PIN));
      float voltage = sensorValue * (5.0 / 1023.0);
      sensor.value = (voltage * dividerRatio) * 100 ;      
      hub.handle();       

}

//kalman filter to 'denoise' the measurements.
float kalman_update(float measurement)
{
  //static int lcnt=0;
  static float x=sensorValue; //value
  static float p=100; //estimation error covariance
  static float k=0; //kalman gain

  // update the prediction value
  p = p + kalman_q;

  // update based on measurement
  k = p / (p + kalman_r);
  x = x + k * (measurement - x);
  p = (1 - k) * p;

  return x;
}
