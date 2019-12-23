#ifndef GUARD_core
#define GUARD_core

#include <math.h>
#include <string>
#include "matrix.cpp"

struct Point3D
{
  double x, y, z;

  Point3D(double t_x, double t_y, double t_z)
  {
    x = t_x;
    y = t_y;
    z = t_z;
  };

  Point3D()
  {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  };

  bool operator==(const Point3D &t_other) const
  {
    return t_other.x == x && t_other.y == y && t_other.z == z;
  }

  bool operator!=(const Point3D &t_other) const
  {
    return t_other.x != x || t_other.y != y || t_other.z != z;
  }

  Point3D operator+(const Point3D& t_other) const
  {
    return Point3D(x + t_other.x, y + t_other.y, z + t_other.z);
  }

};

struct Vector3
{
  double x, y, z;

  Vector3(double t_x, double t_y, double t_z)
  {
    x = t_x;
    y = t_y;
    z = t_z;
  }

  Vector3(double v[3])
  {
    x = v[0];
    y = v[1];
    z = v[2];
  }

  Vector3()
  {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  Vector3 static zero()
  {
    return Vector3(0.0, 0.0, 0.0);
  }

  Vector3 static cross(Vector3& a, Vector3& b)
  {
    return Vector3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
  }

  Vector3 operator+(const Vector3& t_other) const
  {
    return Vector3(x + t_other.x, y + t_other.y, z + t_other.z);
  }

  Vector3 operator+(const Point3D& t_other) const
  {
    return Vector3(x + t_other.x, y + t_other.y, z + t_other.z);
  }

  Vector3 operator-(const Vector3& t_other) const
  {
    return Vector3(x - t_other.x, y - t_other.y, z - t_other.z);
  }

  double operator*(const Vector3& t_other) const
  {
    return x * t_other.x + y * t_other.y + z * t_other.z;
  }


  Vector3 operator*(const double& a) const
  {
    return Vector3 (x * a , y * a , z * a);
  }


  bool operator==(const Vector3 &t_other) const
  {
    double diff_x = x - t_other.x;
    double diff_y = y - t_other.y;
    double diff_z = z - t_other.z;
    double precision = 0.000001;
    return abs(diff_x) <= precision && abs(diff_y) <= precision && abs(diff_z) <= precision;
  }

  bool operator!=(const Vector3 &t_other) const
  {
    double diff_x = x - t_other.x;
    double diff_y = y - t_other.y;
    double diff_z = z - t_other.z;
    double precision = 0.000001;
    return abs(diff_x) > precision && abs(diff_y) > precision && abs(diff_z) > precision;
  }

  double magnitude()
  {
    return sqrt(x * x + y * y + z * z);
  }

  void normalize()
  {
    double mag = magnitude();
    x = x / mag;
    y = y / mag;
    z = z / mag;
  }

  std::string toString()
  {
    return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
  }
};

struct Course
{
  Point3D position;
  Vector3 direction;

  Course(Point3D t_position, Vector3 t_direction)
  {
    position = t_position;
    direction = t_direction;
  };

  Course(Point3D t_position, int t_hdg, int t_climb_rate)
  {
    position = t_position;
    direction.x = cos(t_hdg);
    direction.y = sin(t_hdg);
    direction.z = t_climb_rate;
  }

  Course(double t_lat, double t_long, double t_alt, int t_hdg, int t_climb_rate)
  {
    position.x = t_lat;
    position.y = t_long;
    position.z = t_alt;

    direction.x = cos(t_hdg);
    direction.y = sin(t_hdg);
    direction.z = t_climb_rate;
  }

  bool operator==(const Course &t_other)
  {
    return t_other.position == position && t_other.direction == direction;
  }

  Course static shortestDistance(Course &c1, Course &c2)
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

      double solution[3];
      gaussianElimination(mat, solution);

      double a = solution[0];
      double b = solution[1];
      double c = solution[2];

      if (a >= 0 && b >= 0)
      {
        Point3D position = Point3D(c1.direction.x*a, c1.direction.y*a, c1.direction.z*a) + c1.position;
        Vector3 direction = d3 * c;

        return Course(position, direction);
      }
    }


  };

};

#endif