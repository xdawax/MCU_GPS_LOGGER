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


void output(uint8_t a, uint8_t b, uint8_t c, uint8_t d);




void output(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	USART_transmit_byte(a);
	USART_transmit_byte(b);
	USART_transmit_byte(c);
	USART_transmit_byte(d);
	USART_transmit_byte('\n');
	USART_transmit_byte('\r');
}

void test_RW_word() {
	USART_transmit_string("TESTING: test_RW_word\n\r");
	uint8_t values[4] = {0,0,0,0};
	
	uint32_t word = 0b00000001000000100000001100000100;  // [1,2,3,4] as seperate bytes
	
	USART_transmit_string("Expected output 1234: ");
	EEPROM_write_word_next_free(word);
	
	for (int i = FIRST_DATA_BYTE; i < FIRST_DATA_BYTE + 4; i++)
	{
		values[i] = EEPROM_read_byte(i);
		USART_transmit_byte(values[i] + '0');
	}
	USART_transmit_string("\n\r");
	
	uint32_t read_word = EEPROM_read_word(FIRST_DATA_BYTE);
	if (read_word == word) {
		USART_transmit_string("READING WORD: SUCCESS\n\r");
	} else {
		USART_transmit_string("READING WORD: FAILURE\n\r");
		USART_transmit_string("GOT: ");
		for (int i = FIRST_DATA_BYTE; i < FIRST_DATA_BYTE + 4; i++)
		{
			values[i] = EEPROM_read_byte(i);
			USART_transmit_byte(values[i] + '0');
		}
		USART_transmit_string("\n\rEXPECTED: 16909060\n\r");
	}
	
		
	USART_transmit_string("TEST COMPLETED: test_RW_word\n\n\r");
	
}
void test_RW_byte() {
	
	USART_transmit_string("TESTING: test_RW_byte\n\r");
	uint8_t a = '1';
	uint8_t b = '2';
	uint8_t c = '3';
	uint8_t d = '4';
	
	USART_transmit_string("Expected output 1234: ");
	output(a, b, c, d);
	
	EEPROM_write_byte_next_free(a);
	EEPROM_write_byte_next_free(b);
	EEPROM_write_byte_next_free(c);
	EEPROM_write_byte_next_free(d);
	
	a = EEPROM_read_byte(0x07);
	b = EEPROM_read_byte(0x06);
	c = EEPROM_read_byte(0x05);
	d = EEPROM_read_byte(0x04);
	
	USART_transmit_string("Expected output 4321: ");
	output(a, b, c, d);
	
	EEPROM_write_byte_next_free('a');
	EEPROM_write_byte_next_free('b');
	EEPROM_write_byte_next_free('c');
	EEPROM_write_byte_next_free('d');
	
	a = EEPROM_read_byte(0x0b);
	b = EEPROM_read_byte(0x0a);
	c = EEPROM_read_byte(0x09);
	d = EEPROM_read_byte(0x08);
		
	USART_transmit_string("Expected output dcba: ");
	output(a, b, c, d);
	USART_transmit_string("TEST COMPLETED: test_RW_byte\n\n\r");
}
