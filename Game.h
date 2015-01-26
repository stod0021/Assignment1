#pragma once

#include "GameEngine.h"

class Game : public GameEngine
{
	friend class GameEngine;

protected:
	Game();

	void InitializeImpl();
	void UpdateImpl(float dt);
	void DrawImpl(SDL_Renderer *renderer, float dt);

	Player _player;

	// Using the default member-wise initializer for our new struct.
	Vector2 pos;
	Vector2 vel;
	Vector2 directionVector;
	Vector2 endPointOffSet;
	Vector3 transformedEndPoint;

	const float pi = 3.1415926535f;
	float speed;
	float acceleration;
	float rotationRadians;
	float rotationDegrees;
	float rotationSpeed;
};