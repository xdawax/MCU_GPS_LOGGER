/*
 * test_parser.c
 *
 * Created: 2019-02-17 10:14:15
 *  Author: David
 */ 


#include "test_parser.h"

#define DEFAULT_SIZE 75
const char *DEFAULT_STRING =  "$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C";

void test_get_gps_coord() {
	EEPROM_reset_header();
	
	gps_t gps_data;
	USART_transmit_string("TESTING: get_gps_coord from GPS_parce.c\n\r");
	if (get_gps_coord(&gps_data, DEFAULT_STRING)) {
		USART_transmit_string("\n\rSUCCESSFULLY RECEIVED GPS DATA");
		print_struct(&gps_data);
	} else {
		USART_transmit_string("\n\rFAILED TO RECEIVE GPS DATA");
	}
	USART_transmit_string("TEST COMPLETED: test_gps_coord from GPS_parce.c\n\n\r");
	
}