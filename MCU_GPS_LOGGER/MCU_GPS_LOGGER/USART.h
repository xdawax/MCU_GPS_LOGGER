/*
 * USART.h
 *
 * Created: 2019-02-02 14:51:59
 *  Author: David
 */ 


#ifndef USART_H_
#define USART_H_

#define BUF_SIZE 255	
#define BYTE 8
#define WORD 4

/// Sets up the USART for TX and RX communication
/// BAUD 9600bps 2X speed
/// @returns void
void USART_init();

/// Transmits one byte of data over the USART
///
/// @param byte[in] the byte to be transmitted
///
/// @returns void
void USART_transmit_byte(uint8_t byte);

/// Transmits a string over the USART ended with \n\r
///
/// @param data[in] the array of characters to be transmitted over the USART
///
/// @returns void
void USART_transmit_string(char data[]);

/// Reads one byte of data from the RX buffer
///
/// @returns the byte read from the RX buffer
uint8_t USART_receive_byte();

/// Reads size amount of bytes from the RX buffer storing them in the provided buffer
///
/// @param buf[out] an array of bytes to store the data from the RX buffer in
/// @param size[in] the array can contain size-1 characters
///
/// @returns void
void USART_receive_string(char *buf, uint8_t size);


/// transmits the value of byte as binary string with format 0bxxxxxxxx (x = 1/0)
///
/// @param byte[in] the byte to be transmited as binary
///
/// @returns void
void USART_transmit_binary(uint8_t byte);

/// transmits the value of a word as base 10 value
///
/// @param word[in] the word to be transmited 
///
/// @returns void
void USART_transmit_word(uint32_t word);

#endif /* USART_H_ */