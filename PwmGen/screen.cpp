#include "screen.h"

extern States state;
extern uint16_t coeff;

bool screen_refresh()
{
	lcd_clrscr();
	lcd_goto(0);

	uint32_t tmp;
	double tmpL;	
	char buff[5];
	switch(state.pwm_mode)
	{
		case 0: 
			lcd_puts("CTC "); 

			sprintf(buff," x%u",coeff);
			lcd_puts(buff);			
			
			lcd_goto(40); 
			lcd_puts("Freq: ");
			lcd_goto(46);
			
			tmp = OCR1AH<<8 | OCR1AL;			
			tmpL = 2000 * (tmp+1);
			if (tmpL <= F_CPU)	
			{
				tmpL = F_CPU/tmpL;
				sprintf(buff,"%0.3f",tmpL);
				lcd_puts(buff);
				lcd_puts("KHz");
			}
			else
			{
				sprintf(buff,"%u",(uint16_t)(F_CPU/(2 * (tmp+1))));
				lcd_puts(buff);
				lcd_puts("Hz");
			}
			
		
			
		break;	
		case 1:	lcd_puts("Fast PWM "); lcd_goto(40); lcd_puts("Freq: ");		break;
		case 2:	lcd_puts("Phase Corr. PWM "); lcd_goto(40); lcd_puts("Freq: ");	break;
	}
	
		return true;
}