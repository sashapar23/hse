#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned int TIMER1_INTERVAL = 0x7A12; //=31250 (decimal)
unsigned int TIMER2_INTERVAL = 0xf4; //=244 (decimal)
unsigned char TIMER1_STR[] = "ping\r\n";
unsigned char TIMER2_STR[] = "pong\r\n";

//����� ������ � USART
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

//������������� timer1
void timer1_ini(void)
{
	TCCR1B |= (1<<WGM12); // ������������� ����� ��� (����� �� ����������)
	TIMSK |= (1<<OCIE1A);	//������������� ��� ���������� ���������� 1��� �������� �� ���������� � OCR1A(H � L)
	OCR1A = TIMER1_INTERVAL; //���������� � ������� ����� ��� ���������
	TCCR1B |= (1<<CS11) | (1<<CS10);//��������� �������� �� 64
	//�������� 2 ���
}

//��������� ���������� ��� timer1 �� ����������
ISR (TIMER1_COMPA_vect)
{
	//������� ������ � USART
	serial_avr(TIMER1_STR);
}

//������������� timer2
void timer2_ini(void)
{
	TCCR2 = (1<<WGM21); // ������������� ����� ��� (����� �� ����������)
	TIMSK = (1<<OCIE2); ///������������� ��� ���������� ���������� 2��� �������� �� ����������
	OCR2 = TIMER2_INTERVAL; //���������� � ������� ����� ��� ���������
	TCCR2 |= (1<<CS22) | (1<<CS21); //��������� �������� �� 256
	//�������� 0,7 ���
}

//��������� ���������� ��� timer2 �� ����������
ISR (TIMER2_COMP_vect)
{
	//������� ������ � USART
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

