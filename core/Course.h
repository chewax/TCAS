#pragma once
#include "Vector3.h"
#include <string>

struct Course
{
  core::Vector3 position;
  core::Vector3 direction;

  Course(double t_lat, double t_lon, double t_alt, int t_hdg, int t_climb_rate, int t_speed);
  Course(const core::Vector3& position, const core::Vector3& direction);
  bool operator==(const Course& t_other);
  core::Vector3 intersect (const Course& other) const;
  bool contains(const core::Vector3& P) const;

  Course static shortest_distance(Course& c1, Course& c2);
  Course static check_proximity(Course& c1, Course& c2);

  void print();
  void print(std::string name);
};
