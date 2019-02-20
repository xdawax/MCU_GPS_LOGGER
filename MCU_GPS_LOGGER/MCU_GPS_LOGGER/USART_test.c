/*
 * USART_test.c
 *
 * Created: 2019-02-20 14:37:22
 *  Author: dawa
 */ 
#include "USART_test.h"


void USART_test_word() {
	uint32_t max = 4294967295;
	uint32_t min = 0;
	uint32_t meh = 2345678762;
	uint32_t mdeg  = 837701666;
	
	USART_transmit_string("TESTING: USART_transmit_word from USART.c\n\r");
	USART_transmit_string("\n\rEXPECTING: 4294967295");
	USART_transmit_string("\n\rGOT: ");
	USART_transmit_word(max);
	USART_transmit_string("\n\rEXPECTING: 0");
	USART_transmit_string("\n\rGOT: ");
	USART_transmit_word(min);
	USART_transmit_string("\n\rEXPECTING: 2345678762");
	USART_transmit_string("\n\rGOT: ");
	USART_transmit_word(meh);
	USART_transmit_string("\n\rEXPECTING: 837701666");
	USART_transmit_string("\n\rGOT: ");
	USART_transmit_word(mdeg);
	USART_transmit_string("\n\rTEST COMPLETED: USART_transmit_word from USART.c\n\n\r");
	

}
void USART_test_all() {
	USART_test_word();
}