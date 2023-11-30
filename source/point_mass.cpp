#include <commotion/point_mass.hpp>

using namespace Commotion;


PointMass::PointMass(const Vector2& position, real damping, real mass) {
    this->position = position;
    this->mass = mass;
    this->damping = damping;
    this->velocity = Vector2();
    this->acceleration = Vector2();
    this->forceAccum = Vector2();

}


void PointMass::add_force(const Vector2& force) {
    this->forceAccum += force;
}


void PointMass::clear_force_accum() {
    this->forceAccum = Vector2();
}


void PointMass::integrate(real delta_time) {
    if (this->mass == 0.0) return;

    assert(delta_time > 0.0);

    this->position += ((this->velocity * delta_time) * (this->damping * delta_time))
        + (this->acceleration * delta_time * delta_time * 0.5);

    Vector2 resultant_acceleration;
    resultant_acceleration = this->acceleration;
    resultant_acceleration += this->forceAccum * (1/this->mass);

    this->velocity += resultant_acceleration * delta_time;
    this->velocity *= powf(this->damping, delta_time);

    this->clear_force_accum();
}
