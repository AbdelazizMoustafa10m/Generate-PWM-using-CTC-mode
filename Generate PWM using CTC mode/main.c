/*
 * Generate PWM using CTC mode.c
 *
 * Created: 10/9/2019 2:01:14 PM
 * Author : Abdelaziz
 */ 

/* we want to generate 50 HZ PWM signal with 45% duty cycle
 * T=1/freq = 20ms, Ton= 9ms, Toff= 11ms
 * we choose no prescaler, so OCR for Ton= 9999, OCR for Toff= 10999
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t count= 0;

void Timer1_Init(void)
{
	// set up timer with prescaler = 0 and CTC mode
	TCCR1B |= (1 << WGM12)|(1 << CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	// initialize compare value
	OCR1A = 19999;
	
	// enable compare interrupt
	TIMSK |= (1 << OCIE1A);
	
	// enable global interrupts
	sei();
}

// this ISR is fired whenever a match occurs
ISR (TIMER1_COMPA_vect)
{
	// check for the global counter
	// if count == 1, delay required = 11 ms which is 10999
	// if count == 0, delay required = 9 ms which is 1=9999
	// thus, the value of the OCRx should be constantly updated
	if(count)
	{
		count=0; //clear count
		PORTB|= (1<<PB6); // set Pin
		OCR1A= 10999; //update compare value
	}
	else
	{
		count=1; //set count
		PORTB&= ~(1<<PB6); // clear pin
		OCR1A= 9999;
	}
}

int main(void)
{
    // initialize the output pin, say Pb6
    DDRB |= (1 << 6);
    
    // initialize timer1
    Timer1_Init();
    
    // loop forever
    while(1)
    {
	    // do nothing
	    
    }
}

