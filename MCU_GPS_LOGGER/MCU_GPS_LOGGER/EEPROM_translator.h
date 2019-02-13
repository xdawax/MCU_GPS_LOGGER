/*
 * EEPROM_translator.h
 *
 * Created: 2019-02-13 10:32:58
 *  Author: dawa
 */ 


#ifndef EEPROM_TRANSLATOR_H_
#define EEPROM_TRANSLATOR_H_

// Change to use include when parser is complete
typedef struct {
	int32_t lattitude;
	int32_t longitude;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minute;
} gps_t;

void store_struct(gps_t *gps_data);


#endif /* EEPROM_TRANSLATOR_H_ */