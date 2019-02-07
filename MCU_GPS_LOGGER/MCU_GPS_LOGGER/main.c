/*
 * GPS_test.c
 *
 * Created: 2019-02-01 11:15:01
 * Author : dawa
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "EEPROM.h"

void test_TX_binary();



int main(void)
{
    USART_init();
	
	test_TX_binary();
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}

void test_TX_binary() {
	USART_transmit_string("TESTING: test_TX_binary\n\r");
	uint8_t a = 0b11111111;
	uint8_t b = 0b00000000;
	uint8_t c = 0b01010101;
	uint8_t d = 0b10101010;
	
	USART_transmit_string("Expected output 0b11111111, got: ");
	USART_transmit_binary(a);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0b00000000, got ");
	USART_transmit_binary(b);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0b01010101, got ");
	USART_transmit_binary(c);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0b10101010, got ");
	USART_transmit_binary(d);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("TEST COMPLETED: test_TX_binary\n\n\r");
}