#ifndef BODY_H
#define BODY_H

#include <stdio.h> // temp
#include <stddef.h>

#include "../math/vec2.h"

// TODO: drawing should happen outside of the kinematics
//       logic.
#include <raylib.h>


typedef enum ShapeType {
    S_CIRCLE,
    S_RECTANGLE,
} ShapeType;

typedef struct Shape {
    Vec2 position;
    Vec2 size;
    real rotation;
    Color color;
    ShapeType type;
} Shape;

Shape shape_create(Vec2 position, Vec2 size, real rotation, Color color, ShapeType type);

typedef struct Angular {
    real velocity;
    real acceleration;
    real theta;
} Angular;

typedef struct State {
    // translational
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    // rotational
    Angular angular;

    // misc
    float mass; // kg
    Vec2 force;
} State;

typedef struct Body {
    State state;
    Shape shape;
} Body;

void body_draw(Body *b, Body *target);
void body_add_force(Body *b, Vec2 f);
void body_clear_forces(Body *b);
void body_integrate(Body *b, float dt);

#endif // BODY_H