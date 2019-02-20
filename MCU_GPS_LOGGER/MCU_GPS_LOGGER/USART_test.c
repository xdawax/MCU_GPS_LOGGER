/*
 * USART_test.c
 *
 * Created: 2019-02-20 14:37:22
 *  Author: dawa
 */ 
#include "USART_test.h"

char lat_string[6] = "502621";

void USART_test_word() {
	uint32_t max = 4294967295;
	uint32_t min = 0;
	uint32_t meh = 2345678762;
	uint32_t mdeg  = 837701666;
	uint32_t real_deg = atoi(lat_string);
	
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
	USART_transmit_string("\n\r");
	USART_transmit_string(lat_string);
	USART_transmit_string("EXPECTING 502621");
	USART_transmit_string("\n\rGOT: ");
	USART_transmit_word(real_deg);
	if (real_deg == 4294945629) {
		USART_transmit_string("\n\rCRYYYYYY!\n\r");
	}
	USART_transmit_string("TEST COMPLETED: USART_transmit_word from USART.c\n\n\r");
	

}
void USART_test_all() {
	USART_test_word();
}