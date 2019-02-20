/*
 * GPS_parse.c
 *
 * Created: 2019-02-13 11:48:32
 *  Author: magnu
 */ 


#include "GPS_parse.h"

int is_gprmc(const char *gps_str) {
	char gprmc[8] = "\n$GPRMC";
	int i;
	for (i = 0; i < 7; i++) {
		if (gps_str[i] == '\0') return 0;
		if (gps_str[i] != gprmc[i]) return 0;
	}
	return 1;
}


/*
    @param dest: writes to dest  
    @param gstr: $GPRMC-string 
    @param arg_n: index of argument in string 
*/
void extract_arg_gstr(char *dest, char *gstr, int arg_n) {
	int arg_i = 0;
	int dest_i = 0;
	int i;
	for (i = 0; ; i++) {
		if (gstr[i] == ',') {
			arg_i++;
			} else if (arg_n == arg_i) {
			dest[dest_i] = gstr[i];
			dest_i++;
			} else if (arg_n < arg_i) {
			dest[dest_i] = '\0';
			return;
		}
		if (gstr[i] == END_CHAR) {
			dest[dest_i] = '\0';
			return;
		}
	}
}

int get_lattitude(gps_t *coord, char *gps_str) {
	char lat_str[16];
	extract_arg_gstr(lat_str, gps_str, 3);
	if(lat_str[0] == '\0') return 0;
	char deg_str[16];
	char min_str[16];
	
	int i;
	for (i = 0; i < 2; i++) deg_str[i] = lat_str[i];
	deg_str[2] = '\0';
	for (i = 2; i < 4; i++) min_str[i-2] = lat_str[i];
	for (i = 5; i < 9; i++) min_str[i-3] = lat_str[i];
	min_str[6] = '\0';

	char dir_str[8];
	int32_t direction = 1;
	extract_arg_gstr(dir_str, gps_str, 4);
	if (strcmp(dir_str, "S") == 0) direction *= -1;

	coord->lattitude = direction*(atoi(deg_str)*1000000 + (100*atoi(min_str))/60);
	return 1;
}


int get_longitude(gps_t *coord, char *gps_str) {
	char lon_str[16];
	extract_arg_gstr(lon_str, gps_str, 5);
	if(lon_str[0] == '\0') return 0; 
	char deg_str[16];
	char min_str[16];

	int i;
	for (i = 0; i < 3; i++) deg_str[i] = lon_str[i];
	deg_str[3] = '\0';
	for (i = 3; i < 5; i++) min_str[i-3] = lon_str[i];
	for (i = 6; i < 10; i++) min_str[i-4] = lon_str[i];
	min_str[6] = '\0';

	char dir_str[8];
	int32_t direction = 1;
	extract_arg_gstr(dir_str, gps_str, 6);
	if (strcmp(dir_str, "W") == 0) direction *= -1;

	coord->longitude = direction*(atoi(deg_str)*1000000 + (100*atoi(min_str))/60);
	return 1;
}

int get_date(gps_t *coord, char *gps_str) {
	char date_str[8];
	extract_arg_gstr(date_str, gps_str, 9);
	if(date_str[0] == '\0') return 0;
	char month_str[8];
	char day_str[8];

	month_str[0] = date_str[2];
	month_str[1] = date_str[3];
	month_str[2] = '\0';

	day_str[0] = date_str[0];
	day_str[1] = date_str[1];
	day_str[2] = '\0';

	coord->month = (int8_t) atoi(month_str);
	coord->day = (int8_t) atoi(day_str);
	return 1;
}

int get_time(gps_t *coord, char *gps_str) {
	char time_str[8];
	extract_arg_gstr(time_str, gps_str, 1);
	if(time_str[0] == '\0') return 0;
	char hour_str[8];
	hour_str[0] = time_str[0];
	hour_str[1] = time_str[1];
	hour_str[2] = '\0';
	coord->hour = (int8_t) atoi(hour_str);

	char min_str[8];
	min_str[0] = time_str[2];
	min_str[1] = time_str[3];
	min_str[2] = '\0';
	coord->minute = (int8_t) atoi(min_str);
	return 1;
}

int get_gps_coord(gps_t *coord, char *gps_str) {
	if ( ! get_lattitude(coord, gps_str) ) return 0;
	if ( ! get_longitude(coord, gps_str) ) return 0;
	if ( ! get_date(coord, gps_str) ) return 0;
	if ( ! get_time(coord, gps_str) ) return 0;
	return 1;
}
