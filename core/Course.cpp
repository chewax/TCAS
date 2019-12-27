#include "Course.h"
#include "Geo.h"
#include "Matrix.h"
#include "Utils.h"
#include <iostream>
#include <math.h>
#include <string>

using namespace core;

#define DEBUG(x) std::cout << x << std::endl


Course::Course(double t_lat, double t_lon, double t_alt, int t_hdg, int t_climb_rate, int t_speed)
{
  position.x = geo::Coord::to_fts(t_lat);
  position.y = geo::Coord::to_fts(t_lon);
  position.z = t_alt; // Assumed to be received in always in feets (never Flight Levels)

  double rads = to_rad(t_hdg);
  double spd_ft = kts_to_ftm(t_speed);
  direction.x = sin(rads) * spd_ft;
  direction.y = cos(rads) * spd_ft;
  direction.z = t_climb_rate;
}
Course::Course(const Vector3& position, const Vector3& direction)
{
  this->position = position;
  this->direction = direction;
}


bool Course::operator==(const Course& t_other)
{
  return t_other.position == position && t_other.direction == direction;
}

void Course::print()
{
  std::cout << "Pos: " << position.to_string() << std::endl;
  std::cout << "Dir: " << direction.to_string() << std::endl;
  std::cout << "Mag: " << direction.magnitude() << "\n" << std::endl;
}

void Course::print(std::string name)
{
  std::cout << "*** " << name << " ***" << std::endl;
  std::cout << "Pos: " << position.to_string() << std::endl;
  std::cout << "Dir: " << direction.to_string() << std::endl;
  std::cout << "Mag: " << direction.magnitude() << "\n" << std::endl;
}

Vector3 Course::intersect(const Course& other) const
{
  const Vector3& A = this->position;
  const Vector3& a = this->direction;
  const Vector3& b = other.direction;
  const Vector3 c = other.position - this->position;

  if (Vector3::dot(a, a) == 0.0)
  {
    return NULL;
  }
  if (Vector3::dot(b, b) == 0.0)
  {
    return NULL;
  }
  if (pow(Vector3::dot(a, b), 2) == (Vector3::dot(a, a) * Vector3::dot(b, b)))
  {
    return NULL;
  }

  double numerator = -(Vector3::dot(a, b) * Vector3::dot(b, c)) + (Vector3::dot(a, c) * Vector3::dot(b, b));
  double denominator = (Vector3::dot(a, a) * Vector3::dot(b, b)) - (Vector3::dot(a, b) * Vector3::dot(a, b));

  Vector3 D = A + (a * (numerator / denominator));

  return D;
}

bool Course::contains(const Vector3& P) const
{
  if (P == this->position)
    return true;

  Vector3 AP = P - this->position;
  Vector3 V = this->direction;

  return Vector3::dot(AP, V) > 0;
}

// Returns a Course C3 where C3.position belongs to C1 and the distance from C1 to C2 is minimal.
Course Course::shortest_distance(Course& c1, Course& c2)
{
  if (c1.position == c2.position)
  {
    DEBUG("--> 1");
    return Course(c1.position, Vector3::zero());
  }

  Vector3 d3 = Vector3::cross(c1.direction, c2.direction);

  if (d3 != Vector3::zero()) // Non paralell
  {

    double mat[12] = {c1.direction.x, -c2.direction.x, d3.x, c2.position.x - c1.position.x,
                      c1.direction.y, -c2.direction.y, d3.y, c2.position.y - c1.position.y,
                      c1.direction.z, -c2.direction.z, d3.z, c2.position.z - c1.position.z};

    double* solution = matrix::solve(mat, 3, 4);

    double a = solution[3];
    double b = solution[7];
    double c = solution[11];

    // double a = solution.x;
    // double b = solution.y;
    // double c = solution.z;

    if (a >= 0 && b >= 0)
    {
      Vector3 position = c1.position + (c1.direction * a);
      Vector3 direction = d3 * c;
      DEBUG("--> 2");
      return Course(position, direction);
    }
  }

  c1.direction.normalize();
  c2.direction.normalize();

  Vector3 dP = c2.position - c1.position;

  Vector3 i_dP = -dP;
  double a2 = Vector3::dot(c1.direction, dP);
  double b2 = Vector3::dot(c2.direction, i_dP);

  if (a2 < 0.0 && b2 < 0.0)
  {
    DEBUG("--> 3");
    return Course(c1.position, dP);
  }

  Vector3 p3a = c1.position + (c1.direction * a2);
  Vector3 d3a = c2.position - p3a;

  Vector3 p3b = c1.position;
  Vector3 d3b = c2.position + ((c2.direction * b2) - p3b);

  if (b2 < 0.0)
  {
    DEBUG("--> 4");
    return Course(p3a, d3a);
  }

  if (a2 < 0.0)
  {
    DEBUG("--> 5");
    return Course(p3b, d3b);
  }

  if (d3a.magnitude() <= d3b.magnitude())
  {
    DEBUG("--> 6");
    return Course(p3a, d3a);
  }

  DEBUG("--> 7");
  return Course(p3b, d3b);
};
