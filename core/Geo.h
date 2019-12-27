#pragma once
#include <math.h>
#include <string>

namespace core::geo
{
  const float NM2FT = 6076.12;
  const float KT2FTM = 101.269;
  const float DEG2RAD = M_PI / 180.0;
  const double COORDTOFT = (10000 / 90) * 3280.4;

  double to_rad(int deg);
  double kts_to_ftm(int kts);
  double nms_to_fts(int nm);

  class Coord
  {
    double lat, lon;

  public:
    static double to_fts(double value)
    {
      return value * COORDTOFT;
    }

    Coord(double lat, double lon)
    {
      this->lat = COORDTOFT * lat;
      this->lon = COORDTOFT * lon;
    }

    std::string to_string()
    {
      return "( " + std::to_string(lat) + ", " + std::to_string(lon) + " )";
    }
    
  };

} // namespace core::geo