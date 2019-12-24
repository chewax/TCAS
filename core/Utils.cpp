#include "Utils.h"
#include <math.h>
#include <iostream>

using namespace std;

const float NM2FT = 6076.12;
const float KT2FTM = 101.269;
const float DEG2RAD = M_PI / 180.0;

double to_rad(int deg)
{
  return deg * DEG2RAD;
}

double kts_to_ftm(int kts)
{
  return kts * KT2FTM;
}

double nms_to_fts(int nm)
{
  return nm * NM2FT;
}

void log(string& text)
{
  cout << text << endl;
}