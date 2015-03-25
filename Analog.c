#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	//set reference to internal 1V reference
	ADCA.REFCTRL=0x02;							//Setting this bit enables the bandgap for ADC measurement
	//enable the ADC
	ADCA.CTRLA=0x01;
	// default settings for resolution and conversion mode
	 ADCA.CTRLB = 0b00010000;       //6-5: Current Limit (no limit), 4: Conversion mode : 0 = unsigned , 1 = signed, 3: Freerun , 2-1: Resolution: 00 = 12 bits rechts
	
	//define the ADC clock relative to the peripheral clock
	ADCA.PRESCALER = 0b00000010;	//00000010	//2-0: Prescaler (Divider 16) : 16Mhz -> 1Mhz				
	
	
	//deze registers moet ge denk ik setten maar weet niet of de waarden juist zijn
}
int AnalogGetCh(int PinPos,int PinNeg)
{
	//p.257 voor registers
	
	
	PinNeg = PinNeg - 4; //PA4 = 0, PA5 = 1,...
	//ook wrs voor PinPos
	 //ADCA.CH0.CTRL  = 0b000.....;
	ADCA.CH0.MUXCTRL = 0b00000010;
	 
	 ADCA_CH0_MUXCTRL = ((PinNeg & 0x0F) << 3) | (PinNeg & 0x07); //Selecteer de samplepoorten 
	 
	 ADCA.CH0.INTFLAGS = 0b00000001;		//set flag is set when the ADC conversion is complete
	 
	 //return ADCA.CH0.RES = 
	
	
	return;
}