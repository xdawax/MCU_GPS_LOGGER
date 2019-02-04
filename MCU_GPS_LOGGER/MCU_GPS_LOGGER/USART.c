/*
 * USART.c
 *
 * Created: 2019-02-02 14:51:46
 *  Author: David
 */ 
#include "USART.h"
#include <avr/io.h>

void USART_init()
{
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);		// enable TX and RX
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);     // 8 data bits, 1 stop bit
	
	// Set baud to 9600
	UBRR0H = 0;                        
	UBRR0L = 12;
	// Set baud to 9600
	
	UCSR0A |= (1 << U2X0);						// 2X speed
}

void USART_transmit_byte(uint8_t byte) {
	while(!(UCSR0A & (1 <<UDRE0)));	// wait until buffer is empty
	UDR0 = byte;
}

void USART_transmit_string(char *data) {
	int i = 0;
	
	while(data[i]) {
		USART_transmit_byte(data[i]);
		i++;
	}
}

uint8_t USART_receive_byte() {
	while (!(UCSR0A & (1 << RXC0))); 	// check if there is anything in the buffer.
	USART_transmit_byte(UDR0);
	return UDR0;
}

// Populates a provided buffer with bytes from the RX buffer
void USART_receive_string(char *buf, uint8_t size) {
	int i = 0;
	
	for (i = 0; i < size - 1; i++) {
		buf[i] = USART_receive_byte();
		if (buf[i] == '\r') {
			buf[i + 1] = '\0';
			break;
		}
	}
	
}