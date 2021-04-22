/*
 * 44LedControl.c
 *
 * Created: 21.04.2021 0:37:47
 * Author : Leo
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000 UL;

int main(void)
{
	//Порт А0 пин 13 на вход
	DDRA = 0b00000000;
	//Настраиваем АЦП
	ADMUX=
	(1<<MUX0)|
	(0<<MUX1)|
	(0<<MUX2)|
	(0<<MUX3)|
	(0<<MUX4)|
	(0<<MUX5)| //выбираем ADC1 для ввода через мультиплексер
	(0<<REFS0)|
	(0<<REFS1); //вибираем внешний источник
	ADCSRB=
	(0<<BIN)|
	(0<<ACME)|
	(1<<ADLAR)| //выравнивание справо
	(0<<ADTS0)|
	(0<<ADTS1)|
	(0<<ADTS2);
	
	ADCSRA|=
	(1<<ADEN)| //разрешаем работу АЦП
	(1<<ADPS2)| 
	(0<<ADPS1)|
	(0<<ADPS0)|//Устанавливаем прескейлер на 4
	(1<<ADATE)|
	(0<<ADIE);
	DIDR0=0xff;
	// Запуск АЦП
	ADCSRA|=(1<<ADSC);
	
	
	
	unsigned char Mlad = ADCL;
	unsigned char Star;
	
	unsigned char min = Mlad;
	unsigned char max = Star;
	unsigned char mid;
	
	//настройка пределителя тактовой частоты контроллера
	//CLKPR = 128;
	//CLKPR = 4;
	
	//настройка всех портов на выход
	DDRB = 0b11111111;
	//настройка таймера
	TCCR0A = 0b10000011;
	TCCR0B = 0b00000010;
	//настройка точки сравнения скважности
	OCR0A = 128;
	//изменение точки скважности
	
	
	
	while (1)
	{
		
		/*
		if (min>Mlad)
		{
			min=Mlad;
		}
		if (max<Mlad)
		{
			max=Mlad;
		}
		mid = (min/2+max/2);
		*/
		//изменение точки скважности
		
		ADCSRA|=(1<<ADSC);
		_delay_ms(10);
		OCR0A=ADCH;
		//Проверка на принятие и
		/*if (ADCSRA & (1<<4)) //Если флаг ADIF равен 1
		{
			
			if (AD<200)
			{
				OCR0A = 0;
			} 
			else
			{
				OCR0A = 200;
			}
			ADCSRA |= (1<<4); //Снова выставляем флаг*/
		
	}
}