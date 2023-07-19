#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H


#include "Types.h"
#include <assert.h>
#include <array>
#include <unordered_map>


namespace TTEngine {

	class IComponentArray {
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	/// Tightly packed mapping of all components
	template<typename T>
	class ComponentArray : public IComponentArray {
	private:
		std::array<T, MAX_ENTITIES> mComponentArray;
		std::unordered_map<Entity, size_t> mEntityToIndexMap;
		std::unordered_map<size_t, Entity> mIndexToEntityMap;
		size_t mSize;

	public:
		/// Add a T component to an entity
		void InsertData(Entity entity, T component) {
			assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Tried to add component to the same entity more than once.");

			size_t newIndex = mSize;
			mEntityToIndexMap[entity] = newIndex;
			mIndexToEntityMap[newIndex] = entity;
			mComponentArray[newIndex] = component;
			mSize++;
		}

		/// Remove a T component from an entity
		void RemoveData(Entity entity) {
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Tried to remove a component that doesn't exist.");

			size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
			size_t indexOfLastElement = mSize - 1;
			mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

			Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
			mEntityToIndexMap[entityOfLastElement] = indexOfLastElement;
			mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			mEntityToIndexMap.erase(entity);
			mIndexToEntityMap.erase(indexOfLastElement);

			mSize++;
		}

		/// Get T component from an entity
		T& GetData(Entity entity) {
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Tried to get data from an entity that doesn't exist.");

			return mComponentArray[mEntityToIndexMap[entity]];
		}

		/// Clean up components when an entity is destroyed
		void EntityDestroyed(Entity entity) override {
			if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
				RemoveData(entity);
			}
		}

	};


}




#endif // !COMPONENT_ARRAY_H
