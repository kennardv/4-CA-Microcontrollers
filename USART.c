#include "usart.h"
#include <avr/io.h>
#include <stdio.h>

static int stdio_putchar(char c, FILE * stream);
static int stdio_getchar(FILE *stream);
//Brug tussen drivercode en stdio library. We kunnen zelf functies schrijven die de onderste laag definiëren van de stdio library.
static FILE UsartStdio = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar,_FDEV_SETUP_WRITE);

void USARTInit(void)
{
	//USART_PORT is een macro die in .h geïnitialiseerd is als PORTD of PORTC
	USART_PORT.DIRSET=0b00001000;		//set transmit lijn als output
	USART_PORT.DIRCLR=0b00000100;		//set receive lijn als input
	
	USART.CTRLA=0b00000000;				//set interrupt prioriteit, dit is polled mode (interrupts uitgeschakeld)	
	USART.CTRLB=0b00011000;				//transmitter en receiver ingeschakeld. Double speed communicatie uitgeschakeld (16 USART klokcycli per bit)
	USART.CTRLC=0b00000011;				//asynchrone modus, geen pariteitsbit, 1 stopbit, 8 databits.
	
	//BSEL=983, BSCALE=-7 --> 115200 baud
	//CTRLA + CTRLB(3:0) vormen de 12 bit value voor de baud rate setting. CTRLB(7:4)=baud rate scale factor
	USART.BAUDCTRLA=0xD7;				//1101 0111
	USART.BAUDCTRLB=0x93;				//1001 0011
										//Scale factor=-7, Baud rate=0011 1101 0111 --> 983
	
	//USART.BAUDCTRLA=0xE5;				//BSEL=3301, BSCALE=-5 -->9600 baud
	//USART.BAUDCTRLB=0xBC;
	
	//Brug tussen drivercode en stdio library.
	stdout=&UsartStdio;
	stdin=&UsartStdio;
}

/**
	Verstuur 1 byte over de USART. De data wordt weggeschreven in het USART.DATA register.
	Er wordt gewacht tot de TXCIF flag in USART.STATUS gezet is. (transmit complete interrupt flag).
	Deze wordt gezet als de databyte verzonden is.
	Om klaar te maken voor een volgende datatransfer moeten we de flag manueel op 0 zetten (door een 1 te schrijven)
	--> stdio_getchar(...)
*/
static int stdio_putchar(char c, FILE * stream)
{
	USART.DATA = c;
	while (!(USART.STATUS & 0b01000000));
	USART.STATUS=0b01000000;
	return 0;
}

/**
	Zet de TXCIF flag naar 0 om een nieuwe datatransfer toe te laten.
*/
static int stdio_getchar(FILE *stream)
{
	while (!(USART.STATUS & 0b10000000));
	return USART.DATA;
}
