#include <math.h>
#include <string>
#include "Course.h"
#include "Matrix.h"
#include <iostream>

#define PRINT(x) std::cout << x << std::endl;

using namespace core;

double to_rad(int deg) {
  return deg * M_PI / 180.0;
}

Course::Course(const Vector3& t_position, const Vector3& t_direction)
{
  position.assign(t_position);
  direction.assign(t_direction);
};

Course::Course(const Vector3& t_position, int t_hdg, int t_climb_rate)
{
  position.assign(t_position);
  double rads = to_rad(t_hdg);
  direction.x = sin( rads );
  direction.y = cos( rads );
  direction.z = t_climb_rate;
}

Course::Course(double t_lat, double t_long, double t_alt, int t_hdg, int t_climb_rate)
{
  position.x = t_lat;
  position.y = t_long;
  position.z = t_alt;

  double rads = to_rad(t_hdg);
  direction.x = sin( rads );
  direction.y = cos( rads );
  direction.z = t_climb_rate;
}

bool Course::operator==(const Course &t_other)
{
  return t_other.position == position && t_other.direction == direction;
}

void Course::print()
{
  std::cout << "Pos: " << position.toString() << std::endl;
  std::cout << "Dir: " << direction.toString() << std::endl;
  std::cout << "Mag: " << direction.magnitude() << "\n" << std::endl;
}

void Course::print(std::string name)
{
  std::cout << "*** " << name << " ***" << std::endl;
  std::cout << "Pos: " << position.toString() << std::endl;
  std::cout << "Dir: " << direction.toString() << std::endl;
  std::cout << "Mag: " << direction.magnitude() << "\n" << std::endl;
}

Course Course::shortest_distance(Course& c1, Course& c2)
{
  if (c1.position == c2.position)
  {
    return Course(c1.position, Vector3::zero());
  }

  Vector3 d3 = Vector3::cross(c1.direction, c2.direction);

  if (d3 != Vector3::zero()) //Non paralell
  {
    double mat[3][4] = {
      {c1.direction.x, -c2.direction.x, d3.x, c2.position.x - c1.position.x},
      {c1.direction.y, -c2.direction.y, d3.y, c2.position.y - c1.position.y},
      {c1.direction.z, -c2.direction.z, d3.z, c2.position.z - c1.position.z}};
    
    Matrix m(mat);
    Vector3 solution = m.gaussian_elimination();

    double a = solution.x;
    double b = solution.y;
    double c = solution.z;    

    if (a >= 0 && b >= 0)
    {
      Vector3 position = c1.position + (c1.direction * a);
      Vector3 direction = d3 * c;

      return Course(position, direction);
    }
  }

  c1.direction.normalize();
  c2.direction.normalize();

  Vector3 dP = c2.position - c1.position;

  Vector3 i_dP = dP.inverted();
  double a2 = Vector3::dot(c1.direction, dP);
  double b2 = Vector3::dot(c2.direction, i_dP);
  

  if (a2 < 0.0 && b2 < 0.0)
  {
    return Course(c1.position, dP);
  }

  Vector3 p3a = c1.position + (c1.direction * a2);
  Vector3 d3a = c2.position - p3a;

  Vector3 p3b = c1.position;
  Vector3 d3b = c2.position + ((c2.direction * b2) - p3b);

  if (b2 < 0.0)
  {
    return Course(p3a, d3a);
  }

  if (a2 < 0.0)
  {
    return Course(p3b, d3b);
  }

  if (d3a.magnitude() <= d3b.magnitude())
  {
    return Course(p3a, d3a);
  }

  return Course(p3b, d3b);

};
