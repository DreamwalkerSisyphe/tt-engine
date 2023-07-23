#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H


#include "Types.h"
#include "Systems/System.h"
#include <set>
#include <unordered_map>
#include <memory>
#include <assert.h>

namespace TTEngine {

	class SystemManager {
	private:
		std::unordered_map<const char*, Signature> mSignatures{};						//Hashmap from string pointer to signature
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};			//Hashmap from string pointer to system pointer

	public:
		///Create a pointer to the system and return it
		template<typename T>
		std::shared_ptr<T> RegisterSystem() {
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) == mSystems.end() && "Trying to register system more than once.");

			auto system = std::make_shared<T>();
			mSystems.emplace(std::make_pair(typeName, system));
			return system;
		}

		///Set signature for this system
		template<typename T>
		void SetSignature(Signature signature) {
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) != mSystems.end() && "Trying to use system before registering it.");

			mSignatures.emplace(std::make_pair(typeName, signature));
		}

		///Remove destroyed entity from all system lists
		void EntityDestroyed(Entity entity);

		///Notify all systems that an entity's signature has changed
		void EntitySignatureChanged(Entity entity, Signature entitySignature);
	};





}




#endif // !SYSTEM_MANAGER_H
