#include <iostream>
#include <vector>
#include <iomanip>
#include "Simulator.hpp"

int main() {
  Simulator sim;

  // Add "Sun"
  sim.addBody(Body({0.0, 0.0}, {0.0, 0.0}, 1.989e30));

  // Add "Earth"
  sim.addBody(Body({1.5e11, 0.0}, {0.0, 29780}, 5.972e24));

  double dt = 86400; // 1 step = 1 day

  std::cout << std::left << std::setw(10) << "Giorno"
            << std::setw(20) << "Posizione X"
            << std::setw(20) << "Posizione Y" << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;

  for (int day = 0; day <= 10; ++day) {
    const auto& earth = sim.getBodies()[1];
    std::cout << std::left << std::setw(10) << day
              << std::setw(20) << earth.position.x
              << std::setw(20) << earth.position.y << std::endl;

    sim.step(dt);
  }

  return 0;
}
