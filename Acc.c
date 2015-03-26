#include <avr/io.h>
#include "acc.h"

void AccInit(void)
{
		AnalogInit();
		//uit slaapmodus halen :  By placing a high input signal on pin 7 of acc, the device will resume to normal mode of operation.
		// --> ACC-sleep : PC6
		
		//set sleep pin of accelerometer
		PORTC.OUT&=0b01000000;			//set PC6 high
		PORTC.DIRSET=0b01000000;		//set PC6 as output (output = 1, input = 0)
		
		
		//Poorten acc X, Y , Z staan op PA0 , PA1 en PA2 + GDN op PA4
		
		//PORTA.DIRCLR= 0b11110001;			//Set Input
		
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