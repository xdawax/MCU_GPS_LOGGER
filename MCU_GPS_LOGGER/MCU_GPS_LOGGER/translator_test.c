/*
 * translator_test.c
 *
 * Created: 2019-02-15 09:55:14
 *  Author: dawa
 */ 

#include "translator_test.h"


void translator_test_all() {
	test_store_load_struct();
}
void test_store_load_struct() {
	gps_t gps1;
	gps_t gps2;
	gps_t temp = {0,0,0,0,0,0};
	
	init_structs(&gps1, &gps2);
	
	store_struct(&gps1);	// should be stored at address 2
	store_struct(&gps2);	// should be stored at address 14
	
	get_struct(0, &temp);
	USART_transmit_string("#############################################");
	USART_transmit_string("\n\rEXPECTED: ");
	print_struct(&gps1);
	USART_transmit_string("\n\rGOT:");
	print_struct(&temp);
	USART_transmit_string("#############################################");
	
	get_struct(1, &temp);
	
	USART_transmit_string("\n\n\r#############################################");
	USART_transmit_string("\n\rEXPECTED: ");
	print_struct(&gps2);
	USART_transmit_string("\n\rGOT:");
	print_struct(&temp);
	USART_transmit_string("#############################################");
}


void init_structs(gps_t *gps1, gps_t *gps2) {
	gps1->lattitude = 1;
	gps1->longitude = 2;
	gps1->month = 3;
	gps1->day = 4;
	gps1->hour = 5;
	gps1->minute = 6;
	
	gps2->lattitude = 7;
	gps2->longitude = 7;
	gps2->month = 7;
	gps2->day = 7;
	gps2->hour = 7;
	gps2->minute = 7;
}