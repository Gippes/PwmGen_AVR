#include "PWM.h"

PWM::PWM()
{
	mode = INITIAL;
	
	FastPWM_settings._TCCR1A = 0<<WGM11 | 1<< WGM10 | 1<<COM1A1 | 0<<COM1A0;
	FastPWM_settings._TCCR1B = 0<<WGM13 | 1<< WGM12 | 0<<CS12	| 0<<CS11	| 1<<CS10;
	FastPWM_settings._OCR1AH = 0;
	FastPWM_settings._OCR1AL = 0;
	
	CTC_settings._TCCR1A = 0<<WGM11 | 0<< WGM10 | 0<<COM1A1 | 1<<COM1A0;
	CTC_settings._TCCR1B = 0<<WGM13 | 1<< WGM12 | 0<<CS12	| 0<<CS11	| 1<<CS10;
	CTC_settings._OCR1AH = 0;
	CTC_settings._OCR1AL = 0;
	
	PhaseCorrect_settings._TCCR1A = 0<<WGM11 | 1<< WGM10 | 1<<COM1A1 | 0<<COM1A0;
	PhaseCorrect_settings._TCCR1B = 0<<WGM13 | 0<< WGM12 | 0<<CS12	 | 0<<CS11	| 1<<CS10;
	PhaseCorrect_settings._OCR1AH = 0;
	PhaseCorrect_settings._OCR1AL = 0;

	PhaseCorrectFreq_settings._TCCR1A = 0<<WGM11 | 1<< WGM10 | 1<<COM1A1 | 0<<COM1A0;
	PhaseCorrectFreq_settings._TCCR1B = 1<<WGM13 | 0<< WGM12 | 0<<CS12	 | 0<<CS11	| 1<<CS10;
	PhaseCorrectFreq_settings._OCR1AH = 0;
	PhaseCorrectFreq_settings._OCR1AL = 0;


	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1H = 0;	TCNT1L = 0;									// обнуление счётного регистра
	OCR1AH = 0;	OCR1AL = 0;									// обнуление регистра сравнения выходного сигнала
	
	DDRD	|=	OC1A_bit;									// OC1A ON
	prescaller_value = 1;
}

// выбор деления входной частоты 
void PWM::set_prescaler(const uint8_t &state)
{
	TCCR1B &=~ ((1<<CS12) | (1<<CS11) | (1<<CS10));
	switch(state)
	{
		case 0: TCCR1B |= (0<<CS12) | (0<<CS11) | (1<<CS10); prescaller_value = 1;  break;	// clk/1
		case 1: TCCR1B |= (0<<CS12) | (1<<CS11) | (0<<CS10); prescaller_value = 8;	break;	// clk/8
		case 2: TCCR1B |= (0<<CS12) | (1<<CS11) | (1<<CS10); prescaller_value = 64; break;	// clk/32
		case 3: TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10); prescaller_value = 256;break;	// clk/64
		case 4:	TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10); prescaller_value = 1024;break;	// clk/128
	}
}

uint16_t PWM::get_prescaler_value() const
{
	return prescaller_value;
}

void PWM::save_settings()
{
	settings *tmp;
	tmp = select_mode(mode);	
	tmp->_OCR1AH = OCR1AH;
	tmp->_OCR1AL = OCR1AL;
	tmp->save	 = true;
}

void PWM::set_mode_pwm(_MODE _M)
{
	save_settings();
	mode = _M;
	settings *mode_setting;
	mode_setting = select_mode(mode);

	TCCR1A = mode_setting->_TCCR1A;
	TCCR1B = mode_setting->_TCCR1B;
	
	if (mode_setting->save)
	{
		OCR1AH = mode_setting->_OCR1AH;
		OCR1AL = mode_setting->_OCR1AL;
	}
	else
	{
		OCR1AH = 0;
		OCR1AL = 0;
	}
}

settings* PWM::select_mode(const uint8_t &mode)
{
	settings* tmp;
	switch(mode)
	{
		case FAST_PWM:				tmp = &FastPWM_settings;			break;
		case CTC:					tmp = &CTC_settings;				break;
		case PHASE_CORRECT:			tmp = &PhaseCorrect_settings;		break;
		case PHASE_FREQ_CORRECT:	tmp = &PhaseCorrectFreq_settings;	break;
		default: return 0;
	}
	return tmp;
}


PWM::~PWM()
{
	TIMSK	&=~ (1<<OCIE1A);
	TCCR1A	= 0;
	TCCR1B	= 0;
	DDRD	&=~ OC1A_bit;
	TCNT1H	= 0;	TCNT1L = 0;									// обнуление счётного регистра
	OCR1AH	= 0;	OCR1AL = 0;									// обнуление регистра сравнения выходного сигнала
} 
	
