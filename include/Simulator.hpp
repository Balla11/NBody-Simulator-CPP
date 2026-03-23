#pragma once
#include <vector>
#include <numbers>
#include "Body.hpp"

class Simulator {

public:

  static constexpr double G = 4.0 * std::numbers::pi * std::numbers::pi;

  enum class Integrator {
    Euler,
    VelocityVerlet,
    RK4
  };

  Simulator() = default;

  void clear() {
    bodies.clear();
  }

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
  double getAngularMomentum() const;


private:
  std::vector<Body> bodies;
  Integrator currentIntegrator = Integrator::VelocityVerlet;

  // Private helper methods
  void computeForces();
  void stepEuler(double dt);
  void stepVelocityVerlet(double dt);
  void stepRK4(double dt);
  std::vector<Vector2> computeAccelerations(const std::vector<Body>& state) const;
};

