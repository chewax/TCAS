#pragma once
#include <string>

namespace core {
  struct Vector3
  {
    double x, y, z;
    Vector3(double t_x, double t_y, double t_z);
    Vector3(double v[3]);
    Vector3();
    Vector3 static zero();
    Vector3 static cross(Vector3& a, Vector3& b);
    double static dot(Vector3& a, Vector3& b);
    Vector3 operator+(const Vector3& t_other) const;
    Vector3 operator-(const Vector3& t_other) const;
    Vector3 operator*(const double& a) const;
    double operator*(const Vector3& t_other) const;
    bool operator==(const Vector3 &t_other) const;
    bool operator!=(const Vector3 &t_other) const;
    double magnitude();
    void normalize();
    void invert();
    void assign( const Vector3& t_other);
    Vector3 inverted();
    std::string toString();
  };
}
