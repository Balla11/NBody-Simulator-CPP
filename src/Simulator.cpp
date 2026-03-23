#include "Simulator.hpp"
#include <cmath>

void Simulator::step(double dt) {

    if (currentIntegrator == Integrator::Euler) {
        stepEuler(dt);
    } else if (currentIntegrator == Integrator::VelocityVerlet) {
        stepVelocityVerlet(dt);
    } else if (currentIntegrator == Integrator::RK4) {
        stepRK4(dt);
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

std::vector<Vector2> Simulator::computeAccelerations(const std::vector<Body>& state) const {
    std::size_t n = state.size();
    std::vector<Vector2> acc(n, {0.0, 0.0});

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            Vector2 r = state[j].position - state[i].position;
            double dist = r.norm();
            if (dist == 0.0) continue;
            double distSq = dist * dist;

            Vector2 dir = r * (1.0 / dist);
            acc[i] += dir * (G * state[j].mass / distSq);
            acc[j] -= dir * (G * state[i].mass / distSq);
        }
    }
    return acc;
}

void Simulator::stepRK4(double dt) {
    size_t n = bodies.size();
    if (n == 0) return;

    std::vector<Vector2> k1_v(n), k1_a(n);
    std::vector<Vector2> k2_v(n), k2_a(n);
    std::vector<Vector2> k3_v(n), k3_a(n);
    std::vector<Vector2> k4_v(n), k4_a(n);

    std::vector<Body> temp_bodies = bodies;

    k1_a = computeAccelerations(temp_bodies);

    // k1: estimated at initial istant
    for (std::size_t i = 0; i < n; ++i) k1_v[i] = temp_bodies[i].velocity;

    // k2: estimated at half dt using k1
    for (std::size_t i = 0; i < n; ++i) {
        temp_bodies[i].position = bodies[i].position + k1_v[i] * (dt / 2.0);
        temp_bodies[i].velocity = bodies[i].velocity + k1_a[i] * (dt / 2.0);
    }
    k2_a = computeAccelerations(temp_bodies);
    for (std::size_t i = 0; i < n; ++i) k2_v[i] = temp_bodies[i].velocity;

    // k3:
    for (std::size_t i = 0; i < n; ++i) {
        temp_bodies[i].position = bodies[i].position + k2_v[i] * (dt / 2.0);
        temp_bodies[i].velocity = bodies[i].velocity + k2_a[i] * (dt / 2.0);
    }
    k3_a = computeAccelerations(temp_bodies);
    for (std::size_t i = 0; i < n; ++i) k3_v[i] = temp_bodies[i].velocity;

    // k4:
    for (std::size_t i = 0; i < n; ++i) {
        temp_bodies[i].position = bodies[i].position + k3_v[i] * dt;
        temp_bodies[i].velocity = bodies[i].velocity + k3_a[i] * dt;
    }
    k4_a = computeAccelerations(temp_bodies);
    for (std::size_t i = 0; i < n; ++i) k4_v[i] = temp_bodies[i].velocity;

    // final
    for(size_t i = 0; i < n; ++i) {
        bodies[i].position = bodies[i].position +
            (k1_v[i] + k2_v[i] * 2.0 + k3_v[i] * 2.0 + k4_v[i]) * (dt / 6.0);

        bodies[i].velocity = bodies[i].velocity +
            (k1_a[i] + k2_a[i] * 2.0 + k3_a[i] * 2.0 + k4_a[i]) * (dt / 6.0);
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

double Simulator::getAngularMomentum() const {
    double tot_angular_momentum = 0.0;
    for (const auto& body : bodies) {
        tot_angular_momentum += body.mass * body.position.crossProduct(body.velocity);
    }
    return tot_angular_momentum;
}