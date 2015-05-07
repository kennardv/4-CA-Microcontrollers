#ifndef ENCODER_H_
#define ENCODER_H_

void EncoderInit(void);		//Initialize encoder system
int EncoderGetPos(void);		//Get encoder status as 16 bit integer

//De waarde kan veranderen tussen verschillende opvragingen
volatile int RelativePosition;
volatile int _previousPosition;

#endif 