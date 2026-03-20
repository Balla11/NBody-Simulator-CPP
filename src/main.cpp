#include "Simulator.hpp"
#include "Renderer.hpp"

int main() {
  Simulator sim;

  sim.setIntegrator(Simulator::Integrator::VelocityVerlet);

  // --- Figure-8 Orbit ---
  double m = 1.0e30;

  sim.addBody(Body({9.70e10, -2.43e10}, {12044, 11170}, m));

  sim.addBody(Body({-9.70e10, 2.43e10}, {12044, 11170}, m));

  sim.addBody(Body({0, 0}, {-24088, -22340}, m));

  Renderer renderer(800, 800, 3.8e8f);

  double dt = 10.0;
  int stepsPerFrame = 1440;

  // GAME LOOP
  while (renderer.isOpen()) {
    renderer.handleEvents(); // Gestisce la chiusura della finestra

    // PHYSICS
    for (int i = 0; i < stepsPerFrame; ++i) {
      sim.step(dt);
    }

    // GRAPHICS
    renderer.render(sim);
  }

  return 0;
}