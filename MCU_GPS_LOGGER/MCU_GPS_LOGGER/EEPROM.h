/*
 * EEPROM.h
 *
 * Created: 2019-02-05 11:25:25
 *  Author: dawa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define HEADER_SIZE 4
#define LAST_BYTE 1023					// address-space ends
#define FIRST_BYTE 0					// address-space start
#define ADDRESS_HIGH_BYTE 0				// memory header that contains the 8 highest bits of a pointer to the next free spot in memory
#define ADDRESS_LOW_BYTE 1				// memory header that contains the 8 lowest bits of a pointer to the next free spot in memory
#define ADDRESS_INDEX 3					// data at this address keeps track of how many structs are stored in memory max 255 (8bit)
#define FIRST_DATA_BYTE HEADER_SIZE		// memory of where the first data byte is allowed to be written
#define BYTE 8							// the size of a byte
#define WORD 4							// number of bytes in a word




/// Writes a byte of data to EEPROM memory at provided address
///
/// @param byte the byte to be written into EEPROM
/// @param address the location in memory where to store the data
///             
/// @returns void
void EEPROM_write_byte(uint8_t byte, uint16_t address);

/// Writes a byte of data to EEPROM memory at the lowest available position
///
/// @param byte the byte to be written into EEPROM
///
/// @returns void
void EEPROM_write_byte_next_free(uint8_t byte);

/// Writes a word (4 byte) of data to EEPROM memory at the lowest available position
///
/// @param word the word to be written into EEPROM
///
/// @returns void
void EEPROM_write_word_next_free(uint32_t word);

/// reads and returns one byte from specified address
///
/// @param address the location in EEPROM to retrieve the byte from
///
/// @returns the byte located at address
uint8_t EEPROM_read_byte(uint16_t address);

/// reads 1 word (4 byte) from memory and returns it
///
/// @param address the location in EEPROM to retrieve the word from
///
/// @returns the word located at address
uint32_t EEPROM_read_word(uint16_t address);

/// gives the address of the next free byte in EEPROM [xxxxx(address)--------]
///
/// @returns the next free address in EEPROM
uint16_t EEPROM_get_free_address();



/// !!!!!!!!!WARNING!!!!!!!!!!!!! Overwrites the entire EEPROM with zeros and resets next free memory location
///
/// @returns void
void EEPROM_clear();

/// Resets the header, next free space will be FIRST_DATA_BYTE 
/// and amount of structs stored will be set to 0
///
/// @returns void
void EEPROM_reset_header();








#endif /* EEPROM_H_ */