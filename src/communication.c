#include "communication.h"
#include "simplemath.h"

void inbox_received(DictionaryIterator *iterator, void *context) {
   Tuple *lat_tuple = dict_find(iterator, GETLATITUDE);
   Tuple *long_tuple = dict_find(iterator, GETLONGITUDE);
   int changed = 0;

   if (lat_tuple != 0 && long_tuple != 0) {
         float latitude = lat_tuple->value->int32;
         latitude /= 1000000;
         float longitude = long_tuple->value->int32;
         longitude /= 1000000;

         if (simple_fabs(real_longitude - longitude) > 0.001) {
             real_longitude = longitude;
	     changed = 1;
	 }

         if (simple_fabs(real_latitude - latitude) > 0.001) {
             real_latitude = latitude;
	     changed = 1;
	}
   }
   
   if (changed)
     forceSunUpdate = 1;
  
}