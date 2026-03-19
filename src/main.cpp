#include <iostream>
#include <vector>

int main() {
  std::cout << "--- N-Body-Simulator Initialized ---" << std::endl;

  std::vector<std::string> steps = {"Setup", "Physics", "Rendering"};

  for (const auto& step : steps) {
    std::cout << "Loading: " << step << "..." << std::endl;
  }
  return 0;
}
