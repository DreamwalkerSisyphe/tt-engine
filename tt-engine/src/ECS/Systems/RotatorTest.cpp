#include "RotatorTest.h"


using namespace TTEngine;

extern EntityFactory entityFactory;


void Rotator::Init() {

}

void Rotator::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
			auto& transform = entityFactory.GetComponent<Transform>(entity);
			transform.translation = Vector3Add(transform.translation, { 1.0f, 0.0f, 0.0f });
	}
}
