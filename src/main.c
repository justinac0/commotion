#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common/defs.h"
#include "integrators/euler.h"
#include "kinematics/forces.h"
#include "kinematics/bodies.h"
#include "ui/menu.h"
#include "demo/demo.h"

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "commotion");
	
	Camera2D camera;

	real t = 0.0f;
	real dt = 0.01f;
	real accumulator = 0.0f;
	real lastTime = GetTime();
	
	demo_init(&camera);
	
	Body* target = NULL;
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
		BeginMode2D(camera);
		if (target) {
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
			target = bodies_nearest(position);
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
