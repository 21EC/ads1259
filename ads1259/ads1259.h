#ifndef __ADS1259_H
#define __ADS1259_H

#include "main.h"



#define ADS1259_CLK_H	HAL_GPIO_WritePin(ADS1259_SCK_GPIO_Port, ADS1259_SCK_Pin, 1)
#define ADS1259_CLK_L	HAL_GPIO_WritePin(ADS1259_SCK_GPIO_Port, ADS1259_SCK_Pin, 0)
#define ADS1259_DIN_H	HAL_GPIO_WritePin(ADS1259_MOSI_GPIO_Port, ADS1259_MOSI_Pin, 1)
#define ADS1259_DIN_L	HAL_GPIO_WritePin(ADS1259_MOSI_GPIO_Port, ADS1259_MOSI_Pin, 0)
#define ADS1259_RST_H	HAL_GPIO_WritePin(ADS1259_RST_GPIO_Port, ADS1259_RST_Pin, GPIO_PIN_SET)
#define ADS1259_RST_L	HAL_GPIO_WritePin(ADS1259_RST_GPIO_Port, ADS1259_RST_Pin, GPIO_PIN_RESET)

#define ADS1259_START	HAL_GPIO_WritePin(ADS1259_START_GPIO_Port, ADS1259_START_Pin, GPIO_PIN_SET)
#define ADS1259_CS_L	HAL_GPIO_WritePin(ADS1259_CS_GPIO_Port, ADS1259_CS_Pin, GPIO_PIN_RESET)
#define ADS1259_DRDY	HAL_GPIO_ReadPin(ADS1259_DRDY_GPIO_Port, ADS1259_DRDY_Pin)
#define ADS1259_DOUT	HAL_GPIO_ReadPin(ADS1259_MISO_GPIO_Port, ADS1259_MISO_Pin)


void ADS1259_write(uint8_t data);

uint32_t ADS1259_read(void);

uint8_t ADS1259_readReg(void);

void ADS1259_Init(void);


#endif
