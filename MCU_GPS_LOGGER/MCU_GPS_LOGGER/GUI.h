/*
 * GUI.h
 *
 * Created: 18-02-2019 11:28:11 AM
 *  Author: YashSeeta
 */ 


#ifndef GUI_H_
#define GUI_H_


int select_option = 0;
int num_option = 5;
char menu[5][60] = {
	"1.Grab GPS",
	"2.Start GPS",
	"3.Stop GPS",
	"4.Settings",
	"5.Exit"
};

/*
	Draws Menu and updates with selector
*/
void draw_screen();



#endif /* GUI_H_ */