#include <avr/io.h>
#include "acc.h"

void AccInit(void)
{
		//uit slaapmodus halen :  By placing a high input signal on pin 7 of acc, the device will resume to normal mode of operation.
		// nog iets
		// nog iets
}
unsigned int AccGetXAxisRaw(void)
{
	//gebruik maken van de AnalogGetCh() methode
	
	return 0;
}
unsigned int AccGetYAxisRaw(void)
{
	//gebruik maken van de AnalogGetCh() methode
	return 0;
}
unsigned int AccGetZAxisRaw(void)
{
	//gebruik maken van de AnalogGetCh() methode
	return 0;
}

int AccGetXAxis(unsigned int AccRaw)
{
	return 0;
}

int AccGetYAxis(unsigned int AccRaw)
{
	return 0;
}

int AccGetZAxis(unsigned int AccRaw)
{
	return 0;
}