
#include "Includes.h"

// Configuration word for PIC16F877A
#include <xc.h>
// Main Function
void main(void)
{
	unsigned char State = NORMAL_STATE;	// To store current state  
    unsigned char AuthorTT = Author;
    unsigned char Logo = MsgLogo;
    unsigned char MesaPrograma = MsgPrograma;
    unsigned char MesaDispara = MsgDispara;
    unsigned char BorrrMemo = MsgClear;
    unsigned char GuardarMemo = MsgRec;
    unsigned char DigitoSec = MsgSec;
    unsigned char DisgitoCsec = MsgCsec;
    unsigned char MesaFuego = MsgFuego;
    unsigned char MesaCompletado = MsgCompletado;
    TRISA =  0x3f;
    ADCON1 = 0x07;
    TRISC = 0;
    TRISD = 0;
    PORTC = 0;
    PORTD = 0;
    PORTA = 0;
	TRISD0 = 0;						// Make RD0 pin an output
	RD0	= 0;						// Make RD0 zero
    RD1 = 0;
    RD2 = 0;
    RD3 = 0;
    RD4 = 0;
    RD5 = 0;
    RD6 = 0;
    RD7 = 0;
    RC0 = 0;
    RC1 = 0;
    RC2 = 0;
    RC3 = 0;
    RC4 = 0;
    RC5 = 0;
    RC6 = 0;
    RC6 = 0;
	TRISE  = 0x07;					// PORTE is used for inputs
	ADCON1 = 0x07;					// Disable ADC to make PORTE pins 
									// as digital IO pins
	
	InitLCD();						// Initialize LCD in 4bit mode
	Init1msecTimerInterrupt();		// Start 1 msec timer

	while(1)
	{
       
      
       if(!RA0)	///////////////// MODO PROGRAMA SWICHT RA0 NIVEL  BAJO
		{ 
                ////Msg Logo 
           if (AuthorTT == 1){DisplayAuthorToLCD(); __delay_ms(100); AuthorTT = 0; }
           if (Logo == 1){DisplayMsgLogoToLCD(); __delay_ms(300); Logo = 0; }
           
               /// Msg Modo Dispara
           if (MesaPrograma == 1){DisplayMsgProgramaToLCD();  __delay_ms(300);}    
           
              /// Lee eeprom interna y carga las variables csCounter secCounter
           ReadEeprom();
           UpdateTimeCounters(State); 
             
           /// borrado de memoria 
        if(!RA2){ClearMemo();DisplayMsgClearToLCD();  __delay_ms(300); }
           
      
            
		if(State == NORMAL_STATE)
		{
			if(!RE0)				// si se pulso grabando
			{   
                DisplayMsgRecToLCD(); __delay_ms(300); // mensaje recording
				State = CONFIG_SEC_STATE;	// cambio de estado para programar

				while(!RE0)			//antirebote
                    
					UpdateTimeCounters(State);// actualizar counters
			}

			 
        }
		else					// If state is not NORMAL_STATE
		{
                       
			if(!RE1)			// If Up button pressed
			{
               
				while(!RE1)		// antirebote
					UpdateTimeCounters(State);//   updating   counters

				switch(State)	// Increment counter
				{
                    
                case CONFIG_CSEC_STATE: if(csCounter==99)
											csCounter = 0;
										else
											csCounter++;
										break;            
				case CONFIG_SEC_STATE:	if(secCounter==59)
											secCounter = 0;
										else
											secCounter++;
										break;

				}
			}
			else if(!RE2)		// If Down button pressed
			{

				while(!RE2)		//  antirebote

					UpdateTimeCounters(State);// Keep updating time counters

				switch(State)	// Decrement counter
				{
                case CONFIG_CSEC_STATE:	if(csCounter==0)
											csCounter = 99;
										else
											csCounter--;
                                        break;
				case CONFIG_SEC_STATE:	if(secCounter==0)
											secCounter = 59;
										else
											secCounter--;
										break;

				}
			}
			else if(!RE0)		// If grabando se sigue pulsando
			{
             
                  
				while(!RE0)		//antirebote
					UpdateTimeCounters(State);//   updating   counters

				switch(State)	// switch para los 2 digitos segundos decimas
				{ 
				case CONFIG_SEC_STATE:	State = CONFIG_CSEC_STATE;
                 DisplayMsgSecToLCD();  __delay_ms(300);   
                
                  break;
                  
                case CONFIG_CSEC_STATE: State = NORMAL_STATE;
                  DisplayMsgCsecToLCD(); __delay_ms(300);
                  break;
				}				              
                
			}	
		}
           
            // Update counters
		    UpdateTimeCounters(State);       	 
			// Display time  
			DisplayTimeToLCD( secCounter,csCounter, NORMAL_STATE);
            // escribe en la eeprom interna
		    WriteEeprom();
		    
           
           
           
        } //fin if(!RA0)	 botton programa
       
       if(RA0)	///////////////// MODO DISPARO SWICHT RA0 NIVEL  ALTO
		{ 
             DisplayMsgDisparoToLCD();
             __delay_ms(50);
             
             ReadEeprom();
             DisplayTimeToLCD( secCounter,csCounter, NORMAL_STATE); 
             __delay_ms(50);
             
         if (RA1)//pulso dispara secuencia
          {
             State = NORMAL_STATE;
             ReadEeprom();  
             while(RC0 == 0 )
                {              
                RC0 = 1;                
				}
                          

             while(State == NORMAL_STATE && RC1 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC1 = 1; RC0=0; State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RC2 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC2 = 1; RC1=0; State = NORMAL_STATE; ReadEeprom();   }
				}                          

             while(State == NORMAL_STATE && RC3 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC3 = 1; RC2=0; State = NORMAL_STATE; ReadEeprom();  }
				}             

             while(State == NORMAL_STATE && RC4 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC4 = 1; RC3=0; State = NORMAL_STATE; ReadEeprom();  }
				}             

             while(State == NORMAL_STATE && RC5 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC5 = 1; RC4=0; State = NORMAL_STATE; ReadEeprom();  }
				}

             while(State == NORMAL_STATE && RC6 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC6 = 1; RC5=0; State = NORMAL_STATE; ReadEeprom();  }
				}             

             while(State == NORMAL_STATE && RC7 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC7 = 1; RC6=0; State = NORMAL_STATE; ReadEeprom();  }
				}
             
             
            while(State == NORMAL_STATE && RD0 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD0 = 1; RC7=0; State = NORMAL_STATE; ReadEeprom();  }
				}
            
            while(State == NORMAL_STATE && RD1 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD1 = 1; RD0=0; State = NORMAL_STATE; ReadEeprom();  }
				}
             
            while(State == NORMAL_STATE && RD2 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD2 = 1; RD1=0; State = NORMAL_STATE; ReadEeprom();  }
				}
             
             while(State == NORMAL_STATE && RD3 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD3 = 1; RD2=0; State = NORMAL_STATE; ReadEeprom();  }
				}
             
             while(State == NORMAL_STATE && RD4 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD4 = 1; RD3=0; State = NORMAL_STATE; ReadEeprom();  }
				}
             
             while(State == NORMAL_STATE && RD5 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD5 = 1; RD4=0; State = NORMAL_STATE; ReadEeprom();  }
				}
             
             while(State == NORMAL_STATE && RD6 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD6 = 1; RD5=0; State = NORMAL_STATE; ReadEeprom();  }
				}
                          
             while(State == NORMAL_STATE && RD7 == 0 )
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD7 = 1; RD6=0; State = NORMAL_STATE; ReadEeprom();  }
				}
             
                          
             while(RD7 == 1) ///descativamos todas las salidas
                {              
                 DisplayMsgCompletadoToLCD();
                 __delay_ms(300);
                 UpdateTimeCounters(State); 
                 DisplayMsgDisparoToLCD;
                 RD7 = 0; PORTC = 0x00; PORTD = 0x00;  
				}             
                           
             
             
             

             
             
             
          }
         
        } //fin if(RA0)
      
       
       
  	}//fin while(1)
}//fin void main(void)

