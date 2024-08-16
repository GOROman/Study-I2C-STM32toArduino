// I2C マスターのサンプル

// I2C Wireライブラリ
#include <Wire.h>

#define I2C_ADDR 0x45

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.printf("Hello I2C!");

  // I2C初期化
  Wire.begin(); 
}

void loop() {
  uint8_t err = 0;
  // put your main code here, to run repeatedly:
  uint8_t data[] = {0,1,2,3,4,5};
  Wire.beginTransmission(I2C_ADDR);

  int sentBytes = 0;

  for (int i=0; i<sizeof(data); ++i ) {
    sentBytes += Wire.write(data[i]);
  }

  err = Wire.endTransmission();
  if ( err != 0 ) {
    Serial.printf("I2C: Error endTransmission = %d\n", err );
  } else {
    Serial.printf("I2C: OK! %dbytes\n", sentBytes);
  }
  delay(500);
}
