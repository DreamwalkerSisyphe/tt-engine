#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "System.h"
#include "../EntityFactory.h"
#include "raylib.h"
#include "raymath.h"
#include "../Components/Transform.h"
#include "../Components/Renderable.h"


namespace TTEngine {


	class RenderSystem : public System
	{
	public:
		void Init();
		void Update(float dt);
	};


}


#endif // !RENDER_SYSTEM_H
