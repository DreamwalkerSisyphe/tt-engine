#include "EntityFactory.h"

using namespace TTEngine;

	void EntityFactory::Init() {
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}

	Entity EntityFactory::CreateEntity() {
		return mEntityManager->CreateEntity();
	}

	void EntityFactory::DestroyEntity(Entity entity) {
		mEntityManager->DestroyEntity(entity);
		mComponentManager->EntityDestroyed(entity);
		mSystemManager->EntityDestroyed(entity);
	}

