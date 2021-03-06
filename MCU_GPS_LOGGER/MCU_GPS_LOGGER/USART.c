/*
 * USART.c
 *
 * Created: 2019-02-02 14:51:46
 *  Author: David
 */ 

#ifndef F_CPU
#define F_CPU 1000000
#endif

#include <avr/io.h>
#include <stdint.h>

#include "USART.h"

void USART_init()
{
	UCSR0B = (1 << RXEN0);					// enable RX
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

void USART_transmit_string(char data[]) {
	int i = 0;
	
	while(data[i]) {
		USART_transmit_byte(data[i]);
		i++;
	}
}

uint8_t USART_receive_byte() {
	while (!(UCSR0A & (1 << RXC0))); 	// check if there is anything in the buffer.
	USART_transmit_byte(UDR0);			// echo the character 
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

void USART_transmit_binary(uint8_t byte) {
	USART_transmit_string("0b");
	
	for (uint8_t i = BYTE - 1; i < 255; i--)
	{
		if (byte & (1 << i)) {
			USART_transmit_byte('1');
		} else {
			USART_transmit_byte('0');
		}
	}
}

void USART_transmit_digit(uint8_t byte) {
	USART_transmit_byte(byte + '0');
}

void USART_transmit_word(uint32_t word) {
	uint32_t divisor = 1000000000;

	USART_transmit_digit((word / divisor));
	
	while (divisor > 1) {
		divisor = divisor / 10;
		USART_transmit_digit((word / divisor) % 10);
	}
}

void USART_clear_putty() {
	for (uint8_t i = 0; i < 20; i++)
	{
		USART_transmit_byte('\n');
	}
	USART_transmit_byte('\r');
}
