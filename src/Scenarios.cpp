#include <cmath>
#include <vector>
#include "Scenarios.hpp"
#include "Vector2.hpp"

Body createPlanet(double semi_major_axis, double eccentricity, double mass,
                  double central_mass = 1.0) {

  double GM = Simulator::G * central_mass;

  double r = semi_major_axis * (1.0 - eccentricity);
  double v = std::sqrt((GM / semi_major_axis) * ((1.0 + eccentricity) / (1.0 - eccentricity)));
  return Body({r, 0.0}, {0.0, v}, mass);

}

void loadSolarSystem(Simulator &sim) {

  sim.clear();
  Body sun({0.0, 0.0}, {0.0, 0.0}, 1.0);
  Body mercury = createPlanet(0.39, 0.2056, 1.2e-7);
  Body earth = createPlanet(1.0, 0.0167, 3.0e-6);
  Body jupiter = createPlanet(5.20, 0.0489, 9.5e-4);

  std::vector<Body> tempBodies = {sun, mercury, earth, jupiter};

  double total_mass = 0.0;
  Vector2 r_cm = {0.0, 0.0};
  Vector2 v_cm = {0.0, 0.0};

  for (const auto& body : tempBodies) {
    total_mass += body.mass;
    r_cm += (body.position * body.mass);
    v_cm += (body.velocity * body.mass);
  }

  r_cm = r_cm * (1.0 / total_mass);
  v_cm = v_cm * (1.0 / total_mass);

  for (auto& body : tempBodies) {
    body.position = body.position - r_cm;
    body.velocity = body.velocity - v_cm;
    sim.addBody(body);
  }

}

void loadFigure8(Simulator& sim) {
  sim.clear();
  double m = 1.0 / Simulator::G;

  double x0 = 0.97000436;
  double y0 = -0.24308753;


  double vx = 0.4662036850;
  double vy = 0.4323657300;


  Body b1({x0, y0}, {vx, vy}, m);


  Body b2({-x0, -y0}, {vx, vy}, m);

  Body b3({0.0, 0.0}, {-2.0 * vx, -2.0 * vy}, m);

  sim.addBody(b1);
  sim.addBody(b2);
  sim.addBody(b3);
}