#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	void Initialize();
	void Update(float deltaTime);
	void Draw(SDL_Renderer *renderer, float deltaTime);
protected:
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