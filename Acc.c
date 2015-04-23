#include <avr/io.h>
#include "acc.h"

#define SCALE_FACTOR	//nog uitrekenen door testen
#define CALL_OFFSET		//nog uitrekenen door testen

void AccInit(void)
{
		AnalogInit();
		//uit slaapmodus halen :  By placing a high input signal on pin 6 of acc, the device will resume to normal mode of operation.
		// --> ACC-sleep : PC6
		
		//set sleep pin of accelerometer
		PORTC.OUT |= 0b01000000;			//set PC6 high		//of |= PIN6_bm
		PORTC.DIRSET = 0b01000000;		//set PC6 as output (output = 1, input = 0S) ---- 0x40
			
}
unsigned int AccGetXAxisRaw(void)
{
	//gebruik maken van de AnalogGetCh() methode
	return AnalogGetCh(0, 4);
}
unsigned int AccGetYAxisRaw(void)
{
	//gebruik maken van de AnalogGetCh() methode
	return AnalogGetCh(1, 4);
}
unsigned int AccGetZAxisRaw(void)
{
	//gebruik maken van de AnalogGetCh() methode
	return AnalogGetCh(2, 4);
}

int AccGetXAxis(unsigned int AccRaw)
{
	long result;
	//result = ((long) AccRaw - CALL_OFFSET));
	result  *1000;
	//result = result / SCALE_FACTOR;
	return (int) result;
	
}

int AccGetYAxis(unsigned int AccRaw)
{
	//hetzelfde als x-as;
	return 0;
}

int AccGetZAxis(unsigned int AccRaw)
{
	//hetzelfde als x-as
	return 0;
}