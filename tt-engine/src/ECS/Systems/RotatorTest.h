#ifndef ROTATOR_TEST_H
#define ROTATOR_TEST_H




// TEST HEADER; DELETE ASAP


#include "System.h"
#include "../EntityFactory.h"
#include "raylib.h"
#include "raymath.h"
#include "../Components/Transform.h"

namespace TTEngine {

	class Rotator : public System
	{
	public:
		void Init();
		void Update(float dt);
	};

}

#endif // !ROTATOR_TEST_H

