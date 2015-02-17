#include "LED.h"
#include <avr/io.h>

void LEDInit(void)
{
	PORTE.DIRSET= 0b00001111;	//set output
	PORTE.PIN0CTRL= 0b01010001	//6: invert, 5-3: output conf: pull down, 2-0: input conf: rising edge
	PORTE.PIN1CTRL= 0b01010001
	PORTE.PIN2CTRL= 0b01010001
	PORTE.PIN3CTRL= 0b01010001
	
}
void LEDSet(char bitmask)
{
	//and-functie om enkel eerste 4 bits over te houden (B0 --> B3)
	//bitmask:		0110 0101
	//				0000 1111
	//bitmask -->	0000 0101
	bitmask	= bitmask & 0x0F;				
	
	//behoud laatste 4 bits van register (B4 --> B7) en voeg eerste 4 bits van bitmask toe (B0 --> B3)	
	//OUT:			1100 0110
	//&				1111 0000
	//OUT -->		1100 0000 laatste 4 bits onthouden
	//|				0000 0101
	//OUT -->		1100 0101 originele OUT en bitmask samengevoegd
	PORTE.OUT= (PORTE.OUT & 0xF0) | bitmask;
}