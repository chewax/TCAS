#ifndef GUARD_aircraft
#define GUARD_aircraft
#include <string>
#include "core.cpp"

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
  bool intersect_course(const Aircraft& target, double& int_lat, double& int_lon);
  Course get_course() const;
};

#endif