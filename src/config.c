#include <pebble.h>
#include "config.h"


uint8_t hideseconds;
uint8_t hidesunriseset;
uint8_t hidesecondtime;
uint8_t language;
uint8_t dateformat;

void updateconfig()
{
  hideseconds = persist_exists(HIDESECONDS) ? 
		persist_read_int(HIDESECONDS) : CONFIG_DEFAULT_HIDESECONDS;

  hidesunriseset = persist_exists(HIDESUNRISESET) ? 
		persist_read_int(HIDESUNRISESET) : CONFIG_DEFAULT_HIDESUNRISESET;

  hidesecondtime = persist_exists(HIDESECONDSTIME) ? 
		persist_read_int(HIDESECONDSTIME) : CONFIG_DEFAULT_HIDESECONDSTIME;

  language = persist_exists(LANGUAGE) ? 
		persist_read_int(LANGUAGE) : CONFIG_DEFAULT_LANGUAGE;

  dateformat = persist_exists(DATEFORMAT) ? 
		persist_read_int(DATEFORMAT) : CONFIG_DEFAULT_DATEFORMAT;
}