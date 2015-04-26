#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"

void EncoderInit(void)
{
	//pc5 en 5 voor 2 ind interrupts op willekeurige flank
	//PORTC.PIN4CTRL = 0b00000000;		//totempole / sense on tboth edges
	//PORTC.PIN5CTRL = 0b00000000;		//totempole / sense on tboth edges
	
	//---------------------------------------------------------------------- > hieronder probeersel
	
	PORTC.PIN4CTRL = 0b01011001; //INVEN(1) + OPC(011) + ISC(000)
	PORTC.PIN5CTRL = 0b01011001; //INVEN(1) + OPC(011) + ISC(000)
	
	//PIN is inverted and detected on both edges and with pull-up
	PORTC.INT0MASK = 0b00010000;
	//Pin 4 is used as interrupt on mask0
	PORTC.INT1MASK = 0b00100000;
	//Pin 5 is used as interrupt on mask1
	
	//PORTC.INTFLAGS = 0b00000011; // INT1IF + INT0IF
	PORTC.INTCTRL = 0b00001010;	//INT1LVL(10) + INT0LVL(10)µ
	
	//ISR schrijven + globale variabele (volatile)
	
	
}
int EncoderGetPos(void)
{

	// terugeven van encoder positie
	return 0;
}