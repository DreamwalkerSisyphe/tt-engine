#include "RenderSystem.h"

using namespace TTEngine;

extern EntityFactory entityFactory;

void RenderSystem::Init() {

}

void RenderSystem::Update(float dt) {
	for (auto const& entity : mEntities)
	{
		auto& transform = entityFactory.GetComponent<Transform>(entity);
		auto& renderable = entityFactory.GetComponent<Renderable>(entity);
		DrawModel(renderable.model, transform.translation, 1.0f, WHITE);
	}
}