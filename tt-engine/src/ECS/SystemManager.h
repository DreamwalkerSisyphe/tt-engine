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
		std::unordered_map<const char*, Signature> mSignatures{};
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};

	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem() {
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) == mSystems.end() && "Trying to register system more than once.");

			auto system = std::make_shared<T>();
			mSystems.emplace(std::make_pair(typeName, system));
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature) {
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) != mSystems.end() && "Trying to use system before registering it.");

			mSignatures.emplace(std::make_pair(typeName, signature));
		}

		void EntityDestroyed(Entity entity);
		void EntitySignatureChanged(Entity entity, Signature entitySignature);
	};





}




#endif // !SYSTEM_MANAGER_H
