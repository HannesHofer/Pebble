#pragma once
#include "utils.h"

void get_current_location();
void inbox_received(DictionaryIterator *iterator, void *context);
void update_sunrisesetimage(uint8_t usestored);