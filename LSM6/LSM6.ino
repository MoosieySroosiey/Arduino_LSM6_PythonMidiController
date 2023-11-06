#include <Wire.h>
#include <LSM6.h>

LSM6 imu;

const int bufferSize = 10;
float bufferX[bufferSize];
float bufferY[bufferSize];
float bufferZ[bufferSize];
float bufferGX[bufferSize];
float bufferGY[bufferSize];
float bufferGZ[bufferSize];
int index = 0;

const bool debug = false;

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
    bufferGX[i] = 0.0;
    bufferGY[i] = 0.0;
    bufferGZ[i] = 0.0;
  }
}

void loop() {
  imu.read();

  bufferX[index] = mapFloat(imu.a.x, -32768, 32767, -2.0, 2.0);
  bufferY[index] = mapFloat(imu.a.y, -32768, 32767, -2.0, 2.0);
  bufferZ[index] = mapFloat(imu.a.z, -32768, 32767, -2.0, 2.0);
  bufferGX[index] = mapFloat(imu.g.x, -32768, 32767, -245.0, 245.0);
  bufferGY[index] = mapFloat(imu.g.y, -32768, 32767, -245.0, 245.0);
  bufferGZ[index] = mapFloat(imu.g.z, -32768, 32767, -245.0, 245.0);

  index = (index + 1) % bufferSize; 

  float avgX = 0, avgY = 0, avgZ = 0, avgGX = 0, avgGY = 0, avgGZ = 0;
  for (int i = 0; i < bufferSize; i++) {
    avgX += bufferX[i];
    avgY += bufferY[i];
    avgZ += bufferZ[i];
    avgGX += bufferGX[i];
    avgGY += bufferGY[i];
    avgGZ += bufferGZ[i];
  }
  avgX /= bufferSize;
  avgY /= bufferSize;
  avgZ /= bufferSize;
  avgGX /= bufferSize;
  avgGY /= bufferSize;
  avgGZ /= bufferSize;

  Serial.print(avgX, 2);
  Serial.print("\t");
  Serial.print(avgY, 2);
  Serial.print("\t");
  Serial.print(avgZ, 2);
  Serial.print("\t");
  Serial.print(avgGX, 2);
  Serial.print("\t");
  Serial.print(avgGY, 2);
  Serial.print("\t");
  Serial.println(avgGZ, 2);

  if (debug) {
    Serial.print("Raw aX: "); Serial.print(imu.a.x); Serial.print(" Mapped: "); Serial.println(bufferX[index], 2);
    // Repeat for other values
  }

  delay(10);
}

float mapFloat(long x, long in_min, long in_max, float out_min, float out_max) {
  float result = (x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
  result = constrain(result, out_min, out_max);
  return result;
}
