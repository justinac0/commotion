#include <raylib.h>

#include <iostream>
#include <vector>

#include "commotion/precision.hpp"
#include "commotion/math.hpp"
#include "commotion/point_mass.hpp"
#include "commotion/point_mass_force_generator.hpp"


int main(void) {
    const int SCREEN_WIDTH  = 1280;
    const int SCREEN_HEIGHT = 720;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "commotion");

    Commotion::PointMassForceRegistry point_mass_registry;

    Commotion::PointMass ball(Commotion::Vector2(SCREEN_WIDTH/2, 0), 0.999, 5);
    Commotion::PointMassGravity gravity(Commotion::Vector2(0, 9.8));
    point_mass_registry.add(&ball, &gravity);

    Commotion::real dt = 0.03;

    while (!WindowShouldClose()) {
        // UPDATE
        point_mass_registry.updateForces(dt);
        ball.integrate(dt);

        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(ball.position.x, ball.position.y, 5, YELLOW);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
