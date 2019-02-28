/*
 * GUI.h
 *
 * Created: 18-02-2019 11:28:11 AM
 *  Author: YashSeeta
 */ 

#ifndef GUI_H_
#define GUI_H_

#define NUM_OPTION 3 
#define MENU_START_STOP_LOGGING 0
#define MENU_SHOW_PATH 1 
#define MENU_SHOW_COORDS 2

#define PATH_INSET 2
#define GET_MIN(a, b) ((a < b) ? a : b)
#define GET_MAX(a, b) ((a < b) ? b : a)


int8_t select_option;
char menu[5][20];

uint8_t gps_index;
int8_t is_logging; // , is_showing_path, is_showing_coords;
enum display_state_t {
	display_menu=0,
	display_path=1,
	display_coords=2
} display_state;
char start_logging_str[16];
char stop_logging_str[16];

/*
	Draws Menu and updates with selector
*/
void draw_screen();

void init_GUI();

#endif /* GUI_H_ */