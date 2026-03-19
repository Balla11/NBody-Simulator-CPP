#include "Simulator.hpp"
#include <cmath>

void Simulator::step(const double dt) {

  // Compute all forces
  for (std::size_t i = 0; i < bodies.size(); ++i) {
    for (std::size_t j = i + 1; j < bodies.size(); ++j) {
      auto& body1 = bodies[i];
      auto& body2 = bodies[j];

      Vector2 r = body2.position - body1.position;

      double distSq = r.normSquared() + 1e-4; // Softening
      double dist = std::sqrt(distSq);

      double force_magnitude = (G * body1.mass * body2.mass) / distSq;

      // Using scalar multiplication for Vector2 class
      Vector2 force = r * (force_magnitude / dist);

      body1.applyForce(force);
      body2.applyForce(force * -1.0);


    }
  }
  // Update positions
  for (auto& body : bodies) {
    body.update(dt);
  }
}
