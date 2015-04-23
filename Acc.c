#include <avr/io.h>
#include "acc.h"

#define SCALE_FACTOR_X 300
#define CALL_OFFSET_X 900
#define SCALE_FACTOR_Y 800
#define CALL_OFFSET_Y 945
#define SCALE_FACTOR_Z 1600
#define CALL_OFFSET_Z 1120

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
	result = (long) AccRaw - CALL_OFFSET_X;
	result *= 1000;
	result = result / SCALE_FACTOR_X;
	return (int) result;
}

int AccGetYAxis(unsigned int AccRaw)
{
	long result;
	result = (long) AccRaw - CALL_OFFSET_Y;
	result *= 1000;
	result = result / SCALE_FACTOR_Y;
	return (int) result;
}

int AccGetZAxis(unsigned int AccRaw)
{
	long result;
	result = (long) AccRaw - CALL_OFFSET_Z;
	result *= 1000;
	result = result / SCALE_FACTOR_Z;
	return (int) result;
}