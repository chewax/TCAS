#pragma once
#include <math.h>

//Navigation
#define VERTICAL_SEPARATION_MINIMUMS 1000 //ft
#define LATERAL_SEPARATION_MINIMUMS 6076.12 //ft
#define TIME_SEPARATION_MINIMUMS 60 //seconds

//Conversion units
#define NM2FT 6076.12     //nautical mile to feet
#define KM2FT 3280.84     //km to feet
#define SM2FT 5280        //statute mile to feet
#define KT2FTM 101.269    //kts to feet per minute
#define KMH2FTM 54.6807   //kmh to feet per minute
#define DEG2RAD (M_PI / 180.0)


int operator "" _kts (int val)
{
  return val * KT2FTM;
}

int operator "" _kmh (int val)
{
  return val * KMH2FTM;
}

int operator "" _ftm (int val)
{
  return val;
}

double operator "" _nm (int val)
{
  return val * NM2FT;
}

double operator "" _km (int val)
{
  return val * KM2FT;
}

double operator "" _sm (int val)
{
  return val * SM2FT;
}
