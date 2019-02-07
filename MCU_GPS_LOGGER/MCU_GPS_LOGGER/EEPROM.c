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


// automatically set to atomically RW
void EEPROM_write_byte(uint8_t byte, uint16_t address) {
	cli();								// disable interrupts so we don't get interrupted between seting the master write and write
	while(EECR & (1 << EEPE));			// wait until previous write is completed
	while(SELFPRGEN & (1 << SPMCSR));
	
	EEAR = address;		// write address into address register
	EEDR = byte;		// write data into data register
	
	EECR |= (1 << EEMPE);	// set Master Write Enable
	EECR |= (1 << EEPE);	// within 4 clock cycles enable write
	_delay_ms(5);			// write takes about 3-4 ms, R.I.P run in peace
	sei();								// enable the interrupts
}

void EEPROM_write_byte_next_free(uint8_t byte) {
	
}


// writes 4 byte to memory from specified address
void EEPROM_write_word(uint32_t word, uint16_t address) {
	
}

// writes a word to next free location in EEPROM
void EEPROM_write_word_next_free(uint32_t word) {
	
}

uint8_t EEPROM_read_byte(uint16_t address) {
	cli();							// disable interrupts
	
	uint8_t byte = -1;
	
	while(EECR & (1 << EEPE));	// check that no one is writing data to EEPROM
	
	EEAR = address;					// set address to read from
	EECR |= (1 << EERE);			// enable reading 
	
	byte = EEDR;
	
	sei();							// enable interrupts
	return byte;
}

// reads 4 byte from memory and returns it
uint32_t EEPROM_read_word(uint16_t address){
	return 0;
}

// gives the address of the next free byte [xxxxx(address)--------]
// this is stored in the first 2 bytes of EEPROM memory
uint16_t EEPROM_get_free_address() {
	return 0;
}

// !!!!!!!!!WARNING!!!!!!!!!!!!! Overwrites the entire EEPROM with zeros 
void EEPROM_clear() {
	
}