#include "bodies.h"

#include "../common/functions.h"

Body bodies[MAX_BODIES];
size_t num_bodies = 0;

Body* body_create(Vec2 position, real mass, real radius) {
	if (num_bodies >= MAX_BODIES) {
		return NULL;
	}

	Body* b = &bodies[num_bodies++];

    b->state.position = position;
	b->state.velocity = vec2(0, 0);
	b->state.acceleration = vec2(0, 0);
    b->state.force = vec2(0, 0);
    
	b->state.mass = mass;
	b->radius = radius;
    b->color = random_colour();

	return b;
}

bool body_destroy(Body* b) {
	if (b == NULL) {
		return false;
	}

	for (size_t i = 0; i < num_bodies; i++) {
		if (bodies + i == b) {
			// shift all bodies after this over so our array is contiguous
			for (size_t j = i; j < num_bodies - 1; j++) {
				bodies[j] = bodies[j + 1];
			}

			num_bodies--;
			return true;
		}
	}

	return false;
}

bool body_contains(Body* b, Vec2 position) {
	if (b == NULL) {
		return false;
	}

	Vec2 distance = vec2_subv(b->state.position, position);
	return vec2_mag(distance) <= b->radius;
}

// returns the first body found at the given position, overlapping bodies are not supported
Body* body_get(Vec2 position) {
	for (size_t i = 0; i < num_bodies; i++) {
		// check if this 
		if (body_contains(bodies + i, position)) {
			return bodies + i;
		}
	}

	return NULL;
}