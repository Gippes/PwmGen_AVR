#include "periph_init.h"

void peiph_init()
{
	DDRB =	BIT3;									// ШИМ
	DDRD =	BIT4 | BIT5;							// светодиоды
	PORTD = BIT2 | BIT3 | BIT6;						// кнопки
	PORTB = BIT1 | BIT2;							// энкодер	
	
	//External interrupt initial
	//GICR =	(1<<INT0);								// PD2(16)
	//MCUCR =	(1<<ISC01) | (0<<ISC00);				// по спаду 
	
	//ADC initial
	ADMUX	=	(1<<ADLAR)|							// выравнивание по левому краю
				(0<<REFS1)|(1<<REFS0);				// опорное напряжение от внешнего источника питания
	
	SFIOR	=	(0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);	// преобразование по прерыванию TIM0 OCR0
	
	ADCSRA	=	(1<<ADEN); 							// ADC ON
				//(1<<ADSC) |						// включение преобразования (сбрасывается по окончанию) 
				//(1<<ADATE);						// автоматическое включение преобразований

	//TIM2 initial periodic system timer
	TIMSK |= (1<<OCIE2);							// прерывание по сравнению
	TCCR2 = (1<<FOC2) |								// режим NORMAL
			(0<<CS22) |(1<<CS21) |(1<<CS20);		// clk/256
	TCNT2 = 0;										// обнуление счётного регистра
	OCR2  = 125;									// регистр сравнения
	


				
	//TIM0 initial 
/*	TIMSK = (1<<OCIE0);								
	TCCR0 = (1<<FOC0) |								
			(0<<CS02) |(1<<CS01) |(1<<CS00);		
	TCNT0 = 0;										
	OCR0  = 125;
*/				

}
	
	