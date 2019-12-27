#pragma once
#include <string>

namespace core
{
  struct Vector3
  {
    double x, y, z;
    Vector3(double t_x, double t_y, double t_z);
    Vector3(double v[3]);
    Vector3();
    Vector3(const Vector3& other); // copy constructor

    Vector3 static zero();
    Vector3 static cross(const Vector3& a, const Vector3& b);
    double static dot(const Vector3& a, const Vector3& b);
    double static distance(const Vector3& a, const Vector3& b);
    double static distanceX(const Vector3& a, const Vector3& b);
    double static distanceY(const Vector3& a, const Vector3& b);
  
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator-() const;
    Vector3 operator*(const double& a) const;
    double operator*(const Vector3& other) const;
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
    Vector3& operator=(const Vector3& other);

    Vector3& assign(const Vector3& other);
    double magnitude();
    Vector3& normalize();
    Vector3& invert();
    Vector3 inverted() const;
    std::string to_string();
    void print();
  };

} // namespace core
