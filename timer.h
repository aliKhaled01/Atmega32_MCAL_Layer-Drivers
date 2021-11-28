/*
 * timer.h
 *
 *  Created on: Oct 9, 2021
 *      Author: lenovo
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "MCAL_REGISTERS/Mem_Map32.h"
#include "MCAL_REGISTERS/Mem_Map32.h"
#include "utiles.h"

typedef enum
{
	NORMAL,PWM_PHASE_CORRECT,CTC,FAST_PWM
}enTIMER_MODE;
typedef enum
{
	TIMER_STOP=0,NO_PRESCALLING,FROM_PRESACLLING_8,FROM_PRESACLLING_64,FROM_PRESACLLING_256,FROM_PRESACLLING_1024,ETERNAL_RISING,EXTERNAL_FALLING
}enPRESCALAR;
typedef enum
{
	ICU_RISING_EDGE,ICU_FALLING_EDGE
}enICU_EDGE_TYPE;
typedef enum
{
	OCO_DISCONNECTED,
	OCO_TOGGLE,
	OCO_INVERTING,
	OCO_NON_INVERTING


}enOC0Mode_type;
typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1Scaler_t;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_t;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_t;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_t;
#define ICU_PORT GPIO_D
#define ICU_PIN  GPIO_PIN6
void Timer0_Init(enTIMER_MODE mode ,enPRESCALAR prescalling,enOC0Mode_type OC0mode);
void Timer0_OVInterrupt_Enable();
void Timer0_OVInterrupt_Disable();
void Timer1_Init( Timer1Mode_t mode,Timer1Scaler_t scaler,OC1A_Mode_t oc1a_mode,OC1B_Mode_t oc1b_mode);
void Timer1_InputCaptureEdge(enICU_EDGE_TYPE edge);

#endif /* TIMER_H_ */
