#include <pebble.h>
#include "config.h"



void updateconfig()
{
  showseconds = persist_exists(SHOWSECONDS) ? 
		persist_read_int(SHOWSECONDS) : CONFIG_DEFAULT_SHOWSECONDS;

  showsunrise = persist_exists(SHOWSUNRISE) ? 
		persist_read_int(SHOWSUNRISE) : CONFIG_DEFAULT_SHOWSUNRISE;

  showbat = persist_exists(SHOWBATTERY) ? 
		persist_read_int(SHOWBATTERY) : CONFIG_DEFAULT_SHOWBATTERY;

  showbluetooth = persist_exists(SHOWBLUETOOTH) ? 
		persist_read_int(SHOWBLUETOOTH) : CONFIG_DEFAULT_SHOWBLUETOOTH;

  noseconds_trigger = persist_exists(HIDESECONDS) ? 
		persist_read_int(HIDESECONDS) : CONFIG_DEFAULT_HIDESECONDS;

  language = persist_exists(LANGUAGE) ? 
		persist_read_int(LANGUAGE) : CONFIG_DEFAULT_LANGUAGE;

  dateformat = persist_exists(DATEFORMAT) ? 
		persist_read_int(DATEFORMAT) : CONFIG_DEFAULT_DATEFORMAT;
		
  latitude = persist_exists(GETLATITUDE) ? 
			persist_read_int(GETLATITUDE)/1000000 : GPS_INVALID;
  longitude = persist_exists(GETLONGITUDE) ? 
			persist_read_int(GETLONGITUDE)/1000000 : GPS_INVALID;
  utcoffset = persist_exists(GETUTCOFFSET) ?
			persist_read_int(GETUTCOFFSET) : GPS_INVALID;
}