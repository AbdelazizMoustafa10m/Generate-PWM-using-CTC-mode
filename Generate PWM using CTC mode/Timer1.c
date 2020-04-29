/*
 * Timer1.c
 *
 * Created: 4/29/2020 12:27:30 AM
 *  Author: Abdelaziz
 */ 
/******************************************************************************************************
*                                         Include Header Files
******************************************************************************************************/
#include "Timer1.h"

/******************************************************************************************************
*                                         Function Definition
******************************************************************************************************/
void Timer1_Init(void)
{
	/* Set Up Timer1 with Prescaler = 0 */
	SET_BIT(TCCR1B,CS10);
	/* Set Up Timer1 to Work in CTC Mode */
	SET_BIT(TCCR1B,WGM12);
	/* Initialize counter with zero */
	TCNT1 = 0;
	/* Initialize compare value */
	OCR1A = 19999;
	/* Enable compare interrupt */
	SET_BIT(TIMSK,OCIE1A);
	/* Enable global interrupts*/
	SET_BIT(SREG,7);
}
