#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Types.h"
#include "raylib.h"
#include <set>

namespace TTEngine {

	class System
	{
	public:
		std::set<Entity> mEntities;
	};

}

#endif // !SYSTEM_H
