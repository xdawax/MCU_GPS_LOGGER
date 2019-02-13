/*
 * EEPROM_translator.c
 *
 * Created: 2019-02-13 10:32:37
 *  Author: dawa
 */ 
#include "EEPROM_translator.h"


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

gps_t get_next_struct();

gps_t get_struct(uint8_t index);