#include "Includes.h"


// define digital clock variables
unsigned int msCounter  = 0;
unsigned int csCounter  = 0;
unsigned int secCounter = 0; // valor por defecto

// funciones de eeprom
void ReadEeprom(void)
{
    secCounter = eeprom_read(0);
    csCounter = eeprom_read(2);
}

void WriteEeprom(void)
{
   eeprom_write(0, secCounter);
   eeprom_write(2, csCounter); 
}

void ClearMemo(void)
{
    msCounter = 0;
    csCounter = 0;
    secCounter = 0;
}

void InitTimer0(void)
{
	// Timer0 is 8bit timer, select T0CS and PSA to be zero
	OPTION_REG &= 0xC1;     // Make Prescalar 1:4
	
	T0IE = 1;				// Enable Timer0 interrupt
	GIE = 1;				// Enable global interrupts
}


void Init1msecTimerInterrupt(void)
{
	InitTimer0();		// Intialize timer0 to genrate 1msec interrupts
}




void UpdateTimeCounters(unsigned char State)
{
	if(msCounter==10)
	{
        
		msCounter=0;

                            if(State == NORMAL_STATE)
                            {
                                 if(csCounter==0)
                                {
                                            if(secCounter==0)
                                            {
                                                
                                            }
                                            else{
                                                 secCounter--;
                                                 csCounter = 99;
                                                 }
                                 }
                                 else 
                                     csCounter--;

                            }
	}
}