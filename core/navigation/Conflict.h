#pragma once
#include "../math/Vector2.h"
#include "../airspace/Drone.h"


namespace core{

  struct Conflict {

    Drone traffic;
    Vector2 collision_point;
    double distance_traffic_collision; //signed
    double distance_self_collision; //signed
    bool conflict;

    Conflict(Drone t_traffic, double t_dtraffic_collision, double t_dself_collision);
    Conflict();

    private:
    double m_traffic_collision_distance;
    double m_self_collision_distance;
  };

}