#ifndef POINT_MASS_HPP
#define POINT_MASS_HPP


#include <math.h>
#include <commotion/math.hpp>
#include <commotion/precision.hpp>


namespace Commotion {

class PointMass {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 forceAccum;
    
    real damping;
    real mass; // kg

    PointMass(const Vector2& position, real damping, real mass);

    void add_force(const Vector2& force);
    void clear_force_accum();

    void integrate(real delta_time);
};

}

#endif // POINT_MASS_HPP
