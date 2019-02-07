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
void test_RW_byte();
void test_RW_word();

int main(void)
{
    USART_init();
	
	EEPROM_clear();
	
	test_RW_word();

	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}

void output(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	USART_transmit_byte(a);
	USART_transmit_byte(b);
	USART_transmit_byte(c);
	USART_transmit_byte(d);
	USART_transmit_byte('\n');
	USART_transmit_byte('\r');
}

void test_RW_word() {
	uint8_t values[4] = {0,0,0,0};
	
	uint32_t word = 0b00000001000000100000001100000100;  // [1,2,3,4] as seperate bytes
	
	EEPROM_write_word_next_free(word);
	
	for (int i = FIRST_DATA_BYTE; i < FIRST_DATA_BYTE + 4; i++)
	{
		values[i] = EEPROM_read_byte(i);
		USART_transmit_byte(values[i] + '0');
	}
	
}
void test_RW_byte() {
	uint8_t a = '1';
	uint8_t b = '2';
	uint8_t c = '3';
	uint8_t d = '4';
	
	_delay_ms(100);
	output(a, b, c, d);
	/*
	EEPROM_write_byte_next_free(a);
	EEPROM_write_byte_next_free(b);
	EEPROM_write_byte_next_free(c);
	EEPROM_write_byte_next_free(d);
	*/
	a = EEPROM_read_byte(0x05);
	b = EEPROM_read_byte(0x04);
	c = EEPROM_read_byte(0x03);
	d = EEPROM_read_byte(0x02);
	
	output(a, b, c, d);
    
	EEPROM_write_byte_next_free('a');
	EEPROM_write_byte_next_free('b');
	EEPROM_write_byte_next_free('c');
	EEPROM_write_byte_next_free('d');
	
	a = EEPROM_read_byte(0x09);
	b = EEPROM_read_byte(0x08);
	c = EEPROM_read_byte(0x07);
	d = EEPROM_read_byte(0x06);
		
	output(a, b, c, d);
}
