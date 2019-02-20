/*
 * GPS_parse.h
 *
 * Created: 2019-02-13 11:49:02
 *  Author: magnu
 */ 


#ifndef GPS_PARSE_H_
#define GPS_PARSE_H_

// uses atoi()-function
#include <stdlib.h>

// uses strcmp()-function
#include <string.h>

#include <stdint.h>


// Can be changed to \r
#define END_CHAR '\r'

/*
Example: $GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C
idx____Name________________Example______Units___Description_______________
00. Message ID          | $GPRMC     |       | RMC protocol header
01. UTC Time            | 064951.000 |       | hhmmss.sss
02. Status              | A          |       | A=data valid or V=data not valid
03. Latitude            | 2307.1256  |       | ddmm.mmmm
04. N/S Indicator       | N          |       | N=north or S=south
05. Longitude           | 12016.4438 |       | dddmm.mmmm
06. E/W Indicator       | E          |       | E=east or W=west
07. Speed over Ground   | 0.03       | knots | 
08. Course over Ground  | 165.48     |degrees| True
09. Date                | 260406     |       | ddmmyy
10. Magnetic Variation  | 3.05, W    |degrees| E=east or W=west 
                        |            |       | (Need GlobalTop Customization Service)
11. Mode                | A          |       | A= Autonomous mode
                        |            |       | D= Differential mode
                        |            |       | E= Estimated mode
12. Checksum            | *2C        |       |
    \r\n                |            |       | End of message termination
*/

// decimal = degrees + minutes/60

typedef struct {
    int32_t lattitude; // micro degrees
    int32_t longitude; // micro degrees 
    int8_t month;
    int8_t day; 
    int8_t hour;
    int8_t minute;
} gps_t;


/*
    @returns: 1 if string starts with "$GPRMC", otherwise 0
*/
int is_gprmc(const char *gps_str);

/*
    @param coord: pointer to gps struct to insert values into 
    @param gstr: $GPRMC-string 
    @returns: 1 if succesful otherwise 0 
*/
int get_gps_coord(gps_t *coord, char *gps_str);

uint32_t string_to_int(char *string);
#endif /* GPS_PARSE_H_ */