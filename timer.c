#include "timer.h"
#include "MCAL_REGISTERS/Mem_Map32.h"

/*
 * timer.c
 *
 *  Created on: Oct 9, 2021
 *      Author: lenovo
 */
static void (*Timer1_OVF_Fptr) (void) =NULLPTR;
static void (*Timer1_OCA_Fptr) (void) =NULLPTR;
static void (*Timer1_OCB_Fptr) (void) =NULLPTR;
static void (*Timer1_ICU_Fptr) (void) =NULLPTR;

void Timer0_Init(enTIMER_MODE mode ,enPRESCALAR prescalling,enOC0Mode_type OC0mode)
{
	switch(mode)
	{
	case NORMAL:
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		break;
	case PWM_PHASE_CORRECT:
		SET_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		break;
	case CTC:
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	case FAST_PWM:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;

	}
	TCCR0=TCCR0&0xf8;
	switch(prescalling)
	{
	case TIMER_STOP :
		CLEAR_BIT(TCCR0,0);
		CLEAR_BIT(TCCR0,1);
		CLEAR_BIT(TCCR0,2);

		break;
	case NO_PRESCALLING:
		SET_BIT(TCCR0,0);
		CLEAR_BIT(TCCR0,1);
		CLEAR_BIT(TCCR0,2);

		break;
	case FROM_PRESACLLING_8 :
		CLEAR_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLEAR_BIT(TCCR0,2);
		break;

	case FROM_PRESACLLING_64 :
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLEAR_BIT(TCCR0,2);
		break;

	case FROM_PRESACLLING_256 :
		CLEAR_BIT(TCCR0,0);
		CLEAR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
		break;

	case FROM_PRESACLLING_1024:
		SET_BIT(TCCR0,0);
		CLEAR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
		break;

	}


	switch(OC0mode)
	{
	case OCO_DISCONNECTED :
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
	case OCO_TOGGLE :
		SET_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
	case OCO_NON_INVERTING :
		CLEAR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	case OCO_INVERTING :
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}


}
void Timer0_Disable()
{
	CLEAR_BIT(TCCR0,0);
	CLEAR_BIT(TCCR0,1);
	CLEAR_BIT(TCCR0,2);
}

void Timer0_OVInterrupt_Enable()
{
	SET_BIT(TIMSK,TOIE0);
}

void Timer0_OVInterrupt_Disable()
{
	CLEAR_BIT(TIMSK,TOIE0);
}

void Timer0_OCInterrupt_Enable(void)
{
	SET_BIT(TIMSK,OCIE0);

}

void Timer0_OCInterrupt_Disable(void)
{
	CLEAR_BIT(TIMSK,OCIE0);

}
void Timer1_Init( Timer1Mode_t mode,Timer1Scaler_t scaler,OC1A_Mode_t oc1a_mode,OC1B_Mode_t oc1b_mode)

{
	/*
	Timer/Counter1
	Control Register A –
	TCCR1A
			COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10
	 */
	switch (mode)
	{
	case TIMER1_NORMAL_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
	case TIMER1_CTC_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_CTC_OCRA_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}
	switch (oc1a_mode)
	{
	case OCRA_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_NON_INVERTING:
		CLEAR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
	switch (oc1b_mode)
	{
	case OCRB_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_NON_INVERTING:
		CLEAR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}


	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}

void Timer1_InputCaptureEdge(enICU_EDGE_TYPE edge)
{
	if(edge==ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,ICES1);
	}
	else if(edge==ICU_FALLING_EDGE)
	{
		CLEAR_BIT(TCCR1B,ICES1);
	}
}
void Timer1_ICU_Interrupt_Enable()
{
	SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_Interrupt_Disable()
{
	CLEAR_BIT(TIMSK,TICIE1);
}


void Timer1_OVInterrupt_Enable()
{
	SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVInterrupt_Disable()
{
	CLEAR_BIT(TIMSK,TOIE1);
}


void Timer1_OCAInterrupt_Enable(void)
{
	SET_BIT(TIMSK,OCIE1A);

}

void Timer1_OCAInterrupt_Disable(void)
{
	CLEAR_BIT(TIMSK,OCIE1A);

}
void Timer1_OCBInterrupt_Enable(void)
{
	SET_BIT(TIMSK,OCIE1B);

}

void Timer1_OCBInterrupt_Disable(void)
{
	CLEAR_BIT(TIMSK,OCIE1B);

}
void Timer1_OVF_SetCallBack(void(*LocalPtr)(void))
{
	Timer1_OVF_Fptr=LocalPtr;
}
void Timer1_OCA_SetCallBack(void(*LocalPtr)(void))
{
	Timer1_OCA_Fptr=LocalPtr;
}
void Timer1_OCB_SetCallBack(void(*LocalPtr)(void))
{
	Timer1_OCB_Fptr=LocalPtr;
}
void Timer1_ICU_SetCallBack(void(*LocalPtr)(void))
{
	Timer1_ICU_Fptr=LocalPtr;
}

ISR(TIMER1_OVF_vect)
{
	if( Timer1_OVF_Fptr!=NULLPTR )
	{
		Timer1_OVF_Fptr();
	}

}


//ISR(TIMER1_COMPA_vect)
//{
//	if( Timer1_OCA_Fptr!=NULLPTR )
//	{
//		Timer1_OCA_Fptr();
//	}
//
//}

ISR(TIMER1_COMPB_vect)
{
	if( Timer1_OCB_Fptr!=NULLPTR )
	{
		Timer1_OCB_Fptr();
	}

}
ISR(TIMER1_CAPT_vect)
{
	if( Timer1_ICU_Fptr!=NULLPTR )
	{
		Timer1_ICU_Fptr();
	}

}
