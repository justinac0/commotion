#include "commotion/point_mass_force_generator.hpp"
#include <iostream>

Commotion::PointMassGravity::PointMassGravity(const Vector2& gravity) {
    this->gravity = gravity;
}


void Commotion::PointMassGravity::updateForce(PointMass* point, real delta_time) {
    point->add_force(gravity * point->mass);
}


// Commotion::PointMassDrag::PointMassDrag(real k1, real k2) {
//     this->k1 = k1;
//     this->k2 = k2;
// }

// void Commotion::PointMassDrag::updateForce(PointMass* point, real delta_time) {
//     Vector2 force = point->velocity;

//     real dragCoeff = force.magnitude();
//     dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

//     Vector2 norm_force = force.normalize();
//     force *= norm_force * -dragCoeff;
//     force.print();
//     point->add_force(force);
// }


void Commotion::PointMassForceRegistry::add(PointMass* point, PointMassForceGenerator* generator) {
    PointMassForceRegistration registration;
    registration.point = point;
    registration.forceGenerator = generator;

    registrations.push_back(registration);
}


void Commotion::PointMassForceRegistry::remove(PointMass* point, PointMassForceGenerator* generator) {
    for (auto& registration : registrations) {
        if (registration.point == point) {
            std::cout << "point mass found..." << std::endl;
        }
    }
}


void Commotion::PointMassForceRegistry::clear() {

}


void Commotion::PointMassForceRegistry::updateForces(real delta_time) {
    Registry::iterator i = registrations.begin();
    for (; i != registrations.end(); i++) {
        i->forceGenerator->updateForce(i->point, delta_time);
    }
}
