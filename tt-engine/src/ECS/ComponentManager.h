#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H


#include "Types.h"
#include "ComponentArray.h"
#include <unordered_map>
#include <memory>

namespace TTEngine {

	class ComponentManager {
	private:
		std::unordered_map<const char*, ComponentType> mComponentTypes{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
		ComponentType mNextComponentType{};

		/// Get static casted pointer to T ComponentArray
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray() {
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
		}

	public:
		/// Register a T component to the ComponentArray
		template<typename T>
		void RegisterComponent() {
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Tried to register component type more than once.");

			mComponentTypes.emplace(std::make_pair(typeName, mNextComponentType));
			mComponentArrays.emplace(std::make_pair(typeName, std::make_shared<ComponentArray<T>>()));
			mNextComponentType++;
		}

		/// Try to get a base T component type
		template<typename T>
		ComponentType GetComponentType() {
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Tried to use component before registering it.");

			return mComponentTypes[typeName];
		}
		
		/// Add component to an entity
		template<typename T>
		void AddComponent(Entity entity, T component) {
			GetComponentArray<T>()->InsertData(entity, component);
		}

		/// Remove component from an entity
		template<typename T>
		void RemoveComponent(Entity entity) {
			GetComponentArray<T>()->RemoveData(entity);
		}

		/// Try to get a T component from an entity
		template<typename T>
		T& GetComponent(Entity entity) {
			return GetComponentArray<T>()->GetData(entity);
		}

		/// Component cleanup
		void EntityDestroyed(Entity entity);
	};




}





#endif // !COMPONENT_MANAGER_H
