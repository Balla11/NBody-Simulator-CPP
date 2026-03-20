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
        body.acceleration = {0.0, 0.0};
    }


    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            double dx = bodies[j].position.x - bodies[i].position.x;
            double dy = bodies[j].position.y - bodies[i].position.y;
            double distSq = dx * dx + dy * dy;
            double dist = std::sqrt(distSq);

            if (dist > 0) {
                double force = (G * bodies[i].mass * bodies[j].mass) / distSq;
                double ax = force * dx / dist;
                double ay = force * dy / dist;

                bodies[i].applyForce({ax, ay});
                bodies[j].applyForce({-ax, -ay});
            }
        }
    }
}

// --- EULER ---
void Simulator::stepEuler(double dt) {
    computeForces();

    for (auto& body : bodies) {
        body.velocity.x += body.acceleration.x * dt;
        body.velocity.y += body.acceleration.y * dt;

        body.position.x += body.velocity.x * dt;
        body.position.y += body.velocity.y * dt;
    }
}

// --- VELOCITY VERLET ---
void Simulator::stepVelocityVerlet(double dt) {

    for (auto& body : bodies) {
        body.position.x += body.velocity.x * dt + 0.5 * body.acceleration.x * dt * dt;
        body.position.y += body.velocity.y * dt + 0.5 * body.acceleration.y * dt * dt;

        body.velocity.x += 0.5 * body.acceleration.x * dt;
        body.velocity.y += 0.5 * body.acceleration.y * dt;
    }


    computeForces();


    for (auto& body : bodies) {
        body.velocity.x += 0.5 * body.acceleration.x * dt;
        body.velocity.y += 0.5 * body.acceleration.y * dt;
    }
}