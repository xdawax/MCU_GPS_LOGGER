/*
 * GUI.h
 *
 * Created: 18-02-2019 11:28:11 AM
 *  Author: YashSeeta
 */ 

#ifndef GUI_H_
#define GUI_H_

#define NUM_OPTION 2 

int select_option;
char menu[5][60];

/*
	Draws Menu and updates with selector
*/
void draw_screen();

void init_GUI();

#endif /* GUI_H_ */