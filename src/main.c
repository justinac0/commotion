#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common/defs.h"
#include "integrators/euler.h"
#include "kinematics/forces.h"
#include "kinematics/bodies.h"
#include "ui/menu.h"
#include "demo/demo.h"

typedef struct {
	Body* target;
	bool isDragging;
	Vec2 targetPosition;
} DragState;
#define DRAGSTATE_NONE ((DragState){.target = NULL, .isDragging = false, .targetPosition = vec2(0, 0)})

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "commotion");
	
	Camera2D camera;

	real t = 0.0f;
	real dt = 0.01f;
	real accumulator = 0.0f;
	real lastTime = GetTime();
	
	demo_init(&camera);
	
	Body* target = NULL;
	DragState dragState = DRAGSTATE_NONE;

	bool paused = false;

	while (!WindowShouldClose()) {
		float currentTime = GetTime();
		float frameTime = currentTime - lastTime;
		lastTime = currentTime;

		if (!paused) {
			accumulator += frameTime * 10.0f;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		if (paused) {
			target = NULL;
			DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(MAGENTA, 0.1f));
		}
		BeginMode2D(camera);
		demo_draw();
		if (target) {
			camera.target = (Vector2){
				.x = target->state.position.x,
				.y = target->state.position.y,
			};
		}
		for (size_t i = 0; i < num_bodies; i++) {
			body_draw(&bodies[i], target);
		}
		
		if (dragState.isDragging && dragState.target && paused) {
			Body ghost = *dragState.target;
			ghost.shape.color = Fade(ghost.shape.color, 0.5f);
			ghost.state.position = dragState.targetPosition;
			ghost.shape.position = dragState.targetPosition;
			body_draw(&ghost, target);
		}
		EndMode2D();

		draw_menu(target);
		
		DrawFPS(10, 10);

		EndDrawing();

		// TODO: This should a function
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse = GetMousePosition();
			Vector2 world = GetScreenToWorld2D(mouse, camera);
			
			Vec2 position = vec2(world.x, world.y);
			Body* found_body = bodies_nearest(position);

			if (!paused) {
				target = found_body;
			}

			if (found_body && paused) {
				dragState.target = found_body;
				dragState.isDragging = true;
				dragState.targetPosition = found_body->state.position;
			} else {
				dragState = DRAGSTATE_NONE;
			}
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			if (dragState.isDragging && dragState.target) {
				dragState.target->state.position = dragState.targetPosition;
				dragState.target->shape.position = dragState.targetPosition;
				dragState = DRAGSTATE_NONE;
			}
		}

		if (dragState.isDragging && dragState.target) {
			// Get the world space position of the mouse
			Vector2 mouse = GetMousePosition();
			Vector2 world = GetScreenToWorld2D(mouse, camera);
			dragState.targetPosition = vec2(world.x, world.y);
		}

		// Reset scene :)
		if (IsKeyPressed(KEY_R)) {
			bodies_clear();
			accumulator = 0;
			demo_init(&camera);
		}

		if (IsKeyPressed(KEY_SPACE)) {
			paused = !paused;
		}

		while (accumulator >= dt && !paused) {
			t += dt;
			accumulator -= dt;

			demo_update(dt);
			// TODO: move this to a bodies_* function
			for (size_t i = 0; i < num_bodies; i++) {
				body_integrate(&bodies[i], dt);
			}
		}
	}

	CloseWindow();

	return 0;
}
