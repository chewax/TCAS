#include "Conflict.h"

core::Conflict::Conflict(Drone t_traffic, double t_dtraffic_collision, double t_dself_collision)
{
  this->traffic = t_traffic;
  this->distance_traffic_collision = t_dtraffic_collision; //signed
  this->distance_self_collision = t_dself_collision; //signed
  this->collision_point = t_traffic.get_position() + (t_traffic.get_direction().normalize() * t_dtraffic_collision);
  this->conflict = true;
};

core::Conflict::Conflict()
{
  this->conflict = false;
}
