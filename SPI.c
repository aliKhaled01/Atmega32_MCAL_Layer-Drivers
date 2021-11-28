/*
 * ATmega32A_SPI.c
 *
 * Created: 4/19/2020 11:33:02 AM
 *  Author: Hamdy
 */ 
#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Utils.h"
SPI_ConfigStruct SPI0 = {.SPI_TransfereInterruptCall = NULLPTR};//designator
#define SCK  7
#define MISO 6
#define MOSI 5
#define SS 	 4

void SPI_Init(void)
{
	SPCR = 0;
	SPSR = 0;
	switch(SPI0.EnableControl)
	{
	case SPI_Disable:
		break;
	case SPI_Enable:
		switch(SPI0.Mode)
		{
		case SPI_MASTER:
			//it is better here to use setbit and clear bit
			SPCR |= (1<<MSTR);
			DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SS);//SS
//			PORTB |= (1<<SS) | (1<<MOSI);
			break;
		case SPI_SLAVE:
			DDRB |= (1<<MISO);
			break;
		}
		switch(SPI0.DataOrder)
		{
		case SPI_LSB:
			SPCR |= (1<<DORD);
			break;
		case SPI_MSB:
			CLEAR_BIT(SPCR,DORD);
			break;
		}
		switch(SPI0.InterruptState)
		{
		case SPI_InterruptDisable:
			break;
		case SPI_InterruptEnable:
			SPCR |= (1<<SPIE);
			break;
		}
		switch(SPI0.ClockMode)
		{
		case SPI_CLKMode0:
			//using Default 0 0
			break;
		case SPI_CLKMode1:
			SPCR |= (1<<CPHA);
			break;
		case SPI_CLKMode2:
			SPCR |= (1<<CPOL);
			/*
			 * Note : if Used SPI Mode 3 or Mode 2 (CLK IDLE STATE = HIGH)
			 * in Some MicroControllers we must Explicitly State that The Default clk pin state is High
			 * By Setting the pin to Output with a High Value
			 */
			PORTB |= (1<<SCK);
			break;
		case SPI_CLKMode3:
			SPCR |= (1<<CPHA) | (1<<CPOL);
			PORTB |= (1<<SCK);
			break;
		}
		switch(SPI0.Freq)
		{
		case SPI_FCPU_BY_2:
			SPSR |= (1<<SPI2X);
			break;
		case SPI_FCPU_BY_4:
			break;
		case SPI_FCPU_BY_8:
			SPSR |= (1<<SPI2X);
			SPCR |= (1<<SPR0);
			break;
		case SPI_FCPU_BY_16:
			SPCR |= (1<<SPR0);
			break;
		case SPI_FCPU_BY_32:
			SPSR |= (1<<SPI2X);
			SPCR |= (1<<SPR1);
			break;
		case SPI_FCPU_BY_64:
			SPCR |= (1<<SPR1);
			break;
		case SPI_FCPU_BY_128:
			SPCR |= (1<<SPR1) | (1<<SPR0);
			break;
		}
		/* Enable SPI Communication */
		SPCR |= (1<<SPE);
		break;
	}
}
void SPI_SetCallback(void (*ptr) (void))
{
	SPI0.SPI_TransfereInterruptCall=ptr;

}

uint8 SPI_ReadWrite_Blocking(uint8 Data)
{
	PORTB &= (~(1<<SS));
	/* Transmit Data Using SPI Bus */
	SPDR = Data;
	/* Check if a Write Collision Error Occurred */
	if ( (SPSR & (1<<WCOL) ) != 0)
	{
		SPI0.Error = SPI_WriteCollison;
	}else
	{
		SPI0.Error = SPI_NoError;
	}

	/* Block till The End of Transmit ion */
	while ( (SPSR & (1<<SPIF)) == 0 ) {}

	/* return Rx Data From SPI */
	return SPDR;
}


uint8 SPI_ReadWrite_NonBlocking(uint8 Data)
{
	PORTB &= (~(1<<SS));
	/* Transmit Data Using SPI Bus */
	SPDR = Data;
	/* Check if a Write Collision Error Occurred */
	if ( (SPSR & (1<<WCOL))  != 0)
	{
		SPI0.Error = SPI_WriteCollison;
	}else
	{
		SPI0.Error = SPI_NoError;
	}
	/* return Rx Data From SPI */
	return SPDR;
}



ISR(SPI_STC_vect)
{
	if (SPI0.SPI_TransfereInterruptCall != NULLPTR)
	{
		SPI0.SPI_TransfereInterruptCall();
	}
}



/**
 * App use this driver like that
 *-------------------------------------------------
 * 	SPI0.EnableControl = SPI_Enable;
	SPI0.Mode = SPI_MASTER;
	SPI0.ClockMode = SPI_CLKMode3;
	SPI0.DataOrder = SPI_MSB;
	SPI0.Freq = SPI_FCPU_BY_8;
	SPI0.InterruptState = SPI_InterruptDisable;
 * **/
