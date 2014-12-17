#pragma once
#include "utils.h"

// default config values
#define CONFIG_DEFAULT_HIDESECONDS 		0
#define CONFIG_DEFAULT_HIDESUNRISESET 		0
#define CONFIG_DEFAULT_HIDESECONDSTIME		5
#define CONFIG_DEFAULT_LANGUAGE			0 // 0 == auto
#define CONFIG_DEFAULT_DATEFORMAT		7 // 0 == std. europe

extern uint8_t hideseconds;
extern uint8_t hidesunriseset;
extern uint8_t hidesecondtime;
extern uint8_t language;
extern uint8_t dateformat;

void updateconfig();