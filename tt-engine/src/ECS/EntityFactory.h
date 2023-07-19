#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H


#include "Types.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include <memory>


namespace TTEngine {

	class EntityFactory {
	private:
		std::unique_ptr<ComponentManager> mComponentManager;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<SystemManager> mSystemManager;

	public:
		void Init();
		Entity CreateEntity();
		void DestroyEntity(Entity entity);


		template<typename T>
		void RegisterComponent() {
			mComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(Entity entity, T component) {
			mComponentManager->AddComponent(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(Entity entity) {
			mComponentManager->RemoveComponent(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(Entity entity) {
			return mComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType() {
			return mComponentManager->GetComponentType<T>();
		}

		template<typename T>
		std::shared_ptr<T> RegisterSystem() {
			return mSystemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature signature) {
			mSystemManager->SetSignature<T>(signature);
		}
	};







}



#endif // !ENTITY_FACTORY_H