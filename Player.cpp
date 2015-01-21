#include "Player.h"
#include "MathUtils.h"
#include <math.h>
#include <SDL.h>
#include <iostream>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void Player::Initialize()
{
	// Using the default member-wise initializer for our new struct.
	speed = 10.0f;
	vel = { 0.0f, 0.0f };
    pos = { 320.0f, 320.0f }; // player spawn at centre;
	endPointOffSet = { 10.0f, 0.0f };
	rotationDegrees = rotationDegrees = 10.0f;
	rotationRadians = MathUtils::ToRadians(rotationDegrees);
	directionVector = { cos(rotationRadians), sin(rotationRadians) };
	acceleration = 200.0f;
}

void Player::Update(float deltaTime)
{
	// Draw the point.
	//SDL_RenderDrawPoint(renderer, posX, posY);

	static float rotationDegrees = 10.0f;
	//rotationDegrees += (rotationSpeed * deltaTime);
	//rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);

	rotationRadians = MathUtils::ToRadians(rotationDegrees);

	Vector2 rotatedOffset =
	{
		endPointOffSet.x * cosf(rotationRadians) + endPointOffSet.y * sinf(rotationRadians),
		endPointOffSet.x * sinf(rotationRadians) - endPointOffSet.y * cosf(rotationRadians)
	};

	transformedEndPoint = { pos.x + rotatedOffset.x, pos.y + rotatedOffset.y };


}

void Player::Draw(SDL_Renderer *renderer, float deltaTime)
{
	printf("%f", pos.x);
	SDL_RenderDrawLine(renderer, pos.x, pos.y, transformedEndPoint.x, transformedEndPoint.y);
}


