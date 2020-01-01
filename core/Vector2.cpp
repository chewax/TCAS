#include "Vector2.h"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;
using namespace core;

Vector2::Vector2(double t_x, double t_y) : x(t_x), y(t_y)
{
}

Vector2::Vector2(double v[2]) : x(v[0]), y(v[1]))
{
}

Vector2::Vector2() : x(0.0), y(0.0)
{
}

Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y)
{
}

Vector2 Vector2::zero()
{
  return Vector2(0.0, 0.0);
}

Vector2 Vector2::cross(const Vector2& a, const Vector2& b)
{
  return Vector2(a.x * b.y - b.x * a.y);
}

double Vector2::dot(const Vector2& a, const Vector2& b)
{
  return a * b;
}

double Vector2::distance(const Vector2& a, const Vector2& b)
{
  return sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0) + pow(b.z - a.z, 2.0));
}

double Vector2::distanceX(const Vector2& a, const Vector2& b)
{
  return sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0));
}

double Vector2::distanceY(const Vector2& a, const Vector2& b)
{
  return abs(b.z - a.z);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
  return Vector2(x + other.x, y + other.y, z + other.z);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
  return Vector2(x - other.x, y - other.y, z - other.z);
}

Vector2 Vector2::operator-() const
{
  return this->inverted();
}

double Vector2::operator*(const Vector2& other) const
{
  return x * other.x + y * other.y + z * other.z;
}

Vector2 Vector2::operator*(const double& a) const
{
  return Vector2(x * a, y * a, z * a);
}

bool Vector2::operator==(const Vector2& other) const
{
  double diff_x = x - other.x;
  double diff_y = y - other.y;
  double diff_z = z - other.z;
  double precision = 0.000001;
  return abs(diff_x) <= precision && abs(diff_y) <= precision && abs(diff_z) <= precision;
}

bool Vector2::operator!=(const Vector2& other) const
{
  double diff_x = x - other.x;
  double diff_y = y - other.y;
  double diff_z = z - other.z;
  double precision = 0.000001;
  return abs(diff_x) > precision || abs(diff_y) > precision || abs(diff_z) > precision;
}

Vector2& Vector2::operator=(const Vector2& other)
{
  return this->assign(other);
}

double Vector2::magnitude()
{
  return sqrt(x * x + y * y + z * z);
}

Vector2& Vector2::normalize()
{
  double mag = magnitude();
  x = x / mag;
  y = y / mag;
  z = z / mag;

  return *this;
}

Vector2& Vector2::invert()
{
  x = -x;
  y = -y;
  z = -z;

  return *this;
}

Vector2& Vector2::assign(const Vector2& other)
{
  x = other.x;
  y = other.y;
  z = other.z;

  return *this;
}

Vector2 Vector2::inverted() const
{
  return Vector2(-x, -y, -z);
}

string Vector2::to_string()
{
  return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
}

void Vector2::print()
{
  cout << to_string() << endl;
}