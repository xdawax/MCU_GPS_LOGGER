/*
ATmega8, 48, 88, 168, 328

    /Reset PC6|1   28|PC5      LED
Nokia.SCL  PD0|2   27|PC4      
Nokia.SDIN PD1|3   26|PC3     
Nokia.DC   PD2|4   25|PC2     
Nokia.SCE  PD3|5   24|PC1
Nokia.RST  PD4|6   23|PC0
           Vcc|7   22|Gnd
           Gnd|8   21|Aref
Xtal       PB6|9   20|AVcc
Xtal       PB7|10  19|PB5 SCK  
Switch     PD5|11  18|PB4 MISO 
           PD6|12  17|PB3 MOSI 
           PD7|13  16|PB2      
           PB0|14  15|PB1      
*/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

// display routines for the graphics LCD
#include "nokia5110.h"    
#include <avr/sfr_defs.h>
#include "GUI.h"
#include "EEPROM_translator.h"
// re-useable buffer for numeric-to-text conversion


ISR(PCINT2_vect) 
{
	cli();
	if(bit_is_clear(PIND,PD5))
	{
		PORTC |= (1 << PC5);  // set PC5 to 1
		select_option = (select_option+1)%NUM_OPTION;
		draw_screen();
	} else {
		PORTC &= ~(1 << PC5); // re-set PC5 to 0
	}
	sei();
}


void init_pin_change_interrupt21(void)
{
	PCICR |= (1 << PCIE2); //SET PCIE2 for enabling interrupts ON portD
	PCMSK2 |= (1 << PCINT21); // set mask to look at PCINT21
	sei();
}


void draw_screen() {
	NOKIA_clear();
	int8_t i=0;
	int8_t num_coords = get_num_coordinates();
	char buffer[20];
	sprintf(buffer, "Coords: %d", num_coords);
	NOKIA_print(0,0,buffer,2);
	NOKIA_print(0,(2+select_option)*8,">",0);
	for (i=0; i<2; i++)
	{
		NOKIA_print(6,8*(i+2),menu[i], 0);
	}
	NOKIA_update();
	_delay_ms(100);
}


void init_GUI() 
{
	strcpy(menu[0], "Start logging" );
	strcpy(menu[1], "Display path" );
	select_option = 0;
	
	NOKIA_init(0);
	NOKIA_LED_ENABLE();
	NOKIA_setVop(68);
	DDRC = 0x05;
	DDRD &= ~(1<<PD5);
	PORTD |= (1 << PD5);
	init_pin_change_interrupt21();
	draw_screen();
}

/*
int main(void)
{
	init_GUI();
			
	while (1); 
}*/
