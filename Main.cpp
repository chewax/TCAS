#include "./core/airspace/Drone.h"

int main () 
{

  // Drone(double lat, double lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed);
  Drone d1(100.000, 50.000, 5000, 360, 0, 80);
  Drone d2(90.000, 60.000, 5000, 90, 0, 80);
  d1.check_conflict(d2);

  return 0;

}