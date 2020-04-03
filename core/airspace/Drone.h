#pragma once
#include <string>
#include <math.h>
#include "../math/Vector2.h"

//Forward declaration of Conflict
namespace core {
  struct Conflict;
}

enum class DroneState
{
  NORMAL, MONITORING_TRAFFIC, RESOLVING_CONFLICT
};

class Drone
{
  DroneState state;
  
protected:
  core::Vector2 m_position;
  core::Vector2 m_direction;
  double m_lat;
  double m_lon;

public:
  Drone();
  Drone(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed);
  
  core::Vector2 get_direction() const;
  core::Vector2 get_position() const;

  bool in_violation(const core::Conflict& conflict) const;
  bool theats_ahead(const core::Conflict& conflict) const;
  core::Conflict get_conflict_details(const Drone& a2) const;
  void check_conflict(const Drone& a2) const;

  //Equivalent to resolution advisory on TCAS but instead of advising an action, execute it
  void resolution_actions(const core::Conflict& conflict) const;
  void traffic_advisory (const core::Conflict& conflict) const;
  void resolve_conflict(const core::Conflict& conflict) const;

  int speed;
  int hdg;
  int alt;
  int climb_rate;
};
