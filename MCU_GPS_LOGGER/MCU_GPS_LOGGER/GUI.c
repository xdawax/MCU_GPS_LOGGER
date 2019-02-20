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

gps_t coord_arr[8]; 


ISR(PCINT2_vect) 
{
	if(bit_is_clear(PIND,PD5))
	{
		select_option = (select_option+1)%NUM_OPTION;
		draw_screen();
	}
	if(bit_is_clear(PIND,PD6)) {
		if (is_showing_path) {
			is_showing_path = 0;
		} else if (select_option == MENU_START_STOP_LOGGING) {
			is_logging = !is_logging;
		} else if (select_option == MENU_SHOW_PATH) {
			// --- switch to showing path mode here --- 
			is_showing_path = 1;
			// PORTC |= (1 << PC5); // LED-Display
		} 
		draw_screen();	
	}
}


void init_pin_change_interrupt21(void)
{
	PCICR |= (1 << PCIE2); // SET PCIE2 for enabling interrupts ON portD
	PCMSK2 |= (1 << PCINT21) | (1 << PCINT22); // set mask to look at PCINT21 and PCINT22 
	sei();
}


void draw_path(uint32_t num_coords) {
	gps_t coord;
	uint8_t i;
	coord = coord_arr[0]; // get_struct(0, &coord);
	int32_t min_lon = coord.longitude;
	int32_t max_lon = coord.longitude;
	int32_t min_lat = coord.lattitude;
	int32_t max_lat = coord.lattitude;
	
	/* get minimum and maxim values */
	for (i = 1; i < num_coords ; i++ ) {
		coord = coord_arr[i]; // get_struct(i, &coord);
		if(min_lon > coord.longitude) {
			min_lon = coord.longitude;
		} else if (max_lon < coord.longitude) {
			max_lon = coord.longitude;
		}
		if(min_lat > coord.lattitude){
			min_lat = coord.lattitude;
		} else if (max_lat < coord.lattitude){
			max_lat = coord.lattitude;
		}
	}
	
	/* calculate scale constants */
	const int32_t slope_lon = (max_lon - min_lon)/(NOKIASIZEX-4);
	const int32_t slope_lat = (max_lat - min_lat)/(NOKIASIZEY-4);
	/* actually draw path */
	
	uint8_t x,y;
	for(i= 0; i < num_coords; i++){
		coord = coord_arr[i]; // get_struct(i, &coord);
		x = (uint8_t)((coord.longitude - min_lon + slope_lon*2)/slope_lon);
		y = (uint8_t)((coord.lattitude - min_lat + slope_lat*2)/slope_lat);
		NOKIA_setpixel(x,y);
		NOKIA_setpixel(x+1,y+1);
		NOKIA_setpixel(x-1,y-1);
		NOKIA_setpixel(x+1,y-1);
		NOKIA_setpixel(x-1,y+1);
	}
}

void draw_path_screen() {
	uint8_t num_coords = 7;// get_num_coordinates();
	if (num_coords > 1) {
		draw_path(num_coords);
	} else {
		NOKIA_print(0, 0, "Not enough", 0);
		NOKIA_print(0, 8, "coords", 0);
	}
}

void draw_menu_screen() {
	uint8_t num_coords = get_num_coordinates();
	if (is_logging) {
		strcpy(menu[0], stop_logging_str);
	} 
	else {
		strcpy(menu[0], start_logging_str);
	}
	char buffer[20];
	sprintf(buffer, "Coords: %d", num_coords);
	NOKIA_print(0,0,buffer,2);
	NOKIA_print(0,(2+select_option)*8,">",0);
	int8_t i=0;
	for (i=0; i<2; i++)
	{
		NOKIA_print(6,8*(i+2),menu[i], 0);
	}
}

void draw_screen() {
	NOKIA_clearbuffer();
	if (is_showing_path) {
		draw_path_screen();
	} else {
		draw_menu_screen();
	}
	NOKIA_update();
	_delay_ms(100);
}


void init_GUI() 
{
	/* Setting  variables */
	is_logging = 0;
	is_showing_path = 0;
	strcpy(start_logging_str, "Start logging");
	strcpy(stop_logging_str, "Stop logging");
	strcpy(menu[0], start_logging_str );
	strcpy(menu[1], "Display path" );
	select_option = 0;
	
	/* Initiazing nokia display */
	NOKIA_init(0);
	NOKIA_LED_ENABLE();
	NOKIA_setVop(68);
	
	/* Setting up input pins */
	DDRC |= (1 << PC5);		// Set Pin C5 to output  (LED pin)
	DDRD &= ~(1 << PD5);	// Make pin D5 input (button down)
	PORTD |= (1 << PD5);
	DDRD &= ~(1 << PD6);	// Make pin D6 input (button select)
	PORTD |= (1 << PD6); 
	
	coord_arr[0].longitude = 51200; coord_arr[0].lattitude = 60800;
	coord_arr[1].longitude = 52400; coord_arr[1].lattitude = 64000;
	coord_arr[2].longitude = 53600; coord_arr[2].lattitude = 60800;
	coord_arr[3].longitude = 54800; coord_arr[3].lattitude = 64400;
	coord_arr[4].longitude = 56400; coord_arr[4].lattitude = 60000;
	coord_arr[5].longitude = 58800; coord_arr[5].lattitude = 62800;
	coord_arr[6].longitude = 50400; coord_arr[6].lattitude = 62300;
	
	init_pin_change_interrupt21();
	draw_screen();
}

/*
int main(void)
{
	init_GUI();
			
	while (1); 
}*/
