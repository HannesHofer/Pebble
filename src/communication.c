#include "communication.h"
#include "simplemath.h"

void get_current_location()
{
   Tuplet tuple = TupletInteger(GETGPSCOORDINATES, 1);

   DictionaryIterator *iterator;
   AppMessageResult messageres;

   messageres = app_message_outbox_begin(&iterator);
   if (messageres != APP_MSG_OK || iterator == NULL) {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "app_message_outbox_begin failed");
      return; 
   }


   dict_write_tuplet(iterator, &tuple);
   
   unsigned writeret = dict_write_end(iterator);
   if (writeret == 0)
    return;

   app_message_outbox_send(); 
}

void inbox_received(DictionaryIterator *iterator, void *context) {
   Tuple *lat_tuple = dict_find(iterator, GETLATITUDE);
   Tuple *long_tuple = dict_find(iterator, GETLONGITUDE);
   Tuple *utcoffset_tuple = dict_find(iterator, GETUTCOFFSET);
   
   Tuple *test = dict_find(iterator, 4);
   if (test != 0)
     APP_LOG(APP_LOG_LEVEL_DEBUG, "diogane: %ld", test->value->int32);
     
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

	 //APP_LOG(APP_LOG_LEVEL_DEBUG, "long: %ld, lat:%ld",long_tuple->value->int32, lat_tuple->value->int32);
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

