#include "Main.h"
PWM pwm;

int main( void )
{
	peiph_init();
	lcd_init();
	
	sei();
	
	pwm.set_mode_pwm(PWM::CTC);
	while(1)
	{
			
	}
}

bool push_button (const uint8_t PINX, const uint8_t pin_number, Button &but)
{
	if (!(PINX & 1<<pin_number))
		but.detect = true;
	else
		if ((but.detect == true) && !(but.time ? but.time-- : 0))
		{
			but.time = 70;
			but.detect = false;
			return true;
		}
	return false;
}
