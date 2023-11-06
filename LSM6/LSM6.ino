#include <Wire.h>
#include <LSM6.h>

LSM6 imu;

const int bufferSize = 18; 
float bufferX[bufferSize];
float bufferY[bufferSize];
float bufferZ[bufferSize];
int index = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!imu.init()) {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }

  imu.enableDefault();

  for (int i = 0; i < bufferSize; i++) {
    bufferX[i] = 0.0;
    bufferY[i] = 0.0;
    bufferZ[i] = 0.0;
  }
}

void loop() {
  imu.read();


  float mappedValueX = mapFloat(imu.a.x, -2000, 2000, -1.0, 1.0);
  float mappedValueY = mapFloat(imu.a.y, -2000, 2000, -1.0, 1.0);
  float mappedValueZ = mapFloat(imu.a.z, -2000, 2000, -1.0, 1.0);

  
  bufferX[index] = mappedValueX;
  bufferY[index] = mappedValueY;
  bufferZ[index] = mappedValueZ;

  float avgX = 0.0;
  float avgY = 0.0;
  float avgZ = 0.0;

  for (int i = 0; i < bufferSize; i++) {
    avgX += bufferX[i];
    avgY += bufferY[i];
    avgZ += bufferZ[i];
  }

  avgX /= bufferSize;
  avgY /= bufferSize;
  avgZ /= bufferSize;

  index = (index + 1) % bufferSize;  


  Serial.print(avgX, 4); 
 Serial.print("\t");  
 Serial.print(avgY, 4); 
 Serial.print("\t");  
 Serial.println(avgZ, 4);  

  delay(10);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
