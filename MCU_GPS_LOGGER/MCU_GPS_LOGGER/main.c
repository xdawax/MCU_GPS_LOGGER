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

char GPGGA[BUF_SIZE];
char GPGSA[BUF_SIZE];
char GPRMC[BUF_SIZE];
char GPVTG[BUF_SIZE];


int main(void)
{
	// minimum startup with fresh EEPROM 
	USART_init();
	USART_clear_putty();
	EEPROM_reset_header();

	uint8_t it = 0;
	
	gps_t gps;

	/* Replace with your application code */
    while (1) 
    {	
		while (it < 5) {
			USART_transmit_string("\n\r###############################################################");
			USART_transmit_string("\n\rECHO: \n\r");
			USART_receive_string(GPGGA, BUF_SIZE);
			USART_receive_string(GPGSA, BUF_SIZE);
			USART_receive_string(GPRMC, BUF_SIZE);
			USART_receive_string(GPVTG, BUF_SIZE);
			USART_transmit_string("\n\rRECEIVED :\n\r");	
			USART_transmit_string("GPGGA: ");
			USART_transmit_string(GPGGA);
			USART_transmit_string("\n\rGPGSA: ");
			USART_transmit_string(GPGSA);
			USART_transmit_string("\n\rGPRMC: ");
			USART_transmit_string(GPRMC);
			USART_transmit_string("\n\rGPVTG: ");
			USART_transmit_string(GPVTG);
			it++;
		}
		
		if (is_gprmc(GPRMC)) {
			USART_transmit_string("\n\rIT IS!\n\r");
		}
    }
	return 0;
}
