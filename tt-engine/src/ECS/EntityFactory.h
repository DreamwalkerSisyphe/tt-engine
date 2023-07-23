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
		std::unique_ptr<ComponentManager> mComponentManager;		//Pointer to component manager
		std::unique_ptr<EntityManager> mEntityManager;				//Pointer to entity manager
		std::unique_ptr<SystemManager> mSystemManager;				//Pointer to system manager

	public:
		///Set up pointers
		void Init();

		///Notify entity manager to create an entity
		Entity CreateEntity();

		///Notify all managers to destroy an entity
		void DestroyEntity(Entity entity);


		///Notify the component manager to register a new component
		template<typename T>
		void RegisterComponent() {
			mComponentManager->RegisterComponent<T>();
		}

		///Add a component to an entity and update the signature
		template<typename T>
		void AddComponent(Entity entity, T component) {
			mComponentManager->AddComponent<T>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		///Remove a component from an entity and update the signature
		template<typename T>
		void RemoveComponent(Entity entity) {
			mComponentManager->RemoveComponent<T>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		///Ask the component manager for a component
		template<typename T>
		T& GetComponent(Entity entity) {
			return mComponentManager->GetComponent<T>(entity);
		}

		///Ask the component manager for a component type
		template<typename T>
		ComponentType GetComponentType() {
			return mComponentManager->GetComponentType<T>();
		}

		///Notify the system manager to register a new system
		template<typename T>
		std::shared_ptr<T> RegisterSystem() {
			return mSystemManager->RegisterSystem<T>();
		}

		///Notify the system manager to set the signature
		template<typename T>
		void SetSystemSignature(Signature signature) {
			mSystemManager->SetSignature<T>(signature);
		}
	};







}



#endif // !ENTITY_FACTORY_H
