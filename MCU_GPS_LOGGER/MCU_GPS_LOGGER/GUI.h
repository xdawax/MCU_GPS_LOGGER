/*
 * GUI.h
 *
 * Created: 18-02-2019 11:28:11 AM
 *  Author: YashSeeta
 */ 

#ifndef GUI_H_
#define GUI_H_

#define NUM_OPTION 2 
#define MENU_START_STOP_LOGGING 0
#define MENU_SHOW_PATH 1 

#define PATH_INSET 2

int8_t select_option;
char menu[5][60];

int8_t is_logging;
int8_t is_showing_path;
char start_logging_str[16];
char stop_logging_str[16];

/*
	Draws Menu and updates with selector
*/
void draw_screen();

void init_GUI();

#endif /* GUI_H_ */