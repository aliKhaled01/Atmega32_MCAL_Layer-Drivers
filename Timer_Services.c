/*
 * Timer_Services.c
 *
 *  Created on: Oct 15, 2021
 *      Author: lenovo
 */

#ifndef TIMER_SERVICES_C_
#define TIMER_SERVICES_C_
#include "timer.h"
#include "Timer_services.h"
static uint8 flag=0;
static uint32 t1=0;
static uint32 t2=0;
static uint32 t3=0;
void PWM_Init()
{
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,FROM_PRESACLLING_8,OCRA_NON_INVERTING,OCRB_DISCONNECTED);

}
void PWM_Freq_KHZ(uint16 frq)
{
	if(frq==0);
	else
	{
		uint16 Ttotal = 1000/frq;
		if(Ttotal>=1)
		{
			ICR1=Ttotal-1;
		}
		else
		{
			ICR1=0;
		}
	}


}
void PWM_Freq_HZ(uint16 frq)
{

	if(frq==0);
	else
	{
		uint16 Ttotal = (uint32)1000000/frq;
		if(Ttotal>=1)
		{
			ICR1=Ttotal-1;
		}
		else
		{
			ICR1=0;
		}
	}
}
void PWM_Duty(uint16 duty)
{
	if(duty<=100)
	{
		uint16 Ton = ((uint32)duty*(ICR1+1))/100;
		if(Ton>1)
		{
			OCR1A=Ton-1;
		}
		else
		{
			OCR1A=0;
		}
	}
}
void PWM_Measure(uint32* Pfreq,uint8* Pduty)  //measure PWM from ICU  , we can measure from external interrupt pin also
{
	TCNT1=0;
	uint16 Ton , Toff;
	Timer1_InputCaptureEdge(ICU_RISING_EDGE);
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_ICU_Interrupt_Enable();
	flag=0; // if function called again in while
	while(flag<3);
	Ton=t2-t1;
	Toff = t3-t2;
	*Pduty = ((uint32)Ton*100)/(Ton+Toff);
	*Pfreq= ( (uint32)1000000/(Ton+Toff) );
}
static void Func_ICU(void)
{
	if(flag==0)
	{
		t1=ICR1; //INPUT CAP UNIT READING WHEN RISING EDGE OCCURS
		Timer1_InputCaptureEdge(ICU_FALLING_EDGE);
		flag=1;
	}
	else if(flag==1)
	{
		t2=ICR1;
		Timer1_InputCaptureEdge(ICU_RISING_EDGE);
		flag=2;

	}
	else if(flag==2)
	{
		t3=ICR1;
		Timer1_ICU_Interrupt_Disable();
		flag=3;
	}
}
//ASSUME 8MHZ AT PROTEUS
void Timer1_SetInterruptTime_ms(uint32 time,void(*LocalPtr)(void))
{
	time = time *1000;
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,FROM_PRESACLLING_1024,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	OCR1A=(uint16)(( (time) /128))-1;//us
	Timer1_OCA_SetCallBack(LocalPtr);
	Timer1_OCAInterrupt_Enable();

}
void Timer1_SetInterruptTime_us(uint64 time,void(*LocalPtr)(void))
{

	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,FROM_PRESACLLING_1024,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	OCR1A=(uint16)(( (time) /128))-1;//us
	Timer1_OCA_SetCallBack(LocalPtr);
	Timer1_OCAInterrupt_Enable();

}


#endif /* TIMER_SERVICES_C_ */
