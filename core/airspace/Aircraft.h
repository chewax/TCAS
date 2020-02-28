#pragma once
#include <string>
#include <math.h>
#include "../math/Vector2.h"

// #define KT2FTM 101.269

// class Speed
// {
//   int m_val; //to be stored in feets per minute

//   public:
//   Speed(): m_val(0f) {}
//   Speed(int val): m_val(val) {}

//   int operator "" _kts (int val)
//   {
//     return 
//   }

// }

class Aircraft
{

protected:
  core::Vector2 m_position;
  core::Vector2 m_direction;
  double m_lat;
  double m_lon;

public:
  int speed;
  int hdg;
  int alt;
  int climb_rate;
  std::string reg;
  std::string model;

  Aircraft();
  Aircraft(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed);
  virtual core::Vector2 get_direction() const;
  virtual core::Vector2 get_position() const;
};

