#pragma once
#include "utils.h"

#define GETGPSCOORDINATES 0 	// for request only
#define GETLATITUDE 1		// KEY top get longitude data from dict 
#define GETLONGITUDE 2		// KEY top get latitude data from dict 

void inbox_received(DictionaryIterator *iterator, void *context);