#pragma once
#include "../math/Vector2.h"
#include "../airspace/Aircraft.h"

namespace core{

  struct ConflictInfo {

    Aircraft traffic;
    Vector2 collision_point;
    bool conflict;

    ConflictInfo(Aircraft traffic, double collision_distance);
    ConflictInfo();

    private:
    double m_traffic_collision_distance;
    double m_self_collision_distance;
  };

}