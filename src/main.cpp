#include "Renderer.hpp"
#include "Scenarios.hpp"
#include "Simulator.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

int main() {
  Simulator sim;

  sim.setIntegrator(Simulator::Integrator::VelocityVerlet);

  double dt = 0.001;
  int stepsPerFrame = 10;

  loadSolarSystem((sim));


  Renderer renderer(800, 800, 0.015f);



  // Write on file
  std::ofstream data_file("energy_log.csv");
  if (!data_file.is_open()) {
    std::cerr << "Can't open file" << std::endl;
    return -1;
  }

  data_file << "Time,TotalEnergy\n";

  double time = 0.0;
  int frame_count = 0.0;


  // GAME LOOP
  while (renderer.isOpen()) {
    renderer.handleEvents(); // Gestisce la chiusura della finestra

    // PHYSICS
    for (int i = 0; i < stepsPerFrame; ++i) {
      sim.step(dt);
      time += dt;
    }
    data_file << std::scientific << std::setprecision(14)
              << time << ","
              << sim.getEnergy() << "\n";

    // GRAPHICS
    renderer.render(sim);
  }

  return 0;
}