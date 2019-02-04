/*
 * USART.h
 *
 * Created: 2019-02-02 14:51:59
 *  Author: David
 */ 


#ifndef USART_H_
#define USART_H_


#include <stdbool.h>
#include <stdlib.h>
#include <avr/delay.h>

#define BUF_SIZE 255

void USART_init();

void USART_transmit_byte(uint8_t byte);

void USART_transmit_string(char *data);

uint8_t USART_receive_byte();

void USART_receive_string(char *buf, uint8_t size) ;
#endif /* USART_H_ */