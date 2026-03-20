#include "Simulator.hpp"
#include <cmath>

void Simulator::step(double dt) {

    if (currentIntegrator == Integrator::Euler) {
        stepEuler(dt);
    } else if (currentIntegrator == Integrator::VelocityVerlet) {
        stepVelocityVerlet(dt);
    }
}

void Simulator::computeForces() {

    for (auto& body : bodies) {
        body.acceleration = Vector2(0.0, 0.0);
    }


    for (std::size_t i = 0; i < bodies.size(); ++i) {
        for (std::size_t j = i + 1; j < bodies.size(); ++j) {
            Vector2 diff = bodies[j].position - bodies[i].position;
            double distSq = diff.normSquared();
            double dist = diff.norm();

            if (dist > 0) {
                double force_mag = (G * bodies[i].mass * bodies[j].mass) / distSq;
                Vector2 force_vec = diff * (force_mag / dist);

                bodies[i].applyForce(force_vec);
                bodies[j].applyForce(force_vec * -1.0);
            }
        }
    }
}

// --- EULER ---
void Simulator::stepEuler(double dt) {
    computeForces();

    for (auto& body : bodies) {
        body.velocity += body.acceleration * dt;
        body.position += body.velocity * dt;
    }
}

// --- VELOCITY VERLET ---
void Simulator::stepVelocityVerlet(double dt) {

    for (auto& body : bodies) {
        body.position += body.velocity * dt + body.acceleration * (0.5 * dt * dt);
        body.velocity += body.acceleration * (0.5 * dt);
    }

    computeForces();

    for (auto& body : bodies) {
        body.velocity += body.acceleration * (0.5 * dt);
    }
}

double Simulator::getEnergy() const {
    double kinetic_energy = 0.0;
    double potential_energy = 0.0;

    // Sum over kinetic energy
    for (const auto& body : bodies) {
        kinetic_energy += 0.5 * body.mass * body.velocity.normSquared();
    }

    // Sum over potential energy
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        for (std::size_t j = i + 1; j < bodies.size(); ++j) {
            Vector2 diff = bodies[i].position - bodies[j].position;
            double dist = diff.norm();

            if (dist > 0) {
                potential_energy -= (G * bodies[i].mass * bodies[j].mass) / dist;
            }
        }
    }

    return kinetic_energy + potential_energy;

}