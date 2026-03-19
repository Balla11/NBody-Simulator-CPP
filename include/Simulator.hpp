#pragma once
#include <vector>
#include "Body.hpp"

class Simulator {
private:
  std::vector<Body> bodies;
  const double G = 6.6743e-11;

public:

  Simulator() = default;

  void addBody(const Body &body) {
    bodies.push_back(body);
  }

  void step(double dt);

  const std::vector<Body> &getBodies() const {
    return bodies;
  }

};