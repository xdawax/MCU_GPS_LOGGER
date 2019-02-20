/*
 * tests.c
 *
 * Created: 2019-02-17 10:29:46
 *  Author: David
 */ 
#include "tests.h"

void test_all() {
	
	// translator tests
	//translator_test_all();
	// EEPROM tests
	//test_RW_byte();
	//test_RW_word();
		
	// parser tests
	test_get_gps_coord();
	
	// USART tests
	USART_test_all();
}