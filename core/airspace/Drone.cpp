#include "Drone.h"
#include "../utils/Utils.h"
#include "../navigation/Geo.h"

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
    m_lat = core::Coord::to_fts(t_lat);
    m_lon = core::Coord::to_fts(t_lon);
    speed = t_speed; //must be in feets per minute
    hdg = t_hdg;
    alt = t_alt;
    climb_rate = t_climb_rate;
    m_position = core::Vector2(m_lat, m_lon);
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

  bool Drone::in_violation(const core::Conflict& conflict) const
  {
    double lsep = core::Vector2::distance(m_position, conflict.traffic.get_position());
    double vsep = abs(conflict.traffic.alt - alt);

    std::cout << "LATERAL SEPARATION: " << lsep << std::endl;
    std::cout << "VERTICAL SEPARATION: " << vsep << std::endl;
    
    if (lsep <= LATERAL_SEPARATION_MINIMUMS && vsep <= VERTICAL_SEPARATION_MINIMUMS) return true;
    return false;
  }

  bool Drone::theats_ahead(const core::Conflict& conflict) const
  {
    double dx_a = conflict.distance_self_collision;
    double dx_b = conflict.distance_traffic_collision;

    if (dx_a < 0.0f || dx_b < 0.0f) //if either distance is lt zero => conflict point has been passed => no threat ahead
    {
      return false;
    }

    //assume distance will be in feets and speed will be in feets per minute => so time will be in minutes
    double tx_a = dx_a / this->speed;
    double tx_b = dx_b / conflict.traffic.speed;

    if (abs(tx_a - tx_b) >= 30) //arriving collision point with more than 30 second difference
    {
      return false;
    }

    return true;
  }

  core::Conflict Drone::get_conflict_details(const Drone& a2) const
  {
    core::Vector2 ad = this->get_direction();
    core::Vector2 bd = a2.get_direction();
    
    double dx = a2.get_position().x - this->get_position().x;
    double dy = a2.get_position().y - this->get_position().y;

    double det = bd.x * ad.y - bd.y * ad.x;

    if (det == 0) return core::Conflict();
  
    double u = (dy * bd.x - dx * bd.y) / det; // a1's distance from point of convergence
    double v = (dy * ad.x - dx * ad.y) / det; // a2's distance from point of convergence
    
    return core::Conflict(a2, v, u);
  }
  
  //Equivalent to resolution advisory on TCAS but instead of advising an action, execute it
  void Drone::resolution_actions(const core::Conflict& conflict) const
  {
    
    std::cout << "DISTANCE TO CONFLICT: " << core::Vector2::distance( this->get_position(), conflict.traffic.get_position()) << std::endl;
    std::cout << "NEGOTIATING RESULUTION: " << std::endl;
    std::cout << "CLIMB, CLIMB NOW" << std::endl;
  }

  void Drone::traffic_advisory (const core::Conflict& conflict) const
  {
    std::cout << "TRAFFIC TRAFFIC" << std::endl;
  }

  void Drone::resolve_conflict(const core::Conflict& conflict) const
  {
    if (in_violation(conflict)) return resolution_actions(conflict);
    if (theats_ahead(conflict)) return traffic_advisory(conflict);
  }

   void Drone::check_conflict(const Drone& a2) const
  {
    core::Conflict conflict = get_conflict_details(a2);
    if (!conflict.conflict) 
    {
      std::cout << "NO CONFLICTS" << std::endl;
      return;
    }
    resolve_conflict(conflict);
  }
