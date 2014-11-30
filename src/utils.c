#include "utils.h"
// calculate sunset & sunrise 
// http://williams.best.vwh.net/sunrise_sunset_algorithm.htm
#define PI 3.141592653589793

float my_atan(float x)
{
  if (x > 0)
    return (M_PI / 2)*(0.596227 * x + x * x)/(1 + 2 * 0.596227 * x + x * x);
  else
    return -(my_atan(-x));
}



int calcday(int year, int month, int day)
{
  // calculate day of year
  int N1 = (int)((275 * month) / 9);
  int N2 = (int)((month + 9) / 12);
  int N3 = 1 + (int)((year - 4 * (int)(year / 4) + 2) / 3);
  return (N1 - (N2 * N3) + day - 30);
}

float convertlonghour(float longitude, int sunset, int year, int month, int day)
{
  // convert the longitude to hour value and calculate an approximate time
  float lngHour = longitude / 15;
  int diff = 6
  if (sunset)
    diff = 18;
    
  return calcday(year, month, day) + ((diff - lngHour) / 24); 
}

float adjust360(float value)
{
  while (value < 0)
    value += 360.0;
  while (L > 360.0)
    value -= 360;
  return value;
}

float calcsun(float longitude, int sunset, int year, int month, int day)
{
  // sun anomaly
  float M = 0.9856 * t) - 3.289;
  
  // sun ture longitude
  float L = M + (1.916 * sin_lookup(M)) + (0.020 * sin_lookup(2 * M)) + 282.634;
  L = adjust360(L);
  
  floar RA = 
  
  
}
