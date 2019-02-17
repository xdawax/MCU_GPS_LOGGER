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
#include "tests.h"


int main(void)
{
	// minimum startup with fresh EEPROM 
	USART_init();
	USART_clear_putty();
	EEPROM_reset_header();

	test_all();
	
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}
