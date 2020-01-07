#pragma once
#include <string>
#include <math.h>
#include "../navigation/Conflict.h"
#include "../math/Vector2.h"

enum class DroneState
{
  NORMAL, MONITORING_TRAFFIC, RESOLVING_CONFLICT
};

class Drone
{

private:
  core::Vector2 m_position;
  core::Vector2 m_direction;
  double m_lat;
  double m_lon;
  DroneState state;

public:
  int speed;
  int hdg;
  int alt;
  int climb_rate;
  std::string reg;
  std::string model;

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
