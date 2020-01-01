#pragma once
#include <string>
#include "core/Course.h"

class Aircraft
{

public:
  double lat;
  double lon;
  int speed;
  int hdg;
  int alt;
  int climb_rate;
  std::string reg;
  std::string model;

  Aircraft();
  Aircraft(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed);

  bool intersect_course(const Aircraft& target);
  Course get_course() const;
};