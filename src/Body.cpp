#include "Body.hpp"

void Body::update(const double dt) {

  velocity += acceleration * dt;
  position += velocity * dt;

  acceleration = {0.0, 0.0};


}