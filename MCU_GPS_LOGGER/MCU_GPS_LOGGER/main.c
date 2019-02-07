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

void output(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	USART_transmit_byte(a);
	USART_transmit_byte(b);
	USART_transmit_byte(c);
	USART_transmit_byte(d);
	USART_transmit_byte('\n');
	USART_transmit_byte('\r');
}

int main(void)
{
    USART_init();
	
	uint8_t a = 'a';
	uint8_t b = 'b';
	uint8_t c = 'c';
	uint8_t d = 'd';
	
	_delay_ms(100);
	output(a, b, c, d);
	
	EEPROM_write_byte_next_free(a);
	EEPROM_write_byte_next_free(b);
	EEPROM_write_byte_next_free(c);
	EEPROM_write_byte_next_free(d);
	
	a = EEPROM_read_byte(0x03);
	b = EEPROM_read_byte(0x02);
	c = EEPROM_read_byte(0x01);
	d = EEPROM_read_byte(0x00);
	
	output(a, b, c, d);
    /* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}