#pragma once
#include <string>
#include <math.h>
#include "../navigation/Conflict.h"
#include "../math/Vector2.h"
#include "Aircraft.h"

enum class DroneState
{
  NORMAL, MONITORING_TRAFFIC, RESOLVING_CONFLICT
};

class Drone: public Aircraft
{
  DroneState state;

public:
  Drone();
  Drone(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed);
  
  core::Vector2 get_direction() const;
  core::Vector2 get_position() const;

  bool in_violation(const core::ConflictInfo& conflict) const;
  bool theats_ahead(const core::ConflictInfo& conflict) const;
  core::ConflictInfo get_conflict_details(const Drone& a2) const;
  void check_conflict(const Drone& a2) const;
  //Equivalent to resolution advisory on TCAS but instead of advising an action, execute it
  void resolution_actions(const core::ConflictInfo& conflict) const;
  void traffic_advisory (const core::ConflictInfo& conflict) const;
  void resolve_conflict(const core::ConflictInfo& conflict) const;

};
