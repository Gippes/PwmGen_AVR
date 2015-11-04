#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>
#include "avr/io.h"	


#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)

#define OC1A_bit (1<<5)
#define OC1B_bit (1<<4)

struct settings
{
	uint8_t _TCCR1A;
	uint8_t _TCCR1B;
	uint8_t _OCR1AH;
	uint8_t _OCR1AL;
	bool	save;
};

class PWM
{
private:
	uint8_t mode :3;	
	settings CTC_settings; 
	settings FastPWM_settings;
	settings PhaseCorrect_settings;
	settings PhaseCorrectFreq_settings;
	settings* select_mode(const uint8_t &mode);
	void save_settings();
	
public:
	enum _MODE {INITIAL = 0, FAST_PWM, PHASE_CORRECT,PHASE_FREQ_CORRECT, CTC};
	PWM();
	void set_prescaler(const uint8_t &state);
	void set_mode_pwm(_MODE _M);
	~PWM();
};

#endif //__PWM_H__
