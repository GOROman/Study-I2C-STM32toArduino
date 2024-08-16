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
  // put your main code here, to run repeatedly:
  uint8_t data[] = {3,1,2,3}; // 先頭のバイトが残りのバイト数を意味する

  Wire.beginTransmission(I2C_ADDR);

  int sentBytes = 0;

  for (int i=0; i<sizeof(data); ++i ) {
    sentBytes += Wire.write(data[i]);
  }

  uint8_t err = Wire.endTransmission();
  switch(err) {
    case 0:
      Serial.printf("I2C: OK! %dbytes\n", sentBytes);
    break;
    case 1:
      Serial.printf("I2C: Error(%d) data too long to fit in transmit buffer.\n", err );
    break;
    case 2:
      Serial.printf("I2C: Error(%d) received NACK on transmit of address.\n", err );
    break;
    case 3:
      Serial.printf("I2C: Error(%d) received NACK on transmit of data.\n", err );
    break;
    case 4:
      Serial.printf("I2C: Error(%d) other error.\n", err );
    break;
    case 5:
      Serial.printf("I2C: Error(%d) timeout.\n", err );
    break;
    default:
      Serial.printf("I2C: Error(%d) unknown error.\n", err );
  }      
  delay(500);
}
