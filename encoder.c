#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"

void EncoderInit(void)
{
	//pc5 en 6 voor 2 ind interrupts op willekeurige flank
	//ISR schrijven + globale variabele (volatile)
}
int EncoderGetPos(void)
{
	// terugeven van encoder positie
	return;
}