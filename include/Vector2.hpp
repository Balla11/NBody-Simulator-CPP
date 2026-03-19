#pragma once
#include <cmath>

struct Vector2 {
  double x = 0.0;
  double y = 0.0;

  // Constructors
  Vector2() = default;
  Vector2(double x, double y) : x(x), y(y) {}

  // Overloading
  Vector2 operator+(const Vector2 &v) const {return {x + v.x, y + v.y};}
  Vector2 operator-(const Vector2 &v) const {return {x - v.x, y - v.y};}
  Vector2 operator*(double scalar) const {return {x * scalar, y * scalar};}

  Vector2& operator+=(const Vector2 &v) {x += v.x; y += v.y; return *this;}

  // Utility functions
  [[nodiscard]] double normSquared() const {return x * x + y * y;}
  [[nodiscard]] double norm() const {return std::sqrt(normSquared());}

};