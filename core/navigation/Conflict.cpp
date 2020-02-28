#include "Conflict.h"

core::ConflictInfo::ConflictInfo(Aircraft traffic, double collision_distance)
{
  this->traffic = traffic;
  this->collision_point = traffic.get_position() + (traffic.get_direction().normalize() * collision_distance);
  this->conflict = true;
};

core::ConflictInfo::ConflictInfo()
{
  this->conflict = false;
}
