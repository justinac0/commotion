#pragma once 

#include <iostream>
#include <vector>

#include "commotion/point_mass.hpp"
#include "commotion/precision.hpp"


namespace Commotion {

class PointMassForceGenerator {
public:
    virtual void updateForce(PointMass* point, real delta_time) = 0;
};

class PointMassGravity : public PointMassForceGenerator {
    Vector2 gravity;
public:
    PointMassGravity(const Vector2& gravity);
    virtual void updateForce(PointMass* point, real delta_time);
};


// class PointMassDrag : public PointMassForceGenerator {
//     real k1;
//     real k2;
// public:
//     PointMassDrag(real k1, real k2);
//     virtual void updateForce(PointMass* point, real delta_time);
// };


class PointMassForceRegistry {
protected:
    struct PointMassForceRegistration {
        PointMass* point;
        PointMassForceGenerator* forceGenerator;
    };

    typedef std::vector<PointMassForceRegistration> Registry;
    Registry registrations;

public:
    void add(PointMass* point, PointMassForceGenerator* generator);
    void remove(PointMass* point, PointMassForceGenerator* generator);
    void clear();

    void updateForces(real delta_time);
};

}
