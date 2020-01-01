#include "Aircraft.h"
#include <math.h>

using namespace std;

#define MIN_ACTUAL_SEPARATION 6076.12 * 3 //ft
#define MIN_VERTICAL_SEPARATION 1000 //ft
#define MIN_HORIZONTAL_SEPARATION 6076.12 //ft
#define MIN_TIME_SEPARATION 60 //seconds

Aircraft::Aircraft()
    : lat(0.0), lon(0.0), speed(0), hdg(-1), alt(-1), climb_rate(-1), reg(""), model("") {}

Aircraft::Aircraft(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed)
    : lat(t_lat), lon(t_lon), speed(t_speed), hdg(t_hdg), alt(t_alt), climb_rate(t_climb_rate) {}

Course Aircraft::get_course() const
{
  return Course(lat, lon, alt, hdg, climb_rate, speed);
}

bool Aircraft::intersect_course(const Aircraft &other)
{
  Course self_crs = get_course();
  self_crs.print();

  Course other_crs = other.get_course();
  other_crs.print();
  
  Course coll = Course::shortest_distance(self_crs, other_crs);

  if ( coll.direction.magnitude() >= MIN_ACTUAL_SEPARATION) return false;
  if ( coll.direction.z >= MIN_VERTICAL_SEPARATION) return false;
  if ( sqrt(pow(coll.direction.x, 2) + pow(coll.direction.y, 2)) >= MIN_HORIZONTAL_SEPARATION) return false;

  return true;
  //OTHERWISE ACTUAL RISK OF COLLISION
  //TODO
}