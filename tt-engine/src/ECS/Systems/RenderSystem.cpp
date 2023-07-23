#include "RenderSystem.h"

using namespace TTEngine;

extern EntityFactory entityFactory;

void RenderSystem::Init() {

}

void RenderSystem::Update(float dt) {
	for (auto const& entity : mEntities)
	{
		auto& transform = entityFactory.GetComponent<CTransform>(entity);
		auto& renderable = entityFactory.GetComponent<CRenderable>(entity);
		DrawModel(renderable.model, transform.position, 1.0f, WHITE);
	}
}