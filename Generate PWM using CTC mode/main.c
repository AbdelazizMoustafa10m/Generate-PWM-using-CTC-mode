/*
 * Generate PWM using CTC mode.c
 *
 * Created: 4/28/2020 11:19:00 PM
 * Author : Abdelaziz
 */ 

/* we want to generate 50 HZ PWM signal with 45% duty cycle
 * T=1/freq = 20ms, Ton= 13ms, Toff= 7ms
 * we choose no prescaler, so OCR for Ton= 9999, OCR for Toff= 10999
 */

#include <avr/interrupt.h>
#include "Timer1.h"

/******************************************************************************************************
*                                         Global Variables
******************************************************************************************************/
volatile uint8 Flag= 0;

/******************************************************************************************************
*                            This ISR is fired whenever a match occurs
******************************************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	// check for the global Flag
	// if Flag == 1, delay required = 13 ms which is 12999
	// if Flag == 0, delay required = 7 ms which is 6999
	// thus, the value of the OCRx should be constantly updated
	if(Flag)
	{
		Flag=0; //Clear Flag
		SET_BIT(PORTB,6); // Set Pin 
		OCR1A= 12999; //Update compare value
	}
	else
	{
		Flag=1; //Set Flag
		CLEAR_BIT(PORTB,6); // Clear Pin
		OCR1A= 6999; //Update compare value
	}
}

int main(void)
{
    /* initialize PB6 to be in output Mode */ 
    SET_BIT(DDRB,6);
    /* Initialize Timer1 */
    Timer1_Init();
    // loop forever
    while(1)
    {
	    // do nothing  
    }
}

