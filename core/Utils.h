#pragma once
#include <math.h>
#include <string>

namespace core
{
  const float NM2FT = 6076.12;
  const float KT2FTM = 101.269;
  const float DEG2RAD = M_PI / 180.0;
  const double COORDTOFT = (10000/90) * 3280.4;

  double to_rad(int deg);
  double kts_to_ftm(int kts);
  double nms_to_fts(int nm);
  double coord_to_ft(double coord);
  void log(std::string& text);
} // namespace core