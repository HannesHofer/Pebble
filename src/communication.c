#include "communication.h"
#include "simplemath.h"

void inbox_received(DictionaryIterator *iterator, void *context) {
   Tuple *lat_tuple = dict_find(iterator, GETLATITUDE);
   Tuple *long_tuple = dict_find(iterator, GETLONGITUDE);
   int changed = 0;
   
   //error case use old GPS location
   if (lat_tuple->value->int32 == GPS_INVALID ||
       long_tuple->value->int32 == GPS_INVALID)
    return;
   
   if (lat_tuple != 0 && long_tuple != 0) {
	 persist_write_int(GETLATITUDE, lat_tuple->value->int32);
	 persist_write_int(GETLONGITUDE, long_tuple->value->int32);
         float lat = lat_tuple->value->int32 / 1000000;
         float lon = long_tuple->value->int32 / 1000000;

	// APP_LOG(APP_LOG_LEVEL_DEBUG, "long: %d, lat:%d",(int)lon, (int)lat);
         if (simple_fabs(longitude - lon) > 0.001) {
             longitude = lon;
	     changed = 1;
	 }

         if (simple_fabs(latitude - lat) > 0.001) {
             latitude = lat;
	     changed = 1;
	}
   }
   
   if (changed)
     forceSunUpdate = 1;
  
}