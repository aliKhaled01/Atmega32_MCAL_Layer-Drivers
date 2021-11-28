//#include "EXTERNALINTERRUPT.h"
//#include "MCAL_REGISTERS/Mem_Map32.h"
//#include "utiles.h"
//static void (*INT0_Fptr) (void) =NULLPTR;
//static void (*INT1_Fptr) (void) =NULLPTR;
//static  void (*INT2_Fptr) (void) =NULLPTR;
///*
// * EXTERNALINTERRUPT.c
// *
// *  Created on: Oct 11, 2021
// *      Author: lenovo
// */
//void EXI_DISABLE(enExternalinterupt interrupt)
//{
//	switch(interrupt)
//	{
//	case EXT_INT0:
//		CLEAR_BIT(GICR,INT0);
//		break;
//	case EXT_INT1:
//		CLEAR_BIT(GICR,INT1);
//		break;
//	case EXT_INT2:
//		CLEAR_BIT(GICR,INT2);
//		break;
//
//	}
//
//}
//void EXI_ENABLE(enExternalinterupt interrupt)
//{
//	switch(interrupt)
//	{
//	case EXT_INT0:
//		SET_BIT(GICR,INT0);
//		break;
//	case EXT_INT1:
//		SET_BIT(GICR,INT1);
//		break;
//	case EXT_INT2:
//		SET_BIT(GICR,INT2);
//		break;
//
//	}
//
//}
//
//
//void EXI_triggerEdge(enExternalinterupt interrupt,enTriggerEgde_type trigger)
//{
//	switch (interrupt)
//	{
//	case EXT_INT0:
//		switch(trigger)
//		{
//		case LOW_LEVEL:
//			CLEAR_BIT(MCUCR,ISC00);
//			CLEAR_BIT(MCUCR,ISC01);
//			break;
//		case ANY_LOGIC_CHANGE:
//			SET_BIT(MCUCR,ISC00);
//			CLEAR_BIT(MCUCR,ISC01);
//			break;
//		case FALLING_EDGE:
//			CLEAR_BIT(MCUCR,ISC00);
//			SET_BIT(MCUCR,ISC01);
//			break;
//		case RISING_EDGE:
//			SET_BIT(MCUCR,ISC00);
//			SET_BIT(MCUCR,ISC01);
//			break;
//
//		}
//		break;
//
//
//		case EXT_INT1:
//			switch(trigger)
//			{
//			case LOW_LEVEL:
//				CLEAR_BIT(MCUCR,ISC10);
//				CLEAR_BIT(MCUCR,ISC11);
//				break;
//			case ANY_LOGIC_CHANGE:
//				SET_BIT(MCUCR,ISC10);
//				CLEAR_BIT(MCUCR,ISC11);
//				break;
//			case FALLING_EDGE:
//				CLEAR_BIT(MCUCR,ISC10);
//				SET_BIT(MCUCR,ISC11);
//				break;
//			case RISING_EDGE:
//				SET_BIT(MCUCR,ISC10);
//				SET_BIT(MCUCR,ISC11);
//				break;
//
//			}
//			break;
//
//
//			case EXT_INT2:
//				switch(trigger)
//				{
//
//				case FALLING_EDGE:
//					CLEAR_BIT(MCUCSR,ISC2);
//					break;
//				case RISING_EDGE:
//					SET_BIT(MCUCSR,ISC2);
//					break;
//				default:
//					CLEAR_BIT(MCUCSR,ISC2);
//				}
//				break;
//
//	}
//}
//
//void EXI_SetCallBack(enExternalinterupt interrupt,void (*LocalPtr)(void))
//{
//	switch(interrupt)
//	{
//	case EXT_INT0 :
//		INT0_Fptr = LocalPtr;
//		break;
//	case EXT_INT1 :
//		INT1_Fptr = LocalPtr;
//		break;
//	case EXT_INT2 :
//		INT2_Fptr = LocalPtr;
//		break;
//	}
//}
//ISR(INT0_vect)  //can be in switch case each case withou the need of INT0_Fptr just call the LocalPtr
//{
//	if(INT0_Fptr!=NULLPTR)
//	{
//		INT0_Fptr();
//	}
//}
//ISR(INT1_vect)
//{
//
//	if(INT1_Fptr!=NULLPTR)
//	{
//		INT1_Fptr();
//	}
//}
//ISR(INT2_vect)
//{
//
//	if(INT2_Fptr!=NULLPTR)
//	{
//		INT2_Fptr();
//	}
//}
