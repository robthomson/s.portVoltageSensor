// this is a really simple voltage sensor that is small and light weight for your models.

//voltage divider is:

///22K
//2K


// based on this sort project & manual
//https://github.com/RealTadango/FrSky/blob/master/examples/SimpleSensor/SimpleSensor.ino
#include <SPort.h>                  //Include the SPort library

SPortHub hub(0x12, 9);              //Hardware ID 0x12, Software serial pin 3
SimpleSPortSensor sensor(0x5900);   //Sensor with ID 0x5900
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
  
      // read the input on analog pin 0:
      sensorValue =  kalman_update(analogRead(A2));
      float voltage = sensorValue * (5.0 / 1023.0);
      sensor.value = (voltage * dividerRatio) * 100 ;              //Set the sensor value
      hub.handle();                     //Handle new data

}


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
