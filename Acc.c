#include <avr/io.h>
#include "acc.h"

void AccInit(void)
{
		//uit slaapmodus halen :  By placing a high input signal on pin 7 of acc, the device will resume to normal mode of operation.
		// --> ACC-sleep : PC6
		//Poorten acc X, Y , Z staan op PA0 , PA1 en PA2 + GDN op PA4
		
		//PORTA.DIRCLR= 0b11110001;			//Set Input
		
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