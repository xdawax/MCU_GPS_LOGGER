/*
 * GPS_test.c
 *
 * Created: 2019-02-01 11:15:01
 * Author : dawa
 */ 
#include <avr/io.h>
#include "USART.h"

int main(void)
{
	USART_init();
	char test_message[8] = {'T', 'X', ':', 'O', 'K', '\n', '\r', '\0'};
	char buf[BUF_SIZE];
	
	for (int i = 0; i < BUF_SIZE; i++)
	{
		buf[i] = 0;
	}
	char byte;
    /* Replace with your application code */
    while (1) 
    {
		byte = USART_receive_byte();
		//USART_receive_string(buf, BUF_SIZE);
		//USART_transmit_string(buf);
    }
	return 0;
}

