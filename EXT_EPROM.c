
#include "SPI.h"
#include "EXT_EPROM.h"
#include <util/delay.h>
#include <avr/io.h>
#include "Utils.h"

#define WREN_OPCODE		(0x06)
#define WRTIE_OPCODE	(0x02)
#define READ_OPCODE		(0x03)
#define DUMMY_DATA		(0xFF)


void  EEPROM_Init(void)
{
	SPI0.EnableControl = SPI_Enable;
	SPI0.Mode = SPI_MASTER;
	SPI0.ClockMode = SPI_CLKMode3;
	SPI0.DataOrder = SPI_MSB;
	SPI0.Freq = SPI_FCPU_BY_8;
	SPI0.InterruptState = SPI_InterruptDisable;
	/* Config CS Pin  to be in output mode to use it as CS */

	SET_BIT(CHIP_SELECT_DDR,CHIP_SELECT_PIN);
	SET_BIT(CHIP_SELECT_PORT,CHIP_SELECT_PIN);

	SPI_Init();
}

void EEPROM_WriteByte(uint8 Data , uint16 address)
{
	/* Select EEPROM By Applying 0 to CS */
	CLEAR_BIT(CHIP_SELECT_PORT,CHIP_SELECT_PIN);
	/* Write Latch Enable */
	SPI_ReadWrite_Blocking(WREN_OPCODE);
	/* Apply High to CS to Make Write Latch Enable Instruction Executed*/
	SET_BIT(CHIP_SELECT_PORT,CHIP_SELECT_PIN);
	_delay_ms(50);
	/* Select EEPROM By Applying 0 to CS */
	CLEAR_BIT(CHIP_SELECT_PORT,CHIP_SELECT_PIN);

	SPI_ReadWrite_Blocking(WRTIE_OPCODE);
	SPI_ReadWrite_Blocking(address);
	SPI_ReadWrite_Blocking(Data);
	SET_BIT(CHIP_SELECT_PORT,CHIP_SELECT_PIN);
}

uint8 EEPROM_ReadByte(uint16 address)
{
	
	uint8 ReadData = 0;
	//ss is low
	CLEAR_BIT(CHIP_SELECT_PORT,CHIP_SELECT_PIN);
	//(0x03)
	SPI_ReadWrite_Blocking(READ_OPCODE);
	///0x00
	SPI_ReadWrite_Blocking(address);
	ReadData = SPI_ReadWrite_Blocking(DUMMY_DATA);
	SET_BIT(CHIP_SELECT_PORT,CHIP_SELECT_PIN);
	return ReadData;
}
