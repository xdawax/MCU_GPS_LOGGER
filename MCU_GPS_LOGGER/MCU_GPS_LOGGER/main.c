/*
 * GPS_test.c
 *
 * Created: 2019-02-01 11:15:01
 * Author : dawa
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/delay.h>

#define BUF_SIZE 255


void USART_init()
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);	// enabling RX and TX
	UCSR0C &= ~((1 << UMSEL00) | (1 << UMSEL01)); // ensuring Asynchronous
	UBRR0L = 6;			// 9600 Bps
}

bool USART_is_ready() {
	return (UCSR0A & (1 << UDRE0));
}

void USART_transmit_byte(char byte) {
	while(!(USART_is_ready()));	// wait until buffer is empty
	UDR0 = byte;
}

void USART_transmit_string(char *data, size_t size) {
	int i = 0;
	
	for (i = 0; i < size; i++) {
		USART_transmit_byte(data[i]);
	}
}

char USART_receive_byte() {
	while (!(UCSR0A & (1 << RXC0))); 	// check if there is anything in the buffer.
	return UDR0;
}

// Populates a provided buffer with bytes from the RX buffer
void USART_receive_string(char *buf, size_t size) {
	int i = 0;
	
	for (i = 0; i < size; i++) {
		buf[i] = USART_receive_byte();
	}
}



int main(void)
{
	USART_init();
	char buf[BUF_SIZE];
	buf[0] = 'c';
	char c = '!';
    /* Replace with your application code */
    while (1) 
    {
		//c = USART_receive_byte();
		//USART_receive_string(buf, BUF_SIZE);
		//USART_transmit_string(buf, 6);
		USART_transmit_byte('c');
    }
	return 0;
}

