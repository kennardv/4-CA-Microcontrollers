#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"

volatile int Vorigepositie;		//De waarde kan veranderen tussen verschillende opvragingen
volatile int Relatievepositie;

void EncoderInit(void)
{
	//pc5 en 5 voor 2 ind interrupts op willekeurige flank
	//PORTC.PIN4CTRL = 0b00000000;		//totempole / sense on tboth edges
	//PORTC.PIN5CTRL = 0b00000000;		//totempole / sense on tboth edges
	
	//---------------------------------------------------------------------- > hieronder probeersel
	PORTC.DIRSET = 0b00110000;		//niet zeker		als output zetten 
	
	//PIN is inverted and detected on both edges and with pull-up
	PORTC.PIN4CTRL = 0b01011001; //0 + INVEN(1) + OPC(011 = totem-pole pullup) + ISC(000 = both edges)	p.124
	PORTC.PIN5CTRL = 0b01011001; //INVEN(1) + OPC(011) + ISC(000)
	
	//Pin 4 is used as interrupt on mask0		p.123
	PORTC.INT0MASK = 0b00110000;
	//Pin 5 is used as interrupt on mask1
	//PORTC.INT1MASK = 0b00100000;
	 
	//PORTC.INTFLAGS = 0b00000011; // INT1IF + INT0IF			p.131  --> moet dit??
	PORTC.INTCTRL = 0b00001010;	//INT1LVL(10) + INT0LVL(10)�
	
	//ISR schrijven + globale variabele (volatile)
	
}

ISR(PORTC_INT0MASK) //of toch PORTC_INT1_vect
{
	int result = (PORTC.IN & 0b00110000) >> 4;
	
	//switch case
	//if
	//else
	//00 , 01 , 10 , 11
	switch (result) {
		case 00:
			// Result: 0, Prev: 2
			if ((result + Vorigepositie) % 4 == 2)
			{
				Relatievepositie = 3;
			} 
			else
			{
				Relatievepositie++;
			}
			break;
		case 01:
			// Result: 1, Prev: 3
			if ((result + Vorigepositie) % 4 == 0)
			{
				Relatievepositie--;
			} 
			else
			{
				Relatievepositie++;
			}
			break;
		case 10:
			// Result: 2, Prev: 3
			if ((result + Vorigepositie) % 4 == 1)
			{
				Relatievepositie--;
			}
			else
			{
				Relatievepositie = 0;
			}
			break;
		case 11:
			// Result: 3, Prev: 1
			if ((result + Vorigepositie) % 4 == 0)
			{
				Relatievepositie--;
			}
			else
			{
				Relatievepositie++;
			}
			break;
	}
	
	
	Vorigepositie = result;
}

ISR(PORTC_INT1MASK)	//of toch PORTC_INT1_vect?
{
	
}


int EncoderGetPos(void)
{
	//int positie = 0;
	// terugeven van encoder positie
	
	return Relatievepositie;
}