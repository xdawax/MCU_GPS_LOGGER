/*
 * test_parser.c
 *
 * Created: 2019-02-17 10:14:15
 *  Author: David
 */ 


#include "test_parser.h"

#define DEFAULT_SIZE 75
char *DEFAULT_STRING =  "$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C";
char *REAL_STRING = "$GPRMC,154257.214,A,5950.2621,N,01738.9178,E,0.53,6.58,180219,,,A*63";

void test_get_gps_coord() {
	EEPROM_reset_header();
	
	gps_t gps_data;
	USART_transmit_string("TESTING: get_gps_coord from GPS_parce.c\n\r");
	if (get_gps_coord(&gps_data, REAL_STRING)) {
		USART_transmit_string("\n\rSUCCESSFULLY RECEIVED GPS DATA");
		print_struct(&gps_data);
	} else {
		USART_transmit_string("\n\rFAILED TO RECEIVE GPS DATA");
	}
	USART_transmit_string("TEST COMPLETED: test_gps_coord from GPS_parce.c\n\n\r");
	
}