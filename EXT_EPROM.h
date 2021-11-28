
#ifndef MICROCHIP_EEPROM_25AA010A_H_
#define MICROCHIP_EEPROM_25AA010A_H_
#include "STD_Types.h"


#define CHIP_SELECT_PORT		PORTB
#define CHIP_SELECT_DDR			DDRB
#define CHIP_SELECT_PIN			PB0
#define SPI_USED				SPI0

void EEPROM_Init(void);
void EEPROM_WriteByte(uint8 Data , uint16 address);
uint8 EEPROM_ReadByte(uint16 address);


#endif
