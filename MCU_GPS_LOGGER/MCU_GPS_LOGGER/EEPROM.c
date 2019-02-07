/*
 * EEPROM.c
 *
 * Created: 2019-02-05 11:25:08
 *  Author: dawa
 */ 

#ifndef F_CPU
#define F_CPU 1000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "EEPROM.h"
#include "USART.h"  // debugging

// automatically set to atomically RW
void EEPROM_write_byte(uint8_t byte, uint16_t address) {
	cli();								// disable interrupts so we don't get interrupted between seting the master write and write
	while(EECR & (1 << EEPE));			// wait until previous write is completed
	while(SELFPRGEN & (1 << SPMCSR));
	
	EEAR = address;		// write address into address register
	EEDR = byte;		// write data into data register
	EECR |= (1 << EEMPE);	// set Master Write Enable
	EECR |= (1 << EEPE);	// within 4 clock cycles enable write
	_delay_ms(5);			// write takes about 3-4 ms, R.I.P Run In Peace
	
	if (address >= FIRST_DATA_BYTE) {
		EEPROM_set_free_address(1);	// stepping one byte at the time
	}
	sei();								// enable the interrupts
}

void EEPROM_write_byte_next_free(uint8_t byte) {
	uint16_t address = EEPROM_get_free_address();
	EEPROM_write_byte(byte, address);
}

// writes a word to next free location in EEPROM
void EEPROM_write_word_next_free(uint32_t word) {
	
	uint8_t byte = 0;
	
	for (uint8_t i = WORD-1; i < 255; i--)
	{	
		byte = (word >> (i * BYTE));			// take the 8 msb and store them at a time [1010101011111111] => [10101010] at address n, [11111111] at address n+1
		EEPROM_write_byte_next_free(byte);
	}
}

uint8_t EEPROM_read_byte(uint16_t address) {
	cli();							// disable interrupts
	
	uint8_t byte = 0;
	
	while(EECR & (1 << EEPE));	// check that no one is writing data to EEPROM
	
	EEAR = address;					// set address to read from
	EECR |= (1 << EERE);			// enable reading 
	
	byte = EEDR;
	
	sei();							// enable interrupts

	return byte;
}

// reads 4 byte from memory starting at address and returns it
uint32_t EEPROM_read_word(uint16_t address){
	uint32_t byte = 0;
	uint32_t word = 0;
	
	for (uint8_t i = 0; i < WORD; i++)
	{
		byte = EEPROM_read_byte(address + i);
		word |= (byte << (WORD - i - 1) * BYTE);
	}
	
	return word;
}

// gives the address of the next free byte [xxxxx(address)--------]
// this is stored in the first 2 bytes of EEPROM memory
uint16_t EEPROM_get_free_address() {
	uint16_t address = 0;
	address |= (EEPROM_read_byte(ADDRESS_HIGH_BYTE) << BYTE);	// set the 8 msb as the address high bits
	address |= EEPROM_read_byte(ADDRESS_LOW_BYTE);				// set the 8 lsb as the address high bits
	return address;
}

// updates the free address to the next free byte using the size of last written data
void EEPROM_set_free_address(uint8_t size) {
	uint16_t last_address = EEPROM_get_free_address();
	last_address += size;
	uint8_t last_address_low = last_address;			// set 8 lsb, 
	uint8_t last_address_high = (last_address >> BYTE);		// set 8 msb
	EEPROM_write_byte(last_address_low, ADDRESS_LOW_BYTE);
	EEPROM_write_byte(last_address_high, ADDRESS_HIGH_BYTE);
}

// !!!!!!!!!WARNING!!!!!!!!!!!!! Overwrites the entire EEPROM with zeros and resets next free memory location
// takes ~ 5ms/byte in EEPROM
void EEPROM_clear() {
	USART_transmit_string("CLEARING THE EEPROM. THIS MIGHT TAKE A WHILE!!!\n\r");
	for (int i = FIRST_DATA_BYTE; i < 12; i++)	// only erase 10 first bytes debuggmode
	{
		EEPROM_write_byte(0, i);
	}
	EEPROM_write_byte(0, ADDRESS_HIGH_BYTE);
	EEPROM_write_byte(FIRST_DATA_BYTE, ADDRESS_LOW_BYTE);  // set the address of the first available byte as 2
	USART_transmit_string("EEPROM CLEARED!\n\n\r");
}