#include "EntityManager.h"

using namespace TTEngine;

EntityManager::EntityManager() {
	for (Entity e = 0; e < MAX_ENTITIES; e++) {
		mAvailableEntities.push(e);
	}
}

Entity EntityManager::CreateEntity() {
	assert(mLivingEntitiesCount < MAX_ENTITIES && "Couldn't create entity (too many entities).");

	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop();
	mLivingEntitiesCount++;

	return id;
}

void EntityManager::DestroyEntity(Entity entity) {
	assert(entity < MAX_ENTITIES && "Couldn't destroy entity (out of range).");

	mSignatures[entity].reset();
	mAvailableEntities.push(entity);
	mLivingEntitiesCount--;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
	assert(entity < MAX_ENTITIES && "Couldn't set signature (out of range).");

	mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
	assert(entity < MAX_ENTITIES && "Couldn't get signature (out of range).");

	return mSignatures[entity];
}
