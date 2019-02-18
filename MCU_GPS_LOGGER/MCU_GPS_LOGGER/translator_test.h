/*
 * translator_test.h
 *
 * Created: 2019-02-15 09:55:28
 *  Author: dawa
 */ 


#ifndef TRANSLATOR_TEST_H_
#define TRANSLATOR_TEST_H_

#ifndef F_CPU
#define F_CPU 1000000
#endif

#include "EEPROM_translator.h"
#include "USART.h"

void init_structs(gps_t *gps1, gps_t *gps2);
void test_store_load_struct();
void translator_test_all();
void test_num_coordinates();

#endif /* TRANSLATOR_TEST_H_ */