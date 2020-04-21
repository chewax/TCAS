// Creates a virtual airspace controller to emulate the coinhabitation of multiple aerodynes

#ifndef GUARD_VirtualATC
#define GUARD_VirtualATC

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "../airspace/Drone.h"

struct Traffic 
{
  std::string label;
  double lat;
  double lon;
  int alt;
  int hdg;
  int climb_rate;
  int spd;
  bool _void;

  Traffic()
  {
    this->_void = true;
  }


  Traffic(std::string t_label, double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed):
  label(t_label), lat(t_lat), lon(t_lon), alt(t_alt), hdg(t_hdg), climb_rate(t_climb_rate), spd(t_speed)
  {  
    this->_void = false;
  }
};

class VirtualATC
{
  private:
    std::map<std::string, Traffic> traffics;

  public:
    VirtualATC();
    void add_traffic (std::string t_label, double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed);
    void add_traffic (Traffic t);
    void remove_traffic (std::string label);
    void traffic_instruction (std::vector<std::string> args);
    Traffic get_traffic (std::string label);
    std::vector<Traffic> get_all ();
};

VirtualATC::VirtualATC() 
{
}

void VirtualATC::add_traffic (std::string t_label, double t_lat, double t_lon, int t_alt, int t_hdg, int t_climb_rate, int t_speed)
{
  traffics[t_label] = Traffic(t_label, t_lat, t_lon, t_alt, t_hdg, t_climb_rate, t_speed);
}

void VirtualATC::add_traffic (Traffic t)
{
  traffics[t.label] = t; 
}

Traffic VirtualATC::get_traffic(std::string label)
{
  auto it = traffics.find(label);
  if (it != traffics.end())
  {
    return it->second;
  }
  else
  {
    return Traffic();
  }
}


std::vector<Traffic> VirtualATC::get_all ()
{
  std::vector<Traffic> res;
  std::transform(traffics.begin(), traffics.end(), std::back_inserter(res), [](std::pair<std::string ,Traffic> e) -> Traffic {
    return e.second;
  });

  return res;
}


void VirtualATC::traffic_instruction (std::vector<std::string> args)
{
  std::cout << args[1] << args[2] << std::endl;
}

#endif