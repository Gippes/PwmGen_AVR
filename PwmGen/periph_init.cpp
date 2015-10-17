#include "periph_init.h"

void peiph_init()
{
	DDRB =	BIT3;									// ���
	DDRD =	BIT4 | BIT5;							// ����������
	PORTD = BIT2 | BIT3 | BIT6;						// ������
	PORTB = BIT1 | BIT2;							// �������	
	
	//External interrupt initial
	//GICR =	(1<<INT0);								// PD2(16)
	//MCUCR =	(1<<ISC01) | (0<<ISC00);				// �� ����� 
	
	//ADC initial
	ADMUX	=	(1<<ADLAR)|							// ������������ �� ������ ����
				(0<<REFS1)|(1<<REFS0);				// ������� ���������� �� �������� ��������� �������
	
	SFIOR	=	(0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);	// �������������� �� ���������� TIM0 OCR0
	
	ADCSRA	=	(1<<ADEN); 							// ADC ON
				//(1<<ADSC) |						// ��������� �������������� (������������ �� ���������) 
				//(1<<ADATE);						// �������������� ��������� ��������������

	//TIM2 initial periodic system timer
	TIMSK |= (1<<OCIE2);							// ���������� �� ���������
	TCCR2 = (1<<FOC2) |								// ����� NORMAL
			(0<<CS22) |(1<<CS21) |(1<<CS20);		// clk/256
	TCNT2 = 0;										// ��������� �������� ��������
	OCR2  = 125;									// ������� ���������
	


				
	//TIM0 initial 
/*	TIMSK = (1<<OCIE0);								
	TCCR0 = (1<<FOC0) |								
			(0<<CS02) |(1<<CS01) |(1<<CS00);		
	TCNT0 = 0;										
	OCR0  = 125;
*/				

}
	
	