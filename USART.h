#ifndef USART_H
#define USART_H


#define USART USARTC0
#define USART_PORT PORTC
//#define USART USARTD0
//#define USART_PORT PORTD

void USARTInit(void); //Initialize USART, bind to stdin,stdout

#endif