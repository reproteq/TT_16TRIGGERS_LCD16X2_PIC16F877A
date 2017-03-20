#include "Includes.h"



void interrupt ISR(void)
{
	if(T0IF)  //If Timer0 Interrupt
	{
		TMR0 = 0x08; // Timer0 should overflow after 250 instructions (250x4 = 1msec)
		T0IF = 0;    // Clear the interrupt
		msCounter++; // 1 msec time has occurred
	}
}