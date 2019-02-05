/*
 * EEPROM.c
 *
 * Created: 2019-02-05 11:25:08
 *  Author: dawa
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void EEPROM_write_byte(uint8_t byte, uint16_t address) {
	cli();								// disable interrupts so we don't get interrupted between seting the master write and write
	while(EECR & (1 << EEPE));			// wait until previous write is completed
	while(SELFPRGEN & (1 << SPMCSR));
	
	EEAR = address;		// write address into address register
	EEDR = byte;		// write data into data register
	
	EECR |= (1 << EEMPE);	// set Master Write Enable
	EECR |= (1 << EEPE);	// within 4 clock cycles enable write
	
	sei();								// enable the interrupts
}

uint8_t EEPROM_read_byte(uint16_t address) {
	uint8_t byte = -1;
	
	return byte;
}