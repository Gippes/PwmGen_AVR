#include "periodic.h"

#define LED_FLASHING PORTD ^= BIT4

extern PWM	pwm;
uint16_t coeff = 1;
States state = {0,0,0};
Button freq_div = {0,70};
Button mult_div = {0,70};
Button pwm_mode_select = {0,70};
Encoder enc = {0,0,0};

/* Диспетчер */
ISR(TIMER2_COMP_vect)
{
	TCNT0 = 0;
	//делитель clk
	if(push_button(PIND, 6, freq_div))
	{
		if(state.prescaller > 4)
			state.prescaller = 0;
		pwm.set_prescaler(state.prescaller++);
	}
	
	//коэфф. инкремента 
	if (push_button(PIND, 3, mult_div))
	{
		if(state.coeff > 4)
			state.coeff = 0;
		switch(state.coeff++)
		{
			case 0: coeff = 1;		break;
			case 1: coeff = 10;		break;
			case 2: coeff = 100;	break;
			case 3: coeff = 1000;	break;
		}
	}
	
	if(push_button(PIND, 2, pwm_mode_select))
	{
		if(state.pwm_mode > 2)
			state.pwm_mode = 0;
		lcd_clrscr();
		lcd_goto(0);
		switch(state.pwm_mode++)
		{
			case 0: pwm.set_mode_pwm(PWM::CTC);		lcd_puts("CTC "); lcd_goto(40); lcd_puts("Freq: ");		break;
			case 1: pwm.set_mode_pwm(PWM::FAST_PWM);	lcd_puts("Fast PWM "); lcd_goto(40); lcd_puts("Freq: ");	break;
			case 2: pwm.set_mode_pwm(PWM::PHASE_CORRECT);	lcd_puts("Phase Corr. PWM "); lcd_goto(40); lcd_puts("Freq: ");	break;
			//case 3: pwm.set_mode_pwm(PWM::PHASE_FREQ_CORRECT);	lcd_puts(" "); lcd_goto(4);	break;
		}
	}
	
	//проверка энкодера
	if((!(PINA & BIT1) || !(PINA & BIT2)) || (enc.detect == true))
	{
		if(enc.init == false)
		{
			enc.detect = true;
			char buff[5];
			uint16_t tmp = OCR1AH<<8 | OCR1AL;
			
			if(PINA & BIT1)
			{
				if(coeff <= 0xFFFF - tmp)
				{
					tmp += coeff;
					OCR1AH = (uint8_t)(tmp>>8);
					OCR1AL = (uint8_t)tmp;
				}
				else
				{
					OCR1AH = 0xFF;
					OCR1AL = 0xFF;
				}
			}
			else
			{	
				if(tmp >= coeff)
				{
					tmp -= coeff;
					OCR1AH = (uint8_t)(tmp>>8);
					OCR1AL = (uint8_t)tmp;
				}
				else
				{
					OCR1AH = 0x00;
					OCR1AL = 0x00;
				}
			}
			
			lcd_goto(46);
			tmp = OCR1AH<<8 | OCR1AL;
			switch (state.pwm_mode - 1)
			{
				case 0: uint32_t tmpL = F_CPU / (2000 * (tmp+1)); 
						utoa(tmpL,buff,10);
						lcd_puts(buff);
						lcd_puts(" KHz");
						if (tmpL < 1)
						{
							tmpL = F_CPU/(2 * (tmp+1));
							utoa(tmpL,buff,10);
							lcd_puts(buff);
							lcd_puts(" Hz");
						}
						break; 
			}										
			
								
			enc.delay = 10;
			enc.init = true;
		}
		if((PINA & BIT1) && (PINA & BIT2) && !(enc.delay ? --enc.delay : 0))
		{
			enc.detect = false;
			enc.init = false;
		}
	}
	

	// запуск преобразований ADC
	if(!(ADCSRA & 1<<ADSC))
	{	
								
	}
	ADCSRA |= 1<<ADSC;					
}
