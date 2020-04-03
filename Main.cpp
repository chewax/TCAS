#include "./core/airspace/Drone.h"

int main () 
{
  Drone d1(51.463543, -0.523353, 5000, 360, 0, 5);
  Drone d2(51.4686977, -0.542833, 5000, 90, 0, 5);
  d1.check_conflict(d2);

  return 0;
}