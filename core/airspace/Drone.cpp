#include "Drone.h"
#include "../utils/Utils.h"


Drone::Drone()
  : m_lat(0.0), m_lon(0.0), speed(0), hdg(-1), alt(-1), climb_rate(-1), reg(""), model("") {}

Drone::Drone(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed)
  : m_lat(t_lat), m_lon(t_lon), speed(t_speed), hdg(t_hdg), alt(t_alt), climb_rate(t_climb_rate) 
  {
    m_position = core::Vector2(t_lat, t_lon);
    double rads = core::Utils::to_rad(t_hdg);
    m_direction = core::Vector2( sin(rads) , cos(rads) );
    state = DroneState::NORMAL;
  }

core::Vector2 Drone::get_direction() const
  {
    return m_direction;
  }

core::Vector2 Drone::get_position() const
  {
    return m_position;
  }

  bool Drone::in_violation(const core::ConflictInfo& conflict) const
  {
    return false;
  }

  bool Drone::theats_ahead(const core::ConflictInfo& conflict) const
  {
    return true;
  }

  core::ConflictInfo Drone::get_conflict_details(const Drone& a2) const
  {
    core::Vector2 ad = this->get_direction();
    core::Vector2 bd = a2.get_direction();
    double dx = a2.get_position().x - this->get_position().x;
    double dy = a2.get_position().y - this->get_position().y;
    double det = bd.x * ad.y - bd.y * ad.x;

    if (det == 0) return core::ConflictInfo();
  
    double u = (dy * bd.x - dx * bd.y) / det; // a1's distance from point of convergence
    double v = (dy * ad.x - dx * ad.y) / det; // a2's distance from point of convergence
    
    return core::ConflictInfo(a2.get_position(), a2.get_direction(), v, u);
  }
  
  //Equivalent to resolution advisory on TCAS but instead of advising an action, execute it
  void Drone::resolution_actions(const core::ConflictInfo& conflict) const
  {
  
  }

  void Drone::traffic_advisory (const core::ConflictInfo& conflict) const
  {
    std::cout << "TRAFFIC TRAFFIC" << std::endl;
  }

  void Drone::resolve_conflict(const core::ConflictInfo& conflict) const
  {
    if (in_violation(conflict)) resolution_actions(conflict);
    if (theats_ahead(conflict)) traffic_advisory(conflict);
  }

   void Drone::check_conflict(const Drone& a2) const
  {
    core::ConflictInfo conflict = get_conflict_details(a2);
    if (!conflict.conflict) return;
    resolve_conflict(conflict);
  }
