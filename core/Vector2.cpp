#include "Vector2.h"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;
using namespace core;

Vector2::Vector2(double t_x, double t_y) : x(t_x), y(t_y)
{
}

Vector2::Vector2(double v[2]) : x(v[0]), y(v[1]) 
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

double Vector2::dot(const Vector2& a, const Vector2& b)
{
  return a * b;
}

double Vector2::distance(const Vector2& a, const Vector2& b)
{
  return sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0));
}

Vector2 Vector2::operator+(const Vector2& other) const
{
  return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
  return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-() const
{
  return this->inverted();
}

double Vector2::operator*(const Vector2& other) const
{
  return x * other.x + y * other.y;
}

Vector2 Vector2::operator*(const double& a) const
{
  return Vector2(x * a, y * a);
}

bool Vector2::operator==(const Vector2& other) const
{
  double diff_x = x - other.x;
  double diff_y = y - other.y;
  return abs(diff_x) <= m_precision && abs(diff_y) <= m_precision;
}

bool Vector2::operator!=(const Vector2& other) const
{
  double diff_x = x - other.x;
  double diff_y = y - other.y;
  return abs(diff_x) > m_precision || abs(diff_y) > m_precision;
}

Vector2& Vector2::operator=(const Vector2& other)
{
  return this->assign(other);
}

double Vector2::magnitude()
{
  return sqrt(x * x + y * y);
}

Vector2& Vector2::normalize()
{
  double mag = magnitude();
  x = x / mag;
  y = y / mag;

  return *this;
}

Vector2& Vector2::invert()
{
  x = -x;
  y = -y;

  return *this;
}

Vector2& Vector2::assign(const Vector2& other)
{
  x = other.x;
  y = other.y;

  return *this;
}

Vector2 Vector2::inverted() const
{
  return Vector2(-x, -y);
}

string Vector2::to_string()
{
  return "[ " + std::to_string(x) + ", " + std::to_string(y) + " ]";
}

void Vector2::print()
{
  cout << to_string() << endl;
}