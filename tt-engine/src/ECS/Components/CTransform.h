#ifndef CTRANSFORM_H
#define CTRANSFORM_H


#include "raylib.h"


namespace TTEngine {

	struct CTransform {
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
	};


}

#endif // !CTRANSFORM_H
