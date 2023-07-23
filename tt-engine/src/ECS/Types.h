#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <bitset>



namespace TTEngine {

	// ECS definition
	using Entity = std::uint32_t;
	const Entity MAX_ENTITIES = 3000;
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 32;
	using Signature = std::bitset<MAX_COMPONENTS>;


}

#endif // !TYPES_H
