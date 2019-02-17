/*
 * test_parser.c
 *
 * Created: 2019-02-17 10:14:15
 *  Author: David
 */ 


#include "test_parser.h"

#define DEFAULT_SIZE 75
#define DEFAULT_STRING  "$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C"

void test_get_gps_coord() {
	EEPROM_reset_header();
	USART_transmit_string(DEFAULT_STRING);
}