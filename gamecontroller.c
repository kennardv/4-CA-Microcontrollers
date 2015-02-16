#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Clock.h"
#include "USART.h"
#include "Analog.h"
#include "acc.h"
#include "LED.h"
#include "switch.h"
#include "encoder.h"
#include "speaker.h"


unsigned char a,b;

void SimpleFunction(void);	//A simple function: transmit digits 0 to 9 to the terminal device

int main(void)
{	
	//###1###
	 
	//Initialize subsystems
	ClockInit();			//Initialize system clock (16 MHz)
	USARTInit();			//Initialize USART and bind to stdout,stdin
	AnalogInit();			//Initialize ADC
	AccInit();				//Initialize accelerometer system
	LEDInit();				//Initialize LEDs
	SwitchInit();			//Initialize switches
	EncoderInit();			//Initialize encoder
	SpeakerInit();			//Initialize speaker system
	
	//Enable interrupts
	PMIC.CTRL|=0b00000111;  //Enable low, medium, high priority interrupts
	SREG|=0b10000000;		//Globale interrupt enable


	//###2###	
	
	//Print the digits 0 to 9 5x on terminal device
	//Reason this section didn't work:
	//Omdat dezelfde teller a op verschillende plaatsen wordt gebruikt.
	//Oplossing: b moet als counter voor SimpleFunction gebruikt worden.
	for (a=0;a<5;a++)
	{
		SimpleFunction();
		printf ("\r\n");
	}	

	//###3###

	//Main program loop
	a=0;
    while(1)
    {
		printf ("Counter:%d\r\n",a);
		_delay_ms(500);
		a++;
    }
}

void SimpleFunction(void)
{
	for (b=0;b<10;b++)
		printf ("%d ",b);
}