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
#include "USART.h"
#include "EEPROM.h"
#include "EEPROM_translator.h"
#include "tests.h"
#include "GUI.h"

#define GPS_INTERVAL 5	// skipping storing GPS_INTERVAL times == GPS_INTERVAL seconds

char GPS_DATA[BUF_SIZE];


int main(void)
{
	// minimum startup with fr10esh EEPROM 
	// USART_init();
	// USART_clear_putty();

	EEPROM_reset_header();

	init_GUI();
	DDRC |= (1 << PC5);	// LED-Output
	// gps_t GPS1,GPS2,GPS3;
	// get_gps_coord(&GPS1, "$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C");
	// get_gps_coord(&GPS2, "$GPRMC,064951.000,A,2307.1200,N,12016.4400,E,0.03,165.48,260406,3.05,W,A*2C");
	// get_gps_coord(&GPS3, "$GPRMC,064951.000,A,2307.1236,N,12016.4400,E,0.03,165.48,260406,3.05,W,A*2C");
	//  
	// store_struct(&GPS1);
	// store_struct(&GPS2); 
	// store_struct(&GPS3); 

	uint8_t i = 0;
	uint16_t interval = 0;
	gps_t gps;

	USART_transmit_string("\n\r###############################################################");
	USART_transmit_string("\n\rECHO: \n\r");
	
	//test_all();

	/* Replace with your application code */
    while (1) 
    {	
		while (!get_gps_coord(&gps,GPS_DATA)){
			USART_receive_string(GPS_DATA, BUF_SIZE);
		} 
		GPS_DATA[0] = '0';
		
		while (!(is_gprmc(GPS_DATA))) {
			USART_receive_string(GPS_DATA, BUF_SIZE);
		}
		PORTC |= (1 << PC5); // LED-Display
		if (is_gprmc(GPS_DATA)) {
			interval++;	
		}
		
		// every GPS_INTERVALth iteration store the struct
		if((interval % GPS_INTERVAL) == 0) {
			// USART_transmit_string("\n\rFOUND GPS DATA!\n\r");
			get_gps_coord(&gps, GPS_DATA);
			print_struct(&gps);
			store_struct(&gps);
			i++;
		}
		
		if (i == MAX_STRUCTS) {
			for (int j = 0; j < MAX_STRUCTS; j++) {
				get_struct(j, &gps);
				// USART_transmit_string("\n\r at index: ");
				// USART_transmit_word(j);
				// print_struct(&gps);
			}
			while(1);
		}	
    }
	return 0;
}
