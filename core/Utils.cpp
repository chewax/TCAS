
#include "Utils.h"
#include <iostream>

using namespace std;
using namespace core;

double core::to_rad(int deg)
{
  return deg * DEG2RAD;
}

double core::kts_to_ftm(int kts)
{
  return kts * KT2FTM;
}

double core::nms_to_fts(int nm)
{
  return nm * NM2FT;
}

void core::log(string& text)
{
  cout << text << endl;
}

double core::coord_to_ft(double coord)
{
  return coord * COORDTOFT;
}