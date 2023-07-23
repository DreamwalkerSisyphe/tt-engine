#ifndef ENTITY_MANAGER_H
#define ENNTITY_MANAGER_H

#include "Types.h"
#include <queue>
#include <array>
#include <assert.h>



namespace TTEngine {

	class EntityManager {
	private:
		std::queue<Entity> mAvailableEntities{};					//Unused IDs
		std::array<Signature, MAX_ENTITIES> mSignatures{};			//Array of Signatures (index is ID)
		uint32_t mLivingEntitiesCount{};							//Current living entities

	public:
		///Initialize queue
		EntityManager();											

		///Get an ID from the queue
		Entity CreateEntity();

		///Return the borrowed ID
		void DestroyEntity(Entity entity);

		///Add entity Signature to the array
		void SetSignature(Entity entity, Signature signature);

		///Get an entity's signature
		Signature GetSignature(Entity entity);
	};


}


#endif // !ENTITY_MANAGER_H
