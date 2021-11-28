/*
 * Timer_services.h
 *
 *  Created on: Oct 15, 2021
 *      Author: lenovo
 */

#ifndef TIMER_SERVICES_H_
#define TIMER_SERVICES_H_
#include "STD_TYPES.h"
#include "timer.h"
void PWM_Init();
void PWM_Freq_KHZ(uint16 frq);
void PWM_Freq_HZ(uint16 frq);
void PWM_Duty(uint16 duty);

static void Func_ICU(void);


#endif /* TIMER_SERVICES_H_ */
