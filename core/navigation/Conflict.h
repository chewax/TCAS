#pragma once
#include "../math/Vector2.h"

namespace core{

  struct ConflictInfo {
    Vector2 traffic_position;
    Vector2 traffic_direction;
    Vector2 collision_point;
    bool conflict;

    ConflictInfo(Vector2 traffic_pos, Vector2 traffic_dir, double traffic_dist, double self_dist);
    ConflictInfo();

    private:
    double m_traffic_collision_distance;
    double m_self_collision_distance;
    
  };

}