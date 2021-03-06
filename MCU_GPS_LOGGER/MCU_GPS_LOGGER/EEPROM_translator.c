/*
 * EEPROM_translator.c
 *
 * Created: 2019-02-13 10:32:37
 *  Author: dawa
 */ 
#include "EEPROM_translator.h"
#include "USART.h"				// debugging
#include "EEPROM.h"

/* Blueprint
typedef struct {
	int32_t lattitude;
	int32_t longitude;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minute;
} gps_t;
*/


void store_struct(gps_t *gps_data) {
	EEPROM_write_word_next_free(gps_data->lattitude);
	EEPROM_write_word_next_free(gps_data->longitude);
	EEPROM_write_byte_next_free(gps_data->month);
	EEPROM_write_byte_next_free(gps_data->day);
	EEPROM_write_byte_next_free(gps_data->hour);
	EEPROM_write_byte_next_free(gps_data->minute);
}

void print_struct(gps_t *gps_data) {
	USART_transmit_string("\n\r########### GPS DATA ###########");
	USART_transmit_string("\n\rLattitude: ");
	USART_transmit_word(gps_data->lattitude);
	
	USART_transmit_string("\n\rLongitude: ");
	USART_transmit_word(gps_data->longitude);
	
	USART_transmit_string("\n\rMonth: ");
	USART_transmit_word(gps_data->month);
	
	USART_transmit_string("\n\rDay: ");
	USART_transmit_word(gps_data->day);
	
	USART_transmit_string("\n\rHour: ");
	USART_transmit_word(gps_data->hour);
	
	USART_transmit_string("\n\rMinute: ");
	USART_transmit_word(gps_data->minute);
	USART_transmit_string("\n\r");
}

gps_t *get_next_struct();

void get_struct(uint8_t index, gps_t *gps_data) {
	uint16_t address = (index * sizeof(gps_t)) + HEADER_SIZE;
	gps_data->lattitude = EEPROM_read_word(address);
	address += sizeof(uint32_t);
	gps_data->longitude = EEPROM_read_word(address);
	address += sizeof(uint32_t);
	gps_data->month = EEPROM_read_byte(address);
	address += sizeof(uint8_t);
	gps_data->day = EEPROM_read_byte(address);
	address += sizeof(uint8_t);
	gps_data->hour = EEPROM_read_byte(address);
	address += sizeof(uint8_t);
	gps_data->minute = EEPROM_read_byte(address);
	address += sizeof(uint8_t);
}

uint8_t get_num_coordinates() {
	uint16_t next_free = EEPROM_get_free_address();
	uint8_t num_coordinates = (next_free - HEADER_SIZE) / sizeof(gps_t);
	
	return num_coordinates;
}