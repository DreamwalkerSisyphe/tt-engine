#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <random>

#include "GameCamera.h"
#include "ModelLoader.h"
#include "ECS/EntityFactory.h"
#include "ECS/Systems/RotatorTest.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Components/Renderable.h"




using namespace TTEngine;

EntityFactory entityFactory;


int main(int argc, char* argv[]) {
	InitWindow(800, 600, "tt-engine");

	entityFactory.Init();
	entityFactory.RegisterComponent<Transform>();
	entityFactory.RegisterComponent<Renderable>();
	auto rotator = entityFactory.RegisterSystem<Rotator>();
	auto renderSystem = entityFactory.RegisterSystem<RenderSystem>();
	Signature signature;
	signature.set(entityFactory.GetComponentType<Transform>());
	signature.set(entityFactory.GetComponentType<Renderable>());
	entityFactory.SetSystemSignature<Rotator>(signature);
	entityFactory.SetSystemSignature<RenderSystem>(signature);
	std::vector<Entity> entities(MAX_ENTITIES);

	Renderable renderable;
	renderable.model = LoadModel("assets/neco/neco.obj");


	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);

	for (auto& entity : entities) {
		std::cout << "CREATING ENTITY\n";
		entity = entityFactory.CreateEntity();
		Transform transform;
		transform.translation = Vector3{ randPosition(generator), randPosition(generator), randPosition(generator) };
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
		//rotator->Update(1.0f);

		BeginMode3D(camera);

		renderSystem->Update(1.0f);

		DrawGrid(10, 1.0f);
		EndMode3D();

		DrawText("buru nyuu~", 800 - 200, 600 - 20, 10, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}