#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned int TIMER1_INTERVAL = 0x7A12; //=31250 (decimal)
unsigned int TIMER2_INTERVAL = 0xf4; //=244 (decimal)
unsigned char TIMER1_STR[] = "ping\r\n";
unsigned char TIMER2_STR[] = "pong\r\n";

//вывод строки в USART
void serial_avr(char *str)
{
	UCSRB=(1<<TXEN);
	UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
	UBRRL=51;
	
	for (unsigned int i=0; str[i]!=0; i++)
	{
		UDR=str[i];
		while(!(UCSRA&(1<<UDRE)));
	}
	_delay_ms(500);
}

//инициализация timer1
void timer1_ini(void)
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1A = TIMER1_INTERVAL; //записываем в регистр число для сравнения
	TCCR1B |= (1<<CS11) | (1<<CS10);//установим делитель на 64
	//интервал 2 сек
}

//обработка прерывания для timer1 по совпадению
ISR (TIMER1_COMPA_vect)
{
	//вывести строку в USART
	serial_avr(TIMER1_STR);
}

//инициализация timer2
void timer2_ini(void)
{
	TCCR2 = (1<<WGM21); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK = (1<<OCIE2); ///устанавливаем бит разрешения прерывания 2ого счетчика по совпадению
	OCR2 = TIMER2_INTERVAL; //записываем в регистр число для сравнения
	TCCR2 |= (1<<CS22) | (1<<CS21); //установим делитель на 256
	//интервал 0,7 сек
}

//обработка прерывания для timer2 по совпадению
ISR (TIMER2_COMP_vect)
{
	//вывести строку в USART
	serial_avr(TIMER2_STR);
}
//--------------------------------------------
int main(void)
{
	timer2_ini();
	timer1_ini();
	sei();
	while(1)
	{
	}
}

