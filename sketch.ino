#include <Wire.h>

#define MPU6050_ADDR 0x68

int16_t Ax, Ay, Az;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // I2C start

  // Wake up MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 6, true);

  Ax = Wire.read() << 8 | Wire.read();
  Ay = Wire.read() << 8 | Wire.read();
  Az = Wire.read() << 8 | Wire.read();

  if (abs(Ax) > 15000 || abs(Ay) > 15000 || abs(Az) > 15000) {
    Serial.println("Motion Detected!");
  }

  Serial.print("X: "); Serial.print(Ax);
  Serial.print(" Y: "); Serial.print(Ay);
  Serial.print(" Z: "); Serial.println(Az);

  delay(500);
}