/*
 * main.c
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
	
	EEPROM_reset_header();
	
	
	// can only run one test at the time since they will use same address-space
	test_RW_word();
	//test_RW_byte();
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}