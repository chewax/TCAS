#include "Vector3.h"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;
using namespace core;

Vector3::Vector3(double t_x, double t_y, double t_z) : x(t_x), y(t_y), z(t_z)
{
}

Vector3::Vector3(double v[3]) : x(v[0]), y(v[1]), z(v[2])
{
}

Vector3::Vector3() : x(0.0), y(0.0), z(0.0)
{
}

Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
{
}

Vector3 Vector3::zero()
{
  return Vector3(0.0, 0.0, 0.0);
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
  return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

double Vector3::dot(const Vector3& a, const Vector3& b)
{
  return a * b;
}

double Vector3::distance(const Vector3& a, const Vector3& b)
{
  return sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0) + pow(b.z - a.z, 2.0));
}

double Vector3::distanceX(const Vector3& a, const Vector3& b)
{
  return sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0));
}

double Vector3::distanceY(const Vector3& a, const Vector3& b)
{
  return abs(b.z - a.z);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
  return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
  return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-() const
{
  return this->inverted();
}

double Vector3::operator*(const Vector3& other) const
{
  return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::operator*(const double& a) const
{
  return Vector3(x * a, y * a, z * a);
}

bool Vector3::operator==(const Vector3& other) const
{
  double diff_x = x - other.x;
  double diff_y = y - other.y;
  double diff_z = z - other.z;
  double precision = 0.000001;
  return abs(diff_x) <= precision && abs(diff_y) <= precision && abs(diff_z) <= precision;
}

bool Vector3::operator!=(const Vector3& other) const
{
  double diff_x = x - other.x;
  double diff_y = y - other.y;
  double diff_z = z - other.z;
  double precision = 0.000001;
  return abs(diff_x) > precision || abs(diff_y) > precision || abs(diff_z) > precision;
}

Vector3& Vector3::operator=(const Vector3& other)
{
  return this->assign(other);
}

double Vector3::magnitude()
{
  return sqrt(x * x + y * y + z * z);
}

Vector3& Vector3::normalize()
{
  double mag = magnitude();
  x = x / mag;
  y = y / mag;
  z = z / mag;

  return *this;
}

Vector3& Vector3::invert()
{
  x = -x;
  y = -y;
  z = -z;

  return *this;
}

Vector3& Vector3::assign(const Vector3& other)
{
  x = other.x;
  y = other.y;
  z = other.z;

  return *this;
}

Vector3 Vector3::inverted() const
{
  return Vector3(-x, -y, -z);
}

string Vector3::to_string()
{
  return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
}

void Vector3::print()
{
  cout << to_string() << endl;
}