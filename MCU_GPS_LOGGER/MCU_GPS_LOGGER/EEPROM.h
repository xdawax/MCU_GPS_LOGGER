/*
 * EEPROM.h
 *
 * Created: 2019-02-05 11:25:25
 *  Author: dawa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define LAST_BYTE 1023
#define FIRST_BYTE 0
#define ADDRESS_HIGH_BYTE 0
#define ADDRESS_LOW_BYTE 1
#define FIRST_DATA_BYTE 2
#define BYTE 8
#define WORD 4

void EEPROM_write_byte(uint8_t byte, uint16_t address);
void EEPROM_write_byte_next_free(uint8_t byte);

// writes a word to next free location in EEPROM
void EEPROM_write_word_next_free(uint32_t word);

// reads and returns one byte from specified address
uint8_t EEPROM_read_byte(uint16_t address);

// reads 4 byte from memory and returns it
uint32_t EEPROM_read_word(uint16_t address);

// gives the address of the next free byte [xxxxx(address)--------]
// this is stored in the first 2 bytes of EEPROM memory
uint16_t EEPROM_get_free_address();

// updates the free address to the next free byte using the size of last written data
void EEPROM_set_free_address(uint8_t size);

// !!!!!!!!!WARNING!!!!!!!!!!!!! Overwrites the entire EEPROM with zeros and resets next free memory location
void EEPROM_clear();












#endif /* EEPROM_H_ */