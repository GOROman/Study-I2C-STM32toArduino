// I2C マスターのサンプル

// I2C Wireライブラリ
#include <Wire.h>

#define I2C_PRIMARY_ADDR 0x45
#define I2C_SECONDARY_ADDR 0x46
#define I2C_GENERAL_CALL_ADDR 0x00

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.printf("Hello I2C!");

  // I2C初期化
  Wire.begin(); 
}

void writeI2C(uint8_t addr, uint8_t* data, int size)
{
  Serial.printf("I2C: beginTransmission(0x%02x)\n", addr);
  Wire.beginTransmission(addr);

  int sentBytes = 0;

  for (int i=0; i<size; ++i ) {
    int res = Wire.write(data[i]);
    sentBytes += res;
    Serial.printf("I2C: [%d] Wire.write(0x%02x) -> %d\n", i, data[i], res);  
  }

  uint8_t err = Wire.endTransmission(false);
  switch(err) {
    case 0:
      Serial.printf("I2C: Wire.endTransmission %dbytes\n", sentBytes);
    break;
    case 1:
      Serial.printf("I2C: Wire.endTransmission Error(%d) data too long to fit in transmit buffer.\n", err );
    break;
    case 2:
      Serial.printf("I2C: Wire.endTransmission Error(%d) received NACK on transmit of address.\n", err );
    break;
    case 3:
      Serial.printf("I2C: Wire.endTransmission Error(%d) received NACK on transmit of data.\n", err );
    break;
    case 4:
      Serial.printf("I2C: Wire.endTransmission Error(%d) other error.\n", err );
    break;
    case 5:
      Serial.printf("I2C: Wire.endTransmission Error(%d) timeout.\n", err );
    break;
    default:
      Serial.printf("I2C: Wire.endTransmission Error(%d) unknown error.\n", err );
  }      
}

int readI2C(uint8_t addr, uint8_t* data, int len)
{
  int result = Wire.requestFrom(addr, len);
  Serial.printf("I2C: Wire.requestFrom(0x%02x, %d) = %d\n", addr, len, result);

  for (int i=0;i<len;++i) {
    byte data = Wire.read();
    Serial.printf("I2C: [%d] Wire.read() -> 0x%02x\n", i, data);
  }
  return result;
}

void test(uint8_t addr)
{
  uint8_t data[] = {1,2,3};
  Serial.printf("=============================== I2C ADDR: 0x%02x\n", addr );
  writeI2C(addr, data,sizeof(data));

  delay(500);

  int len = 3;
  byte buffer[3];
  readI2C(addr, buffer, len);

  delay(500);

}

void loop() {
  // STM32 I2C Dual Addressのテスト
  {
    test(I2C_PRIMARY_ADDR); // Primary
    test(I2C_SECONDARY_ADDR); // Secondary
  }
  
  // STM32 I2C General Call Addressのテスト(送信のみ)
  {
    Serial.printf("=============================== General Call Address\n" );
    byte data[] = {0xff};
    writeI2C(0x00, data, sizeof(data));    
  }
}
