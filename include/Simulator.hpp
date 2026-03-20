#pragma once
#include <vector>
#include "Body.hpp"

class Simulator {

public:
  enum class Integrator {
    Euler,
    VelocityVerlet
  };

  Simulator() = default;

  void addBody(const Body& body) {
    bodies.push_back(body);
  }

  void setIntegrator(Integrator method) {
    currentIntegrator = method;
  }

  void step(double dt);

  const std::vector<Body>& getBodies() const {
    return bodies;
  }

  double getEnergy() const;


private:
  std::vector<Body> bodies;
  const double G = 6.6743e-11;
  Integrator currentIntegrator = Integrator::VelocityVerlet;

  // Private helper methods
  void computeForces();
  void stepEuler(double dt);
  void stepVelocityVerlet(double dt);
};

