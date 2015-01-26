#include "Game.h"
#include <SDL.h>
#include <math.h>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Game();
	}
	return _instance;
}

Game::Game() : GameEngine()
{

}

void Game::InitializeImpl()
{
	// Using the default member-wise initializer for our new struct.
	pos = { 320.0f, 320.0f };
	endPointOffSet = { 10.0f, 0.0f };
	speed = 50.0f;
	rotationSpeed = 10.0f;
}

void Game::UpdateImpl(float dt)
{
	SDL_Event evt;
	SDL_PollEvent(&evt);
	// Check for user input.
	if (evt.type == SDL_KEYDOWN)
	{
		SDL_KeyboardEvent &keyboardEvt = evt.key;
		SDL_Keycode &keyCode = keyboardEvt.keysym.sym;
		switch (keyCode)
		{
		case SDLK_UP:
			vel.x += speed * directionVector.x * dt;
			vel.y += speed * directionVector.y * dt;
			vel.x *= 0.9999999;//very nice effect vs 0.99 not so nice
			vel.y *= 0.9999999;
			break;
		case SDLK_DOWN:
			vel.x -= speed * directionVector.x * dt;
			vel.y -= speed * directionVector.y * dt;
			vel.x *= 0.9999999;
			vel.y *= 0.9999999;
			break;
		case SDLK_RIGHT:
			rotationDegrees -= rotationSpeed * dt;
			if (rotationDegrees > pi)
				rotationDegrees = -pi;
			else if (rotationDegrees < -pi){
				rotationDegrees = pi;
			}
			break;
		case SDLK_LEFT:
			rotationDegrees += rotationSpeed * dt;
			if (rotationDegrees > pi)
				rotationDegrees = -pi;
			else if (rotationDegrees < -pi){
				rotationDegrees = pi;
			}
			break;
		case SDLK_SPACE:
			//Projectile pewpew;
			//pewpew.projVel += pewpew.timer
			//	SDL_RenderDrawPoint(renderer,directionVect.x,directionVect.y);
			break;
		default:
			break;
		}
	}
	pos.x = vel.x * dt;
	pos.y = vel.y * dt;
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
	// Set the draw colour for our point.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Draw the point.
	//SDL_RenderDrawPoint(renderer, posX, posY);

	float rotationRadians = MathUtils::ToRadians(rotationDegrees);

	Vector2 rotatedOffset =
	{
		endPointOffSet.x * cosf(rotationRadians) + endPointOffSet.y * sinf(rotationRadians),
		endPointOffSet.x * sinf(rotationRadians) - endPointOffSet.y * cosf(rotationRadians)
	};

	Vector2 transformedEndPoint = { pos.x + rotatedOffset.x, pos.y + rotatedOffset.y };
	//SDL_RenderDrawLine(renderer, pos.x, pos.y, transformedEndPoint.x, transformedEndPoint.y);

	_player.Draw(renderer, dt);
}