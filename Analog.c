#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	//initialisatie met referentiebron interne spanningreferentie van 1V
	
	//set reference to internal 1V reference
	ADCA.REFCTRL=0x02;							//Setting this bit enables the bandgap for ADC measurement
	//enable the ADC
	ADCA.CTRLA=0x01;
	// default settings for resolution and conversion mode
	ADCA.CTRLB=0;
	
	//prescaler ADC!!!!!!!!!
	ADCA.PRESCALER = 0b00000001;						//define the ADC clock relative to the peripheral clock
	
	
	//deze registers moet ge denk ik setten maar weet niet of de waarden juist zijn
}
int AnalogGetCh(int PinPos,int PinNeg)
{
	//p.257 voor registers
	
	 //ADCA.CTRLA = 
	 //ADCA.CTRLB=
	 //ADCA.CH0.CTRL  =
	 //ADCA.CH0.MUXCTRL =
	 ADCA.CH0.INTFLAGS = 0b00000001;		//set flag is set when the ADC conversion is complete
	 
	 //return ADCA.CH0.RES = 
	
	
	return;
}