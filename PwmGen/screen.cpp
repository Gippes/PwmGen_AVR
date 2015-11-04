#include "screen.h"

extern PWM pwm;
extern States state;
extern uint16_t coeff;

bool screen_refresh()
{
	uint32_t tmp;
	const uint16_t div = pwm.get_prescaler_value();
	double tmpL;
	char buff[5];
		
	
	lcd_clrscr();
	lcd_goto(0);
	switch(state.pwm_mode)
	{
		case 0: 
			sprintf(buff,"CTC +%u F/%u ",coeff, div);
			lcd_puts(buff);			
			lcd_goto(40);
			tmp = OCR1AH<<8 | OCR1AL;						
			tmpL = 2000 * (tmp+1);
			if (tmpL <= F_CPU/div)	
			{
				tmpL = F_CPU / (tmpL*div);
				sprintf(buff,"Frq: %0.3f",tmpL);
				lcd_puts(buff);
				lcd_puts("KHz");
			}
			else
			{
				if(!(tmp = F_CPU/(2*div*(tmp+1))))
					tmp = 1;				
				sprintf(buff,"Frq: %lu", tmp);
				lcd_puts(buff);
				lcd_puts("Hz");
			}
			
		
			
		break;	
		case 1:	lcd_puts("Fast PWM "); lcd_goto(40); lcd_puts("Freq: ");		break;
		case 2:	lcd_puts("Phase Corr. PWM "); lcd_goto(40); lcd_puts("Freq: ");	break;
	}
	
		return true;
}