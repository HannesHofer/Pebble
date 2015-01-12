#include "utils.h"
#include "simplemath.h"

#define ZENITH_OFFICIAL 90.83333
#define ZENITH_CIVIL 96.0
#define ZENITH_NAUTICAL 102.0
#define ZENITH_ASTRONOMICAL 108.0

#define ZENITH ZENITH_OFFICIAL
// calculate sunset & sunrise 
// http://williams.best.vwh.net/sunrise_sunset_algorithm.htm

float adjust360(float value)
{
  if (value < 0)
    value += 360.0;
  if (value > 360.0)
    value -= 360;
  return value;
}

int calcday(struct tm *current_time)
{
  int year = current_time->tm_year;
  int month = current_time->tm_mon+1;
  int day = current_time->tm_mday;
  
  // calculate day of year
  int N1 = simple_floor(275 * month / 9);
  int N2 = simple_floor((month + 9) / 12);
  int N3 = 1 + simple_floor((year - 4 * simple_floor(year / 4) + 2) / 3);
  return (N1 - (N2 * N3) + day - 30);
}

float convertlonghour(float longitude, int sunset, struct tm *current_time)
{
  // convert the longitude to hour value and calculate an approximate time
  float lngHour = longitude / 15;
  int diff = 6;
  if (sunset)
    diff = 18;
    
  return calcday(current_time) + ((diff - lngHour) / 24); 
}

void Timezone(float* time)
{
  *time += ((float)utcoffset)/60;
  if (*time > 24) *time -= 24;
  if (*time < 0) *time += 24;
}

float calcsun(float longitude, float latitude, int sunset, 
	      struct tm *current_time)
{
  float t = convertlonghour(longitude, sunset, current_time);
  // sun anomaly
  float M = (0.9856 * t) - 3.289;
  
  // sun true longitude
  float L = M + (1.916 * simple_sin((M_PI / 180.0f) * M)) + 
            (0.020 * simple_sin((M_PI / 180.0f) * 2 * M)) + 282.634;
  L = adjust360(L);
  
  // sun right ascension
  float RA = (180.0f / M_PI) * 
             simple_atan(0.91764 * simple_tan((M_PI / 180.0f) * L));
  RA = adjust360(RA);
  
  // right ascension value needs to be in the same quadrant as L
  float Lquadrant = simple_floor(L / 90) * 90;
  float RAquadrant = simple_floor(RA / 90) * 90;
  RA += Lquadrant - RAquadrant;
  RA /= 15;
  // sun declination
  float sinDec = 0.39782 * simple_sin((M_PI / 180.0f) * L);
  float cosDec = simple_cos(simple_asin(sinDec));
  
  // sun local hour angle
  float cosH = (simple_cos((M_PI / 180.0f) * ZENITH) -
	       (sinDec * simple_sin((M_PI / 180.0f) * latitude))) /
	       (cosDec * simple_cos((M_PI / 180.0f) * latitude));
  
  if (cosH > 1 || cosH < -1)
    return -1.0;
  
  // convert into hours
  
  float H;
  if (sunset)
    H = (180.0f / M_PI) * simple_acos(cosH);
  else
    H = 360 - ((180.0f / M_PI) * simple_acos(cosH));
  
  H /= 15;
  
  // calculate local mean time
  float T = H + RA - (0.06571 * t) - 6.622;
  
  // convert to UTC
  float UT = T - (longitude / 15);

  if (UT < 0)
    UT += 24;
  else if (UT > 24)
    UT -= 24;
  
  Timezone(&UT);
    
  return UT;
}


