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


double operator "" _kts (unsigned long long val)
{
  return val * KT2FTM;
}

double operator "" _kmh (unsigned long long val)
{
  return val * KMH2FTM;
}

double operator "" _ftm (unsigned long long val)
{
  return val;
}

double operator "" _nm (unsigned long long val)
{
  return val * NM2FT;
}

double operator "" _km (unsigned long long val)
{
  return val * KM2FT;
}

double operator "" _sm (unsigned long long val)
{
  return val * SM2FT;
}
