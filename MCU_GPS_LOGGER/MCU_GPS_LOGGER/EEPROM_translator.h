/*
 * EEPROM_translator.h
 *
 * Created: 2019-02-13 10:32:58
 *  Author: dawa
 */ 


#ifndef EEPROM_TRANSLATOR_H_
#define EEPROM_TRANSLATOR_H_

#include "EEPROM.h"
#include <stdint.h>

// Change to use include when parser is complete
typedef struct {
	int32_t lattitude;
	int32_t longitude;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minute;
} gps_t;


/// Writes the provided struct to the EEPROM in the first available spot
///
/// @param gps_data the struct to be stored in EEPROM 
///
/// @returns void
void store_struct(gps_t *gps_data);

/// Gets the next struct stored in EEPROM
///
/// @returns the struct stored at the next place in memory
gps_t get_next_struct();



/// Fetches a gps_t struct from EEPROM at provided index
///
///	@param index the indexed order of storage in memory i.e. index 2 = memory location (2 * size_of(gps_t)) + header
///
/// @returns the struct stored at the provided index in memory
gps_t get_struct(uint8_t index);

#endif /* EEPROM_TRANSLATOR_H_ */