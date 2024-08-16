/*
 * i2c_slave.c
 *
 *  Created on: Aug 16, 2024
 *      Author: GOROman
 */


#include "main.h"
#include "i2c_slave.h"

extern I2C_HandleTypeDef hi2c1; // (from main.c)

#define RxSIZE	6
uint8_t RxData[RxSIZE];

// I2Cの完了(Cplt = Complete?) リッスン完了コールバック
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	// 再びリッスンモードにする
	HAL_I2C_EnableListen_IT(hi2c);
}


