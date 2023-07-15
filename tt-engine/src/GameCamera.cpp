#include "GameCamera.h"
#include "raymath.h"


GameCamera::GameCamera() {
	camera              = { 0 };
	camera.position     = Vector3{ 0.0f, 0.0f, 5.0f };
	camera.target       = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.up           = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy         = 45.0f;
	camera.projection   = CAMERA_PERSPECTIVE;

    camDist             = 10.0f;	
    rotAngle            = 90.0f;		
    tiltAngle           = -25.0f;
    rotSpeed            = 0.25f;
    moveSpeed           = 3.0f;

    moveVec             = { 0.0f, 0.0f, 0.0f };
    cameraOffset        = { 0.0f, 0.0f, 0.0f };

    cursorPos           = GetMousePosition();
    newPos              = cursorPos;
}

GameCamera::~GameCamera() {
	delete &camera;
}

Camera3D& GameCamera::GetCamera()
{
	return camera;
}

void GameCamera::HandleRotation(Camera3D &camera)
{
    // only rotate on left click
    if (IsMouseButtonDown(0))
    {
        newPos = GetMousePosition();

        // update angles with the difference between cursor positions
        rotAngle    += (newPos.x - cursorPos.x) * rotSpeed;
        tiltAngle   += (newPos.y - cursorPos.y) * rotSpeed;

        // clamp tilt so we don't flip
        if (tiltAngle > 89)
            tiltAngle = 89;
        if (tiltAngle < -89)
            tiltAngle = -89;
    }

    // always update the position so we don't get jumps
    cursorPos = GetMousePosition();
    moveVec = { 0,0,0 };

    // eww eww stinky separate inputs from action
    if (IsKeyDown(KEY_W))
        moveVec.z = -moveSpeed * GetFrameTime();
    if (IsKeyDown(KEY_S))
        moveVec.z = moveSpeed * GetFrameTime();

    if (IsKeyDown(KEY_A))
        moveVec.x = -moveSpeed * GetFrameTime();
    if (IsKeyDown(KEY_D))
        moveVec.x = moveSpeed * GetFrameTime();

    if (IsKeyDown(KEY_Q))
        moveVec.y = moveSpeed * GetFrameTime();
    if (IsKeyDown(KEY_E))
        moveVec.y = -moveSpeed * GetFrameTime();

    // update zoom
    camDist += GetMouseWheelMove();
    if (camDist < 1)
        camDist = 1;

    // update offset from target point
    cameraOffset = { 0, 0, camDist };

    Matrix tiltMat  = MatrixRotateX(tiltAngle * GetFrameTime());    // tilt rotation
    Matrix rotMat   = MatrixRotateY(rotAngle * GetFrameTime());     // plane rotation
    Matrix mat      = MatrixMultiply(tiltMat, rotMat);              // believe it or not, both rotations

    cameraOffset    = Vector3Transform(cameraOffset, mat);          // from camera position to world space vector
    moveVec         = Vector3Transform(moveVec, rotMat);            // from movement vector to world space vector

    camera.target   = Vector3Add(camera.target, moveVec);           // move target point

    camera.position = Vector3Add(camera.target, cameraOffset);      // offset the camera with the target point
}