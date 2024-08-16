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

/**
  * @brief  Listen Complete callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */

// I2Cの完了(Cplt = Complete?) リッスン完了コールバック
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	// 再びリッスンモードにする
	HAL_I2C_EnableListen_IT(hi2c);
}

/*
 * @brief  Slave Address Match callback.
 * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 *                the configuration information for the specified I2C.
 * @param  TransferDirection Master request Transfer Direction (Write/Read), value of @ref I2C_XFERDIRECTION
 * @param  AddrMatchCode Address Match Code
 * @retval None
 */

// スレーブアドレスが一致した時に呼ばれるコールバック
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	// 転送の方向を判別
	if (TransferDirection == I2C_DIRECTION_TRANSMIT) {
		/**
		  * @brief  Sequential receive in slave/device I2C mode an amount of data in non-blocking mode with Interrupt
		  * @note   This interface allow to manage repeated start condition when a direction change during transfer
		  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
		  *                the configuration information for the specified I2C.
		  * @param  pData Pointer to data buffer
		  * @param  Size Amount of data to be sent
		  * @param  XferOptions Options of Transfer, value of @ref I2C_XFEROPTIONS
		  * @retval HAL status
		  */

			// 受信開始する
			HAL_I2C_Slave_Seq_Receive_IT(hi2c, RxData, RxSIZE, I2C_FIRST_AND_LAST_FRAME);
	} else {
	}
}

/**
  * @brief  Slave Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
// 受信完了時に呼ばれるコールバック
// [注意] RxSIZE を HAL_I2C_Slave_Seq_Receive_IT で指定しているので RxSIZE分のデータが来ない場合はこのコールバックは呼ばれない
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	// GPIOをトグルする(LEDがある前提)
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11); // PA11
}
