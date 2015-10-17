#ifndef PERIODIC_H_
#define PERIODIC_H_

#include "Main.h"
struct States
{
	uint8_t	prescaller	:3;
	uint8_t	coeff		:3;
	uint8_t	pwm_mode	:3;
};

struct Encoder
{
	bool	detect;
	bool	init;
	uint8_t delay;
};

ISR(TIMER0_COMP_vect);

#endif