
#ifndef SPI_H_
#define _SPI_H_

#include "STD_Types.h"
typedef enum
{
	SPI_Disable,
	SPI_Enable,
}SPI_Control;

typedef enum
{
	SPI_InterruptDisable,
	SPI_InterruptEnable,
}SPI_InterruptState;

typedef enum
	{
		SPI_MSB,
		SPI_LSB,
}SPI_DataOrder;

typedef enum
{
	SPI_SLAVE,
	SPI_MASTER,
}SPI_Mode;

typedef enum
{
	SPI_CLKMode0,
	SPI_CLKMode1,
	SPI_CLKMode2,
	SPI_CLKMode3,
}SPI_ClockModes;

typedef enum
{
	SPI_FCPU_BY_2,
	SPI_FCPU_BY_4,
	SPI_FCPU_BY_8,
	SPI_FCPU_BY_16,
	SPI_FCPU_BY_32,
	SPI_FCPU_BY_64,
	SPI_FCPU_BY_128,
}SPI_Freq;

typedef enum
{
	SPI_NoError,
	SPI_WriteCollison,
}SPI_Errors;

typedef struct
{
	SPI_Control			EnableControl;
	SPI_Mode			Mode;
	SPI_ClockModes		ClockMode;
	SPI_DataOrder		DataOrder;
	SPI_InterruptState	InterruptState;

	void (*SPI_TransfereInterruptCall) (void);
	/* For Slave Mode -- Freq Should not be Selected */
	SPI_Freq			Freq;
	/* This Bit dose not clear it Self, Check it Before Using Data and erase The Error Your Self By assigning it to SPI_NoError */
	SPI_Errors			Error;
}SPI_ConfigStruct;
///////////////////////////////////////////////////////////
extern SPI_ConfigStruct SPI0;
//////////////////////////////////////////////////////////
void SPI_Init();
uint8 SPI_ReadWrite_Blocking(uint8 Data);
uint8 SPI_ReadWrite_NonBlocking(uint8 Data);
#endif /* ATMEGA32A_SPI_H_ */
