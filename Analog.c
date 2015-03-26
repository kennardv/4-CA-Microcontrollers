#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	//set reference to internal 1V reference
	ADCA.REFCTRL=0b00000010;		//Setting this bit enables the bandgap for ADC measurement
	//enable the ADC
	ADCA.CTRLA=0b00000001;
	// default settings for resolution and conversion mode
	//DIV8
	ADCA.CTRLB=0b00000100;
	
	//prescaler ADC!!!!!!!!!
	ADCA.PRESCALER = 0b00000010;	//define the ADC clock relative to the peripheral clock. DIV16
}
int AnalogGetCh(int PinPos,int PinNeg)
{
	//Config with parameters
	ADCA.CH0.MUXCTRL = (PinPos & 0x0F) << 3;
	ADCA.CH0.MUXCTRL = (PinNeg & 0x0F); //| (PinNeg & 0x07);
	
	//Start meting (NO freerun)
	ADCA.CTRLA = (0b00000100 | ADCA.CTRLA);
	
	//Wait for measure result
	while(ADCA.CH0.INTFLAGS != 0b00000001) { }	//set flag is set when the ADC conversion is complete
	ADCA.CH0.INTFLAGS = 0xFF;
	//Get result
	return ADCA.CH0RES;
}