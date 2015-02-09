#include "communication.h"
#include "simplemath.h"
#include "config.h"

void get_current_location()
{
   Tuplet tuple = TupletInteger(GETGPSCOORDINATES, 1);

   DictionaryIterator *iterator;
   AppMessageResult messageres;

   messageres = app_message_outbox_begin(&iterator);
   if (messageres != APP_MSG_OK || iterator == NULL) {
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "app_message_outbox_begin failed");
      return; 
   }


   dict_write_tuplet(iterator, &tuple);
   
   unsigned writeret = dict_write_end(iterator);
   if (writeret == 0)
    return;

   app_message_outbox_send(); 
}

void GPSrefresh(DictionaryIterator *iterator);
void settings(DictionaryIterator *iterator);


void inbox_received(DictionaryIterator *iterator, void *context) {
   Tuple *isconfiguration = dict_find(iterator, SHOWSECONDS);
   if (isconfiguration)
     settings(iterator);    
   else
     GPSrefresh(iterator);  
}

void settings(DictionaryIterator* iterator)
{
    Tuple *showseconds = dict_find(iterator, SHOWSECONDS);
    Tuple *sunrise = dict_find(iterator, SHOWSUNRISE);
    Tuple *nomovement = dict_find(iterator, HIDESECONDS);
    Tuple *language = dict_find(iterator, LANGUAGE);
    Tuple *dateformat = dict_find(iterator, DATEFORMAT);
    Tuple *bat = dict_find(iterator, SHOWBATTERY);
    Tuple *bluetooth = dict_find(iterator, SHOWBLUETOOTH);
    Tuple *graceful = dict_find(iterator, GRACEFULSTOP);
    Tuple *rectangle = dict_find(iterator, SHOWRECTANGLE);
   
    persist_write_int(SHOWSECONDS, atoi(showseconds->value->cstring));
    persist_write_int(SHOWSUNRISE, atoi(sunrise->value->cstring));
    persist_write_int(SHOWBATTERY, atoi(bat->value->cstring));
    persist_write_int(SHOWBLUETOOTH, atoi(bluetooth->value->cstring));
    persist_write_int(HIDESECONDS, atoi(nomovement->value->cstring));
    persist_write_int(LANGUAGE, atoi(language->value->cstring));
    persist_write_int(DATEFORMAT, atoi(dateformat->value->cstring));
    persist_write_int(GRACEFULSTOP, atoi(graceful->value->cstring));
    persist_write_int(SHOWRECTANGLE, atoi(rectangle->value->cstring));
    
    updateconfig();
    updateUIforConfig();
    
}


void GPSrefresh(DictionaryIterator *iterator) {
   //APP_LOG(APP_LOG_LEVEL_DEBUG, "GPSrefresh");
   Tuple *lat_tuple = dict_find(iterator, GETLATITUDE);
   Tuple *long_tuple = dict_find(iterator, GETLONGITUDE);
   Tuple *utcoffset_tuple = dict_find(iterator, GETUTCOFFSET);
   
   int changed = 0;
   
   //error case use old GPS location
   if (lat_tuple->value->int32 == GPS_INVALID ||
       long_tuple->value->int32 == GPS_INVALID ||
       utcoffset_tuple->value->int32 == GPS_INVALID) {
     update_sunrisesetimage(1);
     return;
   }
   
   if (lat_tuple != 0 && long_tuple != 0 && utcoffset != 0) {
	 persist_write_int(GETLATITUDE, lat_tuple->value->int32);
	 persist_write_int(GETLONGITUDE, long_tuple->value->int32);
	 persist_write_int(GETUTCOFFSET, utcoffset_tuple->value->int32);
	 utcoffset = utcoffset_tuple->value->int32;

         float lat = lat_tuple->value->int32 / 1000000;
         float lon = long_tuple->value->int32 / 1000000;

         if (simple_fabs(longitude - lon) > 0.001) {
             longitude = lon;
	     changed = 1;
	 }

         if (simple_fabs(latitude - lat) > 0.001) {
             latitude = lat;
	     changed = 1;
	}
	
	if (!changed)
	  update_sunrisesetimage(0);
   }
   
   if (changed)
     forceSunUpdate = 1;
}