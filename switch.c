#include "switch.h"
#include <avr/io.h>

void SwitchInit(void)
{
	PORTD.DIRCLR= 0b11110001;			//Set Input pins
	PORTD.PIN0CTRL= 0b01011001;		//6: invert, 5-3: output conf: pull up, 2-0: input conf: rising edge
	PORTD.PIN4CTRL= 0b01011001;
	PORTD.PIN5CTRL= 0b01011001;
	PORTD.PIN6CTRL= 0b01011001;
	PORTD.PIN7CTRL= 0b01011001;
}


char SwitchGet(void)
{
	char switchInput = (PORTD.IN & 0xF0) >> 3;	//Schuif PD7-PD4 naar PD4-PD1 - center is aangesloten op PD0, de rest op PD4-7. We shiften de rest 3 plaatsen terug
	return switchInput | (PORTD.IN & 0x01);		//AND operator om enkel PD0 waarde te behouden, daarna OR om geshifte PD7-4 erbij te tellen.
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                