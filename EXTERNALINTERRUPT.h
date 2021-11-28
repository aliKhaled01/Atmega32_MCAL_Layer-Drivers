/*
 * EXTERNALINTERRUPT.h
 *
 *  Created on: Oct 11, 2021
 *      Author: lenovo
 */

#ifndef EXTERNALINTERRUPT_H_
#define EXTERNALINTERRUPT_H_
#include "STD_TYPES.h"
#include "utiles.h"
typedef enum
{
	LOW_LEVEL,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE

}enTriggerEgde_type;
typedef enum
{
	EXT_INT0,EXT_INT1,EXT_INT2
}enExternalinterupt;
void EXI_ENABLE(enExternalinterupt interrupt);  // FUNCTION NAME BEST PRACTIVE IS MASKING NOT ENABLING OR DISABLING BECAUSE IT IS DEALING WITH GICR AS METIIONED IN SEESIOJ NOTES WORD
void EXI_DISABLE(enExternalinterupt interrupt);
void EXI_triggerEdge(enExternalinterupt interrupt,enTriggerEgde_type trigger);
void EXI_SetCallBack(enExternalinterupt interrupt,void (*LocalPtr)(void));
#endif /* EXTERNALINTERRUPT_H_ */

