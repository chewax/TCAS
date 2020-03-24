#include "Aircraft.h"

using namespace std;

Aircraft::Aircraft()
    : lat(0.0f), lon(0.0f), speed(0), hdg(-1), alt(-1), climb_rate(-1), reg(""), model("") {}

Course Aircraft::get_course() const
{
  return Course(lat, lon, alt, hdg, climb_rate, speed);
}

bool Aircraft::intersect_course(const Aircraft &other, double &int_lat, double &int_lon)
{
  Course self_crs = get_course();
  Course other_crs = other.get_course();
  Course coll = Course::shortest_distance(self_crs, other_crs);
}