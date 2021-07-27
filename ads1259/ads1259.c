#include "ads1259.h"


uint8_t ADS1259_initializeSequence[11] =
{
	0x40, 0x08,			//	Write Register opcode bytes, starting at address 0x00, 9-byte block
	0x05,				//	CONFIG0: SPI timeout EN || Internal ref bias EN
	0x11,				//	CONFIG1: sinc^2 Filter || External REF || START CONV No delay
	0x04,				//	CONFIG2: SYNCOUT DIS || Gate CTL Mode || 400SPS
	0x00, 0x00, 0x00,	//	OFC[2:0]: No offset Correction
	0x00, 0x00, 0x40	//	FSC[2:0]: No Full-Scale Correction
};

static void delay(uint32_t us)
{
	while (us--)
	{
		//	Mind your MCLK freq.
		for (uint8_t i = 170; i > 0; i--);
	}
}

void ADS1259_write(uint8_t data)
{

	for(uint8_t si = 0; si < 8; si++)
	{
		ADS1259_CLK_H;
		if (data & 0x80)
			ADS1259_DIN_H;
		else
			ADS1259_DIN_L;

		data <<= 1;
		delay(20);
		ADS1259_CLK_L;
		delay(20);
	}
}

uint32_t ADS1259_read(void)
{
	uint32_t data_fb;
	uint32_t data_bk;
	ADS1259_CLK_H;
	ADS1259_CLK_L;

	while (ADS1259_DRDY);
	data_fb = 0;
	for (uint8_t i = 0; i < 24; i++)
	{
		data_fb <<= 1;
		ADS1259_CLK_H;
		delay(20);
		if (ADS1259_DOUT)
			data_fb |= 0x00000001;
		else
			data_fb &= 0xfffffffe;
		ADS1259_CLK_L;
		delay(20);
	}
	data_bk = data_fb^0x800000;
	return data_bk;
}

uint8_t ADS1259_readReg(void)
{
	uint8_t reg;
	reg = 0;
	ADS1259_CLK_H;
	ADS1259_CLK_L;
	for(uint8_t i = 0; i < 8; i++)
	{
		reg<<=1;
		delay(0x20);
		if (ADS1259_DOUT)
			reg |= 0x01;
		else
			reg &= 0xfe;

		ADS1259_CLK_H;
		delay(20);
		ADS1259_CLK_L;
	}
	return reg;
}

void ADS1259_Init(void)
{
	//	Hardware Reset
	ADS1259_RST_H;
	HAL_Delay(10);
	ADS1259_RST_L;
	HAL_Delay(10);
	ADS1259_RST_H;
	HAL_Delay(10);

	//	Start Conversion
	ADS1259_CS_L;
	ADS1259_START;

	//	Configure All registers once
	for (uint8_t i = 0; i < 11; i++)
	{
		ADS1259_write(ADS1259_initializeSequence[i]);
	}
	HAL_Delay(10);

	/*
	//	Send Command: Cancel RDATAC Mode to write register commands.
	HAL_SPI_Transmit(&hspi2, (uint8_t*)0x11, 1, 0x10);

	//	Configure All registers once
	HAL_SPI_Transmit(&hspi2, (uint8_t*)ADS1259_initializeSequence, sizeof(ADS1259_initializeSequence), 0x10);

	HAL_SPI_Transmit(&hspi2, (uint8_t*)0x10, 1, 0x10);

	//	Start Conversion by pulling START pin HIGH
	HAL_GPIO_WritePin(ADS1259_START_GPIO_Port, ADS1259_START_Pin, GPIO_PIN_SET);
	//	Then you can read the converted data.
	*/

}

