#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common/defs.h"
#include "integrators/euler.h"
#include "kinematics/forces.h"
#include "kinematics/bodies.h"
#include "ui/menu.h"

void reset() {
	fprintf(stderr, "resetting\n");

	num_bodies = 0;

	Body* b = body_create(vec2(0, 0), 50.0f, 50.0f);
	assert(b);
}

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "commotion");

	Camera2D camera;
	camera.offset = (Vector2){
		HALF_SCREEN_WIDTH,
		HALF_SCREEN_HEIGHT
	};
	camera.target = (Vector2){0};
	camera.rotation = 0.0f;
	camera.zoom = 0.45E-6f;

	float t = 0.0f;
	float dt = 0.01f;
	float accumulator = 0.0f;
	float lastTime = GetTime();
	
	// TODO: Initializer would be nice
	#define VISUAL_SCALING_FACTOR 10.0f
	Body* earth = body_create(vec2(0, 0), EARTH_MASS, EARTH_RADIUS * VISUAL_SCALING_FACTOR);
	assert(earth);

	Body* moon = body_create(vec2(LUNAR_DISTANCE, 0), MOON_MASS, MOON_RADIUS * VISUAL_SCALING_FACTOR);
	assert(moon);
	#undef VISUAL_SCALING_FACTOR

	Body* target = NULL;

	bool paused = false;

	while (!WindowShouldClose()) {
		float currentTime = GetTime();
		float frameTime = currentTime - lastTime;
		lastTime = currentTime;

		if (!paused) {
			accumulator += frameTime * 10;
		}
		
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);
		if (!target) {
			camera.target = (Vector2){
				.x = earth->state.position.x,
				.y = earth->state.position.y,
			};
		} else {
			camera.target = (Vector2){
				.x = target->state.position.x,
				.y = target->state.position.y,
			};
		}
		for (size_t i = 0; i < num_bodies; i++) {
			body_draw(&bodies[i], target);
		}
		EndMode2D();
		
		draw_menu(target);
		
		if (paused) {
			DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.5f));
			int halfText = MeasureText("PAUSED!!!", 48)/2;
			DrawText("PAUSED!!!", HALF_SCREEN_WIDTH - halfText, HALF_SCREEN_HEIGHT - 24, 48, RED);
		}
		DrawFPS(10, 10);

		EndDrawing();

		// TODO: This should a function
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse = GetMousePosition();
			Vector2 world = GetScreenToWorld2D(mouse, camera);

			Vec2 position = vec2(world.x, world.y);			
			target = body_get(position);
		}

		#define ROTATION_FORCE 1E32
		// https://gamedev.stackexchange.com/questions/70075/how-can-i-find-the-perpendicular-to-a-2d-vector
		if (IsKeyPressed(KEY_W)) {
			Vec2 direction = vec2_subv(moon->state.position, earth->state.position);
			Vec2 clockwise_orbit = vec2_unit(vec2(direction.y, -direction.x));
			Vec2 force = vec2_mulr(clockwise_orbit, ROTATION_FORCE);
			body_add_force(moon, force);			
		}
		if (IsKeyPressed(KEY_S)) {
			Vec2 direction = vec2_subv(moon->state.position, earth->state.position);
			Vec2 anticlockwise_orbit = vec2_unit(vec2(-direction.y, direction.x));
			Vec2 force = vec2_mulr(anticlockwise_orbit, ROTATION_FORCE);
			body_add_force(moon, force);			
		}
		#undef ROTATION_FORCE

		if (IsKeyPressed(KEY_R)) reset();
		if (IsKeyPressed(KEY_SPACE)) paused = !paused;
		
		if (accumulator >= dt && !paused) {
			t += dt;
			accumulator -= dt;

			body_add_force(earth, orbit(moon, earth));
			body_add_force(moon, orbit(earth, moon));

			// TODO: move this to a bodies_* function
			for (size_t i = 0; i < num_bodies; i++) {
				body_integrate(&bodies[i], dt);
			}
		}
	}

	CloseWindow();

	return 0;
}
