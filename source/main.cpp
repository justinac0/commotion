#include <raylib.h>

#include <iostream>
#include <vector>

#include <commotion/precision.hpp>
#include <commotion/math.hpp>
#include <commotion/point_mass.hpp>


int main(void) {
    const int SCREEN_WIDTH  = 1280;
    const int SCREEN_HEIGHT = 720;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "commotion");
    
    std::vector<Commotion::PointMass> bullets;

    while (!WindowShouldClose()) {
        // UPDATE
        for (auto& bullet : bullets) {
            bullet.integrate(0.033);
        }

        if (IsMouseButtonPressed(0)) {
            Vector2 mp = GetMousePosition();
            Commotion::PointMass newBullet = Commotion::PointMass(Commotion::Vector2(mp.x, mp.y), 0.999, 2);
            newBullet.acceleration.y = 1;
            bullets.push_back(Commotion::PointMass(newBullet));
        }

        // DRAW        
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto& bullet : bullets) {
            DrawCircle(bullet.position.x, bullet.position.y, 5, YELLOW);
        }

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
