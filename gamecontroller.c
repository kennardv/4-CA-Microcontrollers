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
unsigned char ledOn = 0x08;				//Begin waarde moet 1 zijn - als ze allemaal 0 zijn kan er niets geshift worden.
unsigned char terminalByte = 0x55;		//0101 0101

void SimpleFunction(void);	//A simple function: transmit digits 0 to 9 to the terminal device
void RunLight(void);

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
	/*for (a=0;a<5;a++)
	{
		SimpleFunction();
		printf ("\r\n");
	}*/	

	//###3###

	//Main program loop
	a=0;
    while(1)
    {
		RunLight();
		//printf("$SWITCH %d\r\n", SwitchGet());
		printf("%d",terminalByte);
		_delay_ms(200);
    }
}

void SimpleFunction(void)
{
	for (b=0;b<10;b++)
		printf ("%d ",b);
}

void RunLight(void)
{
	if(ledOn == 0x08)							//4de bit actief (led: D4)
	{
		//0000 1000
		ledOn = 0x01;							//1ste bit actief (led: D1)
		//printf("ledOn = 0x01\r\n");
	}
	else
	{
		ledOn = ledOn << 1; 					//Actieve bit links shiften
		//printf("ledOn shifted left\r\n", ledOn);
	}
	
	LEDSet(ledOn);
}