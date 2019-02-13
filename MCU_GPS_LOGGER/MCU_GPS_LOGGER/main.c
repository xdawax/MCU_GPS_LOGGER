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
void test_TX_word();


int main(void)
{
    USART_init();
	
	USART_clear_putty();
	test_TX_binary();
	test_TX_word();
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}

void test_TX_word() {
	USART_transmit_string("TESTING: test_TX_binary_word\n\r");
	uint32_t a = 1892392;
	uint32_t b = 0;
	uint32_t c = 4294967295;
	uint32_t d = 19910;
	
	USART_transmit_string("Expected output 0001892392, got: ");
	USART_transmit_word(a);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0000000000, got: ");
	USART_transmit_word(b);
	USART_transmit_string("\n\r");
		
	USART_transmit_string("Expected output 4294967295, got: ");
	USART_transmit_word(c);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0000019910, got: ");
	USART_transmit_word(d);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("TEST COMPLETED: test_TX_word\n\n\r");
}

void test_TX_binary() {
	USART_transmit_string("TESTING: test_TX_binary_byte\n\r");
	uint8_t a = 0b11111111;
	uint8_t b = 0b00000000;
	uint8_t c = 0b01010101;
	uint8_t d = 0b10101010;
	
	USART_transmit_string("Expected output 0b11111111, got: ");
	USART_transmit_binary(a);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0b00000000, got: ");
	USART_transmit_binary(b);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0b01010101, got: ");
	USART_transmit_binary(c);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("Expected output 0b10101010, got: ");
	USART_transmit_binary(d);
	USART_transmit_string("\n\r");
	
	USART_transmit_string("TEST COMPLETED: test_TX_binary\n\n\r");
}