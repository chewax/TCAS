#pragma once
#include <string>

namespace core
{
  struct Vector2
  {
    double x, y, z;
    double m_precision = 0.000001;
    Vector2(double t_x, double t_y);
    Vector2(double v[2]);
    Vector2();
    Vector2(const Vector2& other); // copy constructor

    Vector2 static zero();
    double static dot(const Vector2& a, const Vector2& b);
    double static distance(const Vector2& a, const Vector2& b);
  
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator-() const;
    Vector2 operator*(const double& a) const;
    double operator*(const Vector2& other) const;
    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
    Vector2& operator=(const Vector2& other);

    Vector2& assign(const Vector2& other);
    double magnitude();
    Vector2& normalize();
    Vector2& invert();
    Vector2 inverted() const;
    std::string to_string();
    void print();
  };

} // namespace core
