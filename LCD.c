#include "Includes.h"


void ToggleEpinOfLCD(void)
{
	LCD_E = 1;                // Give a pulse on E pin
	__delay_us(E_Delay);      // so that LCD can latch the
	LCD_E = 0;                // data from data bus
	__delay_us(E_Delay); 	
}


void WriteCommandToLCD(unsigned char Command)  
{
	LCD_RS = 0;				  // It is a command
	
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= (Command&0xF0);  // Write Upper nibble of data
	ToggleEpinOfLCD();		  // Give pulse on E pin	
	
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= ((Command<<4)&0xF0); // Write Lower nibble of data
	ToggleEpinOfLCD();		  // Give pulse on E pin
}


void WriteDataToLCD(char LCDChar)  
{
	LCD_RS = 1;				  // It is data
	
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= (LCDChar&0xF0);  // Write Upper nibble of data
	ToggleEpinOfLCD();		  // Give pulse on E pin	
	
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= ((LCDChar<<4)&0xF0); // Write Lower nibble of data
	ToggleEpinOfLCD();		  // Give pulse on E pin
}


void InitLCD(void)
{ 
	// Firstly make all pins output
	LCD_E  		 		 = 0;   // E  = 0
	LCD_RS  	 		 = 0;   // RS = 0
	LCD_Data_Bus_D4		 = 0;  	// Data bus = 0
	LCD_Data_Bus_D5		 = 0;  	// Data bus = 0
	LCD_Data_Bus_D6		 = 0;  	// Data bus = 0
	LCD_Data_Bus_D7		 = 0;  	// Data bus = 0
	LCD_E_Dir    		 = 0;   // Make Output
	LCD_RS_Dir    	 	 = 0;   // Make Output
	LCD_Data_Bus_Dir_D4  = 0;   // Make Output
	LCD_Data_Bus_Dir_D5  = 0;   // Make Output
	LCD_Data_Bus_Dir_D6  = 0;   // Make Output
	LCD_Data_Bus_Dir_D7  = 0;   // Make Output

  ///////////////// Reset process from datasheet //////////////
   __delay_ms(40);
   
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= 0x30;			  // Write 0x3 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin

   __delay_ms(6);
   
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= 0x30;			  // Write 0x3 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin

   __delay_us(300);
   
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= 0x30;			  // Write 0x3 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin

   __delay_ms(2);
   
	PORTB &= 0x0F;			  // Make Data pins zero
	PORTB |= 0x20;			  // Write 0x2 value on data bus
	ToggleEpinOfLCD();		  // Give pulse on E pin
	
	__delay_ms(2);
  /////////////// Reset Process End ////////////////
	WriteCommandToLCD(0x28);    //function set
	WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
	WriteCommandToLCD(0x01);    //clear display
	WriteCommandToLCD(0x06);    //entry mode, set increment
        //segunda linea
}


void WriteStringToLCD(const char *s)
{
	while(*s)
		WriteDataToLCD(*s++);   // print first character on LCD 
}


void ClearLCDScreenLine2(void)       // Clear the Screen and return cursor to zero position
{
	      // Delay for cursor to return at zero position
   
    WriteCommandToLCD(0xC0);
    __delay_ms(2); 
}

void ClearLCDScreen(void)       // Clear the Screen and return cursor to zero position
{
	WriteCommandToLCD(0x01);    // Clear the screen
	__delay_ms(2);              // Delay for cursor to return at zero position
    
}



// Displays time in HH:MM:SS format
void DisplayTimeToLCD(unsigned int s,  unsigned int cs,unsigned char State )   
{
	ClearLCDScreen();      // Move cursor to zero location and clear screen

	

	if(State == CONFIG_SEC_STATE)
	{
		WriteDataToLCD( ' ' );	// Display Spaces
		WriteDataToLCD( ' ' );		
	}
	else
	{
		WriteDataToLCD( (s/10)+0x30 );	//Display Seconds
		WriteDataToLCD( (s%10)+0x30 );
	}
    //Display ':'
	WriteDataToLCD(':');

	if(State == CONFIG_CSEC_STATE)
	{
		WriteDataToLCD( ' ' );	// Display Spaces
		WriteDataToLCD( ' ' );	
       // WriteDataToLCD( ' ' ); 
	}
	else
	{
		WriteDataToLCD( (cs/10)+0x30 );	//Display mlSeconds
		WriteDataToLCD( (cs%10)+0x30 );
       // WriteDataToLCD( (cs%10)+0x30 );
	}
}

void DisplayAuthorToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen
    WriteDataToLCD( 'T' );	// Display Spaces
    WriteDataToLCD( 'T' );	// Display Spaces
    WriteDataToLCD( ' ' );	// Display Spaces 
    WriteDataToLCD( '2' );	// Display Spaces
    WriteDataToLCD( '0' );	// Display Spaces
    WriteDataToLCD( '1' );	// Display Spaces
    WriteDataToLCD( '7' );	// Display Spaces
		
}

// Displays time in HH:MM:SS format
void DisplayMsgDisparoToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen

    WriteDataToLCD( 'D' );	// Display Spaces
    WriteDataToLCD( 'I' );	// Display Spaces
    WriteDataToLCD( 'S' );	// Display Spaces
    WriteDataToLCD( 'P' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'R' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( '.' );	// Display Spaces
    WriteDataToLCD( '.' );	// Display Spaces
    WriteDataToLCD( '.' );	// Display Spaces
		
}

void DisplayMsgProgramaToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen

    WriteDataToLCD( 'P' );	// Display Spaces
    WriteDataToLCD( 'R' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'G' );	// Display Spaces
    WriteDataToLCD( 'R' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'M' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
		
}

void DisplayMsgLogoToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen

    WriteDataToLCD( 'P' );	// Display Spaces
    WriteDataToLCD( 'I' );	// Display Spaces
    WriteDataToLCD( 'R' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'T' );	// Display Spaces
    WriteDataToLCD( 'E' );	// Display Spaces
    WriteDataToLCD( 'C' );	// Display Spaces
    WriteDataToLCD( 'N' );	// Display Spaces
    WriteDataToLCD( 'I' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'T' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'M' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'S' );	// Display Spaces
 

}	

void DisplayMsgClearToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen

    WriteDataToLCD( 'B' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'R' );	// Display Spaces
    WriteDataToLCD( 'R' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'D' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( ' ' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'K' );	// Display Spaces
		
}

void DisplayMsgRecToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen

    WriteDataToLCD( 'G' );	// Display Spaces
    WriteDataToLCD( 'R' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'B' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'N' );	// Display Spaces
    WriteDataToLCD( 'D' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces

		
}

void DisplayMsgSecToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen

    WriteDataToLCD( 'S' );	// Display Spaces
    WriteDataToLCD( 'E' );	// Display Spaces
    WriteDataToLCD( 'G' );	// Display Spaces
    WriteDataToLCD( 'U' );	// Display Spaces
    WriteDataToLCD( 'N' );	// Display Spaces
    WriteDataToLCD( 'D' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'S' );	// Display Spaces
    WriteDataToLCD( ' ' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'K' );	// Display Spaces
 
		
}

void DisplayMsgCsecToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen
    WriteDataToLCD( 'D' );	// Display Spaces
    WriteDataToLCD( 'E' );	// Display Spaces
    WriteDataToLCD( 'C' );	// Display Spaces
    WriteDataToLCD( 'I' );	// Display Spaces
    WriteDataToLCD( 'M' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
	WriteDataToLCD( 'S' );	// Display Spaces
    WriteDataToLCD( ' ' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'K' );	// Display Spaces
      
}


void DisplayMsgCompletadoToLCD(void)   
{
	ClearLCDScreenLine2();      // Move cursor to zero location and clear screen
    WriteDataToLCD( 'C' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
    WriteDataToLCD( 'M' );	// Display Spaces
    WriteDataToLCD( 'P' );	// Display Spaces
    WriteDataToLCD( 'L' );	// Display Spaces
    WriteDataToLCD( 'E' );	// Display Spaces
    WriteDataToLCD( 'T' );	// Display Spaces
    WriteDataToLCD( 'A' );	// Display Spaces
    WriteDataToLCD( 'D' );	// Display Spaces
    WriteDataToLCD( 'O' );	// Display Spaces
 
}