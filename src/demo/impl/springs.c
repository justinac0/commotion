#include <assert.h>

#include "../../common/defs.h"
#include "../../math/vec2.h"
#include "../../kinematics/body.h"
#include "../../kinematics/bodies.h"
#include "../../kinematics/forces.h"
#include "../demo.h"

static Body *b = NULL;

void demo_init(Camera2D *camera) {
    camera->offset = (Vector2){
		HALF_SCREEN_WIDTH,
		HALF_SCREEN_HEIGHT
	};
	camera->target = (Vector2){0};
	camera->rotation = 0.0f;
	camera->zoom = 1.0f;;

    b = bodies_add(vec2(0, 0), 
        shape_create(vec2(0, 0),
        vec2(25,25),
        0,
        RED,
        S_CIRCLE), 50.0f
    );
    assert(b);
}

void demo_draw() {}

void demo_update(real dt) {
    body_add_force(b, (Vec2){
        .x = spring(0, b->state.position.x, b->state.velocity.x, 10.0, 1.0),
        .y = spring(0, b->state.position.y, b->state.velocity.y, 10.0, 1.0)
    });
}
