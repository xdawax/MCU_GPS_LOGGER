/*
 * EEPROM.h
 *
 * Created: 2019-02-05 11:25:25
 *  Author: dawa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_write_byte(uint8_t byte, uint16_t address);

uint8_t EEPROM_read_byte(uint16_t address);


#endif /* EEPROM_H_ */