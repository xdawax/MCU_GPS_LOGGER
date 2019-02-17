/*
 * main.c
 *
 * Created: 2019-02-01 11:15:01
 * Author : dawa
 */ 

#ifndef F_CPU
#define F_CPU 1000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>  // for nulls
#include "USART.h"
#include "EEPROM.h"
#include "EEPROM_translator.h"

// test files
#include "translator_test.h"
#include "EEPROM_test.h"

int main(void)
{
	USART_init();
	USART_clear_putty();
	
	// translator tests
	test_store_load_struct();
	
	// EEPROM tests
	test_RW_byte();
	test_RW_word();
	
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}
