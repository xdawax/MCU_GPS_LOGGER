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



int main(void)
{
	USART_init();
	USART_clear_putty();
	
	test_store_load_struct();
	
	
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}
