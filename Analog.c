#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	//initialisatie met referentiebron interne spanningreferentie van 1V
	
	//set reference to internal 1V reference
	ADCA.REFCTRL=0x02;
	//enable the ADC
	ADCA.CTRLA=0x01;
	// default settings for resolution and conversion mode
	ADCA.CTRLB=0;
	
	//prescaler ADC!!!!!!!!!
	//ADCA.PRESCALER = iets :p
	
	//deze registers moet ge denk ik setten maar weet niet of de waarden juist zijn
}
int AnalogGetCh(int PinPos,int PinNeg)
{
	//p.257 voor registers
	
	 //ADCA.CTRLA = 
	 
	 //ADCA.CH0.CTRL  =
	 //ADCA.CH0.MUXCTRL =
	 //ADCA.CH0.INTFLAGS = 
	 
	 //return ADCA.CH0.RES = 
	
	
	return;
}