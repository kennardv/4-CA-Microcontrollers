#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"

void EncoderInit(void)
{
	//pc5 en 6 voor 2 ind interrupts op willekeurige flank
	PORTC.PIN4CTRL = 0b00000000;
	PORTC.PIN5CTRL = 0b00000000;
	//ISR schrijven + globale variabele (volatile)
}
int EncoderGetPos(void)
{
	// terugeven van encoder positie
	return 0;
}