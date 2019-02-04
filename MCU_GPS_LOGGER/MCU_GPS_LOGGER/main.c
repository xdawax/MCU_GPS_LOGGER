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

    /* Replace with your application code */
    while (1) 
    {
	USART_receive_byte();
    }
	return 0;
}

