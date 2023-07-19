#ifndef ENTITY_MANAGER_H
#define ENNTITY_MANAGER_H

#include "Types.h"
#include <queue>
#include <array>
#include <assert.h>



namespace TTEngine {

	class EntityManager {
	private:
		std::queue<Entity> mAvailableEntities{};
		std::array<Signature, MAX_ENTITIES> mSignatures{};
		uint32_t mLivingEntitiesCount = 0;

	public:
		EntityManager();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void SetSignature(Entity entity, Signature signature);
		Signature GetSignature(Entity entity);
	};


}


#endif // !ENTITY_MANAGER_H
