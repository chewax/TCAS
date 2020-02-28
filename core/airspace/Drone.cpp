#include "Drone.h"
#include "../utils/Utils.h"

Drone::Drone()
{
  m_lat = 0.0;
  m_lon = 0.0;
  speed = 0;
  hdg = -1;
  alt = -1;
  climb_rate = 1;
  reg = "";
  model = ""; 
}

Drone::Drone(double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed)
  {
    m_lat = t_lat;
    m_lon = t_lon;
    speed = t_speed; //must be in feets per minute
    hdg = t_hdg;
    alt = t_speed;
    climb_rate = t_climb_rate;
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
    double lsep = core::Vector2::distance(m_position, conflict.traffic.get_position());
    double vsep = abs(conflict.traffic.alt - alt);
    if (lsep <= LATERAL_SEPARATION_MINIMUMS && vsep <= VERTICAL_SEPARATION_MINIMUMS) return true;
    return false;
  }

  bool Drone::theats_ahead(const core::ConflictInfo& conflict) const
  {
    double dx_a = (conflict.collision_point - this->get_position()) / this->get_direction().normalize();          //distance from self to colission point
    double dx_b = (conflict.collision_point - conflict.get_position()) / conflict.get_direction().normalize();    //distance from traffic to collision point

    if (dx_a < 0 || dx_b < 0) //if either distance is lt zero => conflict point has been passed => no threat ahead
    {
      return false;
    }

    //assume distance will be in feets and speed will be in feets per minute => so time will be in minutes
    double tx_a = dx_a / this->speed;
    double tx_b = dx_b / conflict.speed;

    if (abs(tx_a - tx_b) >= 30) //arriving collision point with more than 30 second difference
    {
      return false;
    }

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
    
    // return core::ConflictInfo(a2.get_position(), a2.get_direction(), v, u, a2.alt);
    return core::ConflictInfo(a2, v);
  }
  
  //Equivalent to resolution advisory on TCAS but instead of advising an action, execute it
  void Drone::resolution_actions(const core::ConflictInfo& conflict) const
  {
    std::cout << "CLIMB, CLIMB NOW" << std::endl;
  }

  void Drone::traffic_advisory (const core::ConflictInfo& conflict) const
  {
    std::cout << "TRAFFIC TRAFFIC" << std::endl;
  }

  void Drone::resolve_conflict(const core::ConflictInfo& conflict) const
  {
    if (in_violation(conflict)) return resolution_actions(conflict);
    if (theats_ahead(conflict)) return traffic_advisory(conflict);
  }

   void Drone::check_conflict(const Drone& a2) const
  {
    core::ConflictInfo conflict = get_conflict_details(a2);
    if (!conflict.conflict) return;
    resolve_conflict(conflict);
  }
