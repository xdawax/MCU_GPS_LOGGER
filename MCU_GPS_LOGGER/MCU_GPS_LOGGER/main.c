/*
 * main.c
 *
 * Created: 2019-02-01 11:15:01
 * Author : dawa
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>  // for nulls
#include "USART.h"
#include "EEPROM.h"
#include "EEPROM_translator.h"


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
void init_structs(gps_t *gps1, gps_t *gps2);
void test_store_load_struct();


int main(void)
{
	USART_init();
	USART_clear_putty();
	EEPROM_clear();
	test_store_load_struct();
	
	
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}
