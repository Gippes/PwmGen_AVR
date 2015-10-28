#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include "periph_init.h"
#include "PWM.h"
#include "periodic.h"
#include "LCD/hd44780.h"
#include "screen.h"


#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)


struct Button
{
	bool	detect;
	uint8_t time;
};

/*** ������� �������� ������� ������, ���� ������ -> �������� n ������, �� ��������� ���������� true. ���� �� ������ false ***/
// const uint8_t PINX		- ��� �����
// const uint8_t pin_number	- ����� ���� �� ������� ����������� ������
// Button &but				- ��������� ���������� ���� ������������ ������ � ����� ��������
bool push_button (const uint8_t PINX, const uint8_t pin_number, Button &but);
#endif