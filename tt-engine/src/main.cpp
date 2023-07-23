#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <random>

#include "GameCamera.h"
#include "ModelLoader.h"
#include "ECS/EntityFactory.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Components/CRenderable.h"
#include "ECS/Components/CTransform.h"




using namespace TTEngine;

EntityFactory entityFactory;


int main(int argc, char* argv[]) {
	InitWindow(800, 600, "tt-engine");

	// Initializing a bunch of stuff for the ECS
	entityFactory.Init();
	entityFactory.RegisterComponent<CTransform>();
	entityFactory.RegisterComponent<CRenderable>();
	auto renderSystem = entityFactory.RegisterSystem<RenderSystem>();

	Signature signature;
	signature.set(entityFactory.GetComponentType<CTransform>());
	signature.set(entityFactory.GetComponentType<CRenderable>());
	entityFactory.SetSystemSignature<RenderSystem>(signature);

	std::vector<Entity> entities(MAX_ENTITIES);

	CRenderable renderable;
	CTransform transform;
	renderable.model = LoadModel("assets/neco/neco.obj");


	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-10.0f, 10.0f);

	//Create a bunch of stuff to test ecs
	for (auto& entity : entities) {
		entity = entityFactory.CreateEntity();

		transform.position = Vector3{ randPosition(generator),randPosition(generator),randPosition(generator) };

		entityFactory.AddComponent(entity, transform);
		entityFactory.AddComponent(entity, renderable);
	}

	GameCamera* gameCamera = new GameCamera();
	Camera3D camera = gameCamera->GetCamera();


	SetTargetFPS(60);

	// Game Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(GRAY);

		gameCamera->HandleRotation(camera);

		BeginMode3D(camera);

			renderSystem->Update(GetFrameTime());
			DrawGrid(10, 1.0f);

		EndMode3D();

		DrawText("buru nyuu~", 800 - 200, 600 - 20, 10, WHITE);
		DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}