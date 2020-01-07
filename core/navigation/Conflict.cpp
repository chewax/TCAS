#include "Conflict.h"

core::ConflictInfo::ConflictInfo(core::Vector2 traffic_pos, core::Vector2 traffic_dir, double traffic_dist, double self_dist)
  :traffic_position(traffic_pos), traffic_direction(traffic_dir), m_traffic_collision_distance(traffic_dist), m_self_collision_distance(self_dist)
{
  this->collision_point = traffic_pos + (traffic_dir.normalize() * traffic_dist);
  this->conflict = true;
};

core::ConflictInfo::ConflictInfo()
{
  this->conflict = false;
}
