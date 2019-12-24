#include <math.h>
#include <string>
#include "Vector3.h"

using namespace std;
using namespace core;

Vector3::Vector3(double t_x, double t_y, double t_z)
{
  x = t_x;
  y = t_y;
  z = t_z;
}

Vector3::Vector3(double v[3])
{
  x = v[0];
  y = v[1];
  z = v[2];
}

Vector3::Vector3()
{
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

Vector3 Vector3::zero()
{
  return Vector3(0.0, 0.0, 0.0);
}

Vector3 Vector3::cross(Vector3& a, Vector3& b)
{
  return Vector3(
      a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x);
}

double Vector3::dot(Vector3& a, Vector3& b)
{
  return a * b;
}

Vector3 Vector3::operator+(const Vector3& t_other) const
{
  return Vector3(x + t_other.x, y + t_other.y, z + t_other.z);
}

Vector3 Vector3::operator-(const Vector3& t_other) const
{
  return Vector3(x - t_other.x, y - t_other.y, z - t_other.z);
}

double Vector3::operator*(const Vector3& t_other) const
{
  return x * t_other.x + y * t_other.y + z * t_other.z;
}

Vector3 Vector3::operator*(const double& a) const
{
  return Vector3 (x * a , y * a , z * a);
}


bool Vector3::operator==(const Vector3 &t_other) const
{
  double diff_x = x - t_other.x;
  double diff_y = y - t_other.y;
  double diff_z = z - t_other.z;
  double precision = 0.000001;
  return abs(diff_x) <= precision && abs(diff_y) <= precision && abs(diff_z) <= precision;
}

bool Vector3::operator!=(const Vector3 &t_other) const
{
  double diff_x = x - t_other.x;
  double diff_y = y - t_other.y;
  double diff_z = z - t_other.z;
  double precision = 0.000001;
  return abs(diff_x) > precision || abs(diff_y) > precision || abs(diff_z) > precision;
}

double Vector3::magnitude()
{
  return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize()
{
  double mag = magnitude();
  x = x / mag;
  y = y / mag;
  z = z / mag;
}

void Vector3::invert()
{
  x = -x;
  y = -y;
  z = -z;
}

void Vector3::assign( const Vector3& t_other)
{
  x = t_other.x;
  y = t_other.y;
  z = t_other.z;
}

Vector3 Vector3::inverted()
{
  return Vector3(-x, -y, -z);
}

string Vector3::toString()
{
  return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
}


