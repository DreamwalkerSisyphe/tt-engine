#include "raylib.h"

int main() {
	InitWindow(800, 600, "tt-engine");

    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();

	return 0;
}