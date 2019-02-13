/*
 * GPS_test.c
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

void test_TX_binary();
void test_TX_word();

void init_structs(gps_t *gps1);

int main(void)
{
    gps_t *gps1 = NULL;
	gps_t *gps2 = NULL;
	gps_t *temp = NULL;
	
	USART_init();
	USART_clear_putty();
	
	init_structs(gps1);
	
	print_struct(gps1);
	//print_struct(gps2);
	
	/* Replace with your application code */
    while (1) 
    {	
		
    }
	return 0;
}
void init_structs(gps_t *gps1) {
		gps1->lattitude = 1;
		gps1->longitude = 2;
		gps1->month = 3;
		gps1->day = 4;
		gps1->hour = 5;
		gps1->minute = 6;
}