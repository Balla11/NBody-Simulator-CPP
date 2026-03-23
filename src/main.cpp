#include "Renderer.hpp"
#include "Scenarios.hpp"
#include "Simulator.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>


void runConvergenceAnalysis() {
  std::cout << "Running convergence analysis..." << std::endl;

  std::vector<double> dt_values = {0.0001, 0.0002, 0.0003, 0.0005, 0.0008,
                                   0.001, 0.002, 0.003, 0.005, 0.008,
                                   0.01, 0.02, 0.03, 0.05, 0.08,
                                   0.1, 0.2, 0.3, 0.5, 0.8};
  double total_time = 1.1; // Simulate one year

  std::ofstream out("convergence_data.csv");
  out << "dt,euler_err,verlet_err,rk4_err\n";
  out << std::scientific << std::setprecision(8);

  // Lo diciamo anche al terminale per comodità
  std::cout << std::scientific << std::setprecision(6);

  std::vector<Simulator::Integrator> integrators = {
    Simulator::Integrator::Euler,
    Simulator::Integrator::VelocityVerlet,
    Simulator::Integrator::RK4
  };

  for (double dt : dt_values) {
    out << dt;
    for (auto integrator : integrators) {
      Simulator sim;
      sim.setIntegrator(integrator);

      loadSolarSystem(sim);
      double E0 = sim.getEnergy();
      double max_error = 0.0;

      int steps = static_cast<int> (total_time / dt);
      for (int i = 0; i < steps; ++i) {
        sim.step(dt);
        double E = sim.getEnergy();
        double err = std::abs(E - E0) / (std::abs(E0) + 1e-10);
        if (err > max_error) {
          max_error = err;
        }
      }
      out << "," << max_error;
    }
    out << "\n";
    std::cout << "Completed test for dt =  " << dt << "\n";
  }
  out.close();
  std::cout << "Running convergence analysis complete." << std::endl;
}





int main() {


  //runConvergenceAnalysis();
  //return 0;

  Simulator sim;

  sim.setIntegrator(Simulator::Integrator::VelocityVerlet);

  double dt = 0.001;
  int stepsPerFrame = 100;

  loadSolarSystem((sim));
  //loadFigure8(sim);


  Renderer renderer(800, 800, 0.015f);



  // Write on file
  std::ofstream data_file("simulation_data.csv");
  if (!data_file.is_open()) {
    std::cerr << "Can't open file" << std::endl;
    return -1;
  }

  data_file << "Time,Total_Energy,Angular_Momentum\n";

  double time = 0.0;
  int frame_count = 0.0;


  // GAME LOOP
  while (renderer.isOpen()) {
    renderer.handleEvents();

    // PHYSICS
    for (int i = 0; i < stepsPerFrame; ++i) {
      sim.step(dt);
      time += dt;
    }
    data_file << std::scientific << std::setprecision(14)
              << time << ","
              << sim.getEnergy() << ","
              << sim.getAngularMomentum() << "\n";

    // GRAPHICS
    renderer.render(sim);
  }
  data_file.close();

  return 0;
}