#include "Aircraft.h"
#include "../utils/Utils.h"

Aircraft::Aircraft()
    : m_lat(0.0), m_lon(0.0), speed(0), hdg(-1), alt(-1), climb_rate(-1), reg(""), model("") {}

Aircraft::Aircraft(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed)
    : m_lat(t_lat), m_lon(t_lon), speed(t_speed), hdg(t_hdg), alt(t_alt), climb_rate(t_climb_rate) {}

core::Vector2 Aircraft::get_direction() const
  {
    return m_direction;
  }

core::Vector2 Aircraft::get_position() const
  {
    return m_position;
  }