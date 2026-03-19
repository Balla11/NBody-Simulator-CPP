#pragma once
#include "Vector2.hpp"

class Body {
public:
  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;
  double mass;
  Body(const Vector2 &pos, const Vector2 &vel, const double m)
    : position(pos), velocity(vel), acceleration{0,0}, mass(m) {}

  void applyForce(Vector2 force) {
    acceleration += force * (1.0 / mass);
  }

  void update(double dt);

};