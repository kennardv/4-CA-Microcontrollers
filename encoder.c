#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"



void EncoderInit(void)
{	
	PORTC.DIRSET = 0b00110000;		//niet zeker		als output zetten 
	
	//PIN is inverted and detected on both edges and with pull-up
	PORTC.PIN4CTRL = 0b01011000; //0 + INVEN(1) + OPC(011 = totem-pole pullup) + ISC(000 = both edges)	p.124
	PORTC.PIN5CTRL = 0b01011000; //INVEN(1) + OPC(011) + ISC(000)
	
	//Pin 4 is used as interrupt on mask0		p.123
	PORTC.INT0MASK = 0b00110000;
	//Pin 5 is used as interrupt on mask1
	//PORTC.INT1MASK = 0b00100000;
	 
	PORTC.INTFLAGS = 0b00000011; // INT1IF + INT0IF			p.131  --> moet dit??
	PORTC.INTCTRL = 0b00001010;	//INT1LVL(10) + INT0LVL(10)µ	p.101
	
	_previousPosition = 3;
}

ISR(PORTC_INT0_vect) //of toch PORTC_INT1_vect
{
	
	int result = (PORTC.IN & 0b00110000) >> 4;
	if(result == 0x00) {
		result = 0;
	} else if (result == 0x01) {
		result = 1;
	} else if (result == 0x02) {
		result = 3;
	} else if (result == 0x03) {
		result = 2;
	}
	
	switch (result) {
		case 0:
			// Result: 0, Prev: 2
			if (_previousPosition == 3)
			{
				_previousPosition = 0;
				RelativePosition++;
			} 
			else if (_previousPosition == 1)
			{
				_previousPosition--;
				RelativePosition--;
			}
			break;
		case 1:
			// Result: 1, Prev: 3
			if (_previousPosition == 0)
			{
				_previousPosition++;
				RelativePosition++;
			} 
			else if (_previousPosition == 2)
			{
				_previousPosition--;
				RelativePosition--;
			}
			break;
		case 2:
			// Result: 2, Prev: 3
			if (_previousPosition == 1)
			{
				_previousPosition++;
				RelativePosition++;
			}
			else if (_previousPosition == 3)
			{
				_previousPosition--;
				RelativePosition--;
			}
			break;
		case 3:
			// Result: 3, Prev: 1
			if (_previousPosition == 2)
			{
				_previousPosition++;
				RelativePosition++;
			}
			else if (_previousPosition == 0)
			{
				_previousPosition = 3;
				RelativePosition--;
			}
			break;
	}
}

/*ISR(PORTC_INT1MASK)	//of toch PORTC_INT1_vect?
{
	
}*/


int EncoderGetPos(void)
{
	//int positie = 0;
	// terugeven van encoder positie
	
	return RelativePosition;
}