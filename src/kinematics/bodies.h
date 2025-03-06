#ifndef BODIES_H
#define BODIES_H

#define MAX_BODIES (10)

#include <raylib.h>

#include "../common/defs.h"
#include "body.h"

extern Body bodies[MAX_BODIES];
extern size_t num_bodies;

Body* body_create(Vec2 position, real mass, real radius);
bool body_destroy(Body* b);
bool body_contains(Body* b, Vec2 position);
Body* body_get(Vec2 position);

#endif // BODIES_H