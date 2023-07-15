#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"


class GameCamera {
private:
	Camera3D camera;

	float camDist;			// distance from target
	float rotAngle;			// rotation angle around Y
	float tiltAngle;		// up/down tilt

	float rotSpeed;
	float moveSpeed;

	Vector2 cursorPos;
	Vector2 newPos;
	Vector3 moveVec;		// vector we use to update camera position
	Vector3 cameraOffset;	// offset from target point

public:
	GameCamera();
	~GameCamera();
	Camera3D& GetCamera();

	void HandleRotation(Camera3D &camera);
};





#endif	// !CAMERA_H