#pragma once
#include "Vector3.h"
#include <string>

struct Course
{
  core::Vector3 position;
  core::Vector3 direction;
  Course(const core::Vector3& t_position, const core::Vector3& t_direction);
  Course(const core::Vector3& t_position, int t_hdg, int t_climb_rate);
  Course(double t_lat, double t_long, double t_alt, int t_hdg, int t_climb_rate);
  bool operator==(const Course &t_other);
  Course static shortest_distance(Course& c1, Course& c2);
  void print();
  void print(std::string name);
};

