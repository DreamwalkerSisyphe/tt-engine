#include "raylib.h"
#include "raymath.h"

#include "include/GameCamera.h"
#include "include/ModelLoader.h"

int main(int argc, char* argv[]) {
	InitWindow(800, 600, "tt-engine");
    
    GameCamera *gameCamera = new GameCamera();
    Camera3D camera = gameCamera->GetCamera();

    Vector3 origin = { 0.0f, 0.0f, 0.0f };

    Neco *neco = new Neco();


    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(GRAY);

        gameCamera->HandleRotation(camera);
        BeginMode3D(camera);
        DrawModel(neco->GetNeco(), origin, 1.0f, WHITE);
        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawText("buru nyuu~", 800 - 200, 600 - 20, 10, WHITE);

        EndDrawing();
    }

    CloseWindow();

	return 0;
}