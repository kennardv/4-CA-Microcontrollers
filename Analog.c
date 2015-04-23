#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void)
{
	PORTA.DIRCLR=PIN0_bm;		//0x01
	PORTA.DIRCLR = PIN1_bm;		//0x02
	PORTA.DIRCLR = PIN2_bm;		//0x04
	PORTA.DIRCLR = PIN3_bm;		//0x08
	PORTA.DIRCLR = PIN4_bm;		//0x10
	
	//set reference to internal 1V reference
	ADCA.REFCTRL=ADC_BANDGAP_bm;		// of = ADC_BANDGAP_bm		//Setting this bit enables the bandgap for ADC measurement
	
	//enable the ADC
	ADCA.CTRLA=ADC_ENABLE_bm;			 // of = ADC_ENABLE_bm
	
	// default settings for resolution and conversion mode, use 12-bit ad conversion, signed/unsigned is selected at each conversion
	// NOT -> 1110 1111 ---- bit 4 = conversion mode -> 0 = unsigned, 1 = signed (p. 258)
	ADCA.CTRLB &= ADC_CONMODE_bm;
	
	//configure prescaler ADC
	ADCA.PRESCALER = ADC_PRESCALER_DIV16_gc;	//of = 	ADC_PRESCALER_DIV16_gc (zijn al variabelen die aangemaakt zijn --> zoveel makkelijker!	//define the ADC clock relative to the peripheral clock. DIV16 --> moet kleiner zijn als 1,4 Mhz
	
}

//Get analog channel value
//PinPos:
	//Differential mode: positive input pin (0 to 15)
	//Single ended mode: input pin (0 to 15)
//PinNeg:
	//Differential mode: negative input pin (0 to 7)
	//Single ended mode: write '-1' to select single ended mode
//Return value:
	//-2048 to 2047 (signed) or 0 to 4095 (unsigned)
	//10000: Invalid pin settings

int AnalogGetCh(int PinPos,int PinNeg)
{
	int result=0;
	
	//Config with parameters
	
	//single ended mode --> zie uitleg boven methode
	if(PinPos <=15 && PinNeg==-1 ) 
	{
		//clear bit 4 of CTRL register to set conversion mode to unsigned
		//ADCA.CTRLB &= ~ADC_CONMODE_bm;		//0x10	-->niet zeker van dit!!!	Bitwise AND + Bitwise NOT : ~ (Bits that are 0 become 1, and those that are 1 become 0)
		//configure single ended mode for unsigned mode (and set no gain)
		ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;		//0x01 <<0
		//select input on inputmux
		ADCA.CH0.MUXCTRL = (PinPos)<<3;	//MUX_NEG will be set to 0		//bitwise shift left
	}
	
	//differential mode 
	else if (PinPos<=15 && PinNeg<=7)	//pinpos <=7??
	{
		//set bit 4 of CTRL register to set conversion mode to signed
		ADCA.CTRLB|=ADC_CONMODE_bm;
		//configure differential mode with gain ()for signed mode
		ADCA.CH0.CTRL=ADC_CH_INPUTMODE_DIFFWGAIN_gc;		//0x03<<0	--> gain = 1
		//select inputs on inputmux
		ADCA.CH0.MUXCTRL = (PinPos)<<3 | (PinNeg-4);
	}
	// invalid pin settings
	else
		result =  100000;
	
	
	//Start meting (NO freerun)
	ADCA.CTRLA = (0b00000100 | ADCA.CTRLA);		// of |= ADC_CH0START_bm
	
	//Wait until conversion / for measure result		//op CH0 of algemene flagss??
	while(ADCA.CH0.INTFLAGS != 0x01) { }	//set flag is set when the ADC conversion is complete
	ADCA.CH0.INTFLAGS = 0x01;
	
	//Get result
	result =  ADCA.CH0RES;
	
	// return result
	return result;
}