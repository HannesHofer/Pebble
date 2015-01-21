#pragma once
#include <pebble.h>

#define TIMEZONE  1.0
#define GPS_INVALID 99999

// Persistant storage information
#define GETGPSCOORDINATES	0	// for request only
#define GETLATITUDE		1	// KEY to get longitude data from dict 
#define GETLONGITUDE		2	// KEY to get latitude data from dict 
#define GETUTCOFFSET		3	// KEY to get utcoffset data from dict
#define SHOWSECONDS		4
#define SHOWSUNRISE		5
#define HIDESECONDS		6
#define LANGUAGE		7
#define DATEFORMAT		8
#define SHOWBATTERY		9
#define SHOWBLUETOOTH		10


// custom globals
static char* days[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
static uint8_t bat_level = 0;
static GBitmap *s_res_nobluetooth;
static GColor drawcolor = GColorBlack;
static GPath *edge_path[4];
static const GPathInfo BOLT_PATH_INFO = {
  .num_points = 6,
  .points = (GPoint []) {{-1, 8}, {2, 8}, {7, 3}, {4, 0}, {-1, 5}, {-1, 8}}
};
static uint8_t seconds_startdraw[] = {66, 75, 84, 93, 102, 111, 121, 130, 140, 1,
                                      11, 22, 33, 44, 55, 66, 77, 88, 99, 110,
                                      121, 132, 142, 140, 130, 121, 111, 102, 93, 84, 
                                      75, 66, 57, 48, 39, 30, 20, 11, 0, 142,
                                      132, 121, 110, 99, 88, 77, 66, 55, 44, 33,
                                      22, 11, 1, 0, 11, 20, 30, 39, 48, 57};

static GColor not_drawcolor() {
  return drawcolor == GColorBlack ? GColorWhite : GColorBlack;
}

float calcsun(float longitude, float latitude, int sunset, struct tm *current_time);

extern float latitude;
extern float longitude;
extern int32_t utcoffset;
extern int forceSunUpdate;
extern uint8_t showseconds;
extern uint8_t showsunrise;
extern uint8_t language;
extern uint8_t dateformat;
extern uint16_t noseconds_trigger;
extern uint8_t showbat;
extern uint8_t showbluetooth;
