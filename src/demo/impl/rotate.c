#include <assert.h>

#include <raylib.h>

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
	camera->zoom = 1.0f;

    b = bodies_add(
        vec2(0, 0),
        shape_create(vec2(0, 0),
            vec2(100,50),
            0,
            RED,
            S_RECTANGLE),
        10.0f
    );

    b->state.angular.acceleration = 0.5f;
}

void demo_draw() {
    real x = b->state.position.x;
    real y = b->state.position.y;
    real sx = b->shape.size.x;
    real sy = b->shape.size.y;

    // NOTE: why is this in deg???
    real theta = b->state.angular.theta * PI/180;

    DrawLine(x, y, x + sx * cosf(theta), y + sx * sinf(theta), GREEN);
}

void demo_update(real dt) {

}
