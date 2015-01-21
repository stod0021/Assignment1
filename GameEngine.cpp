#include "GameEngine.h"
#include <SDL.h>
#include <math.h>
#include "MathUtils.h"
#include <iostream>
GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = SDL_CreateWindow("Asteroids Beta",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 640,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	player.Initialize();

	/* Get the time at the beginning of our game loop so that we can track the
	* elapsed difference. */
	oldTime = SDL_GetTicks();
	currentTime = oldTime;
}

void GameEngine::Shutdown()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GameEngine::Update()
{
	SDL_Event evt;
	SDL_PollEvent(&evt);

	// Calculating the time difference since our last loop.
	oldTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = (currentTime - oldTime) / 1000;
	// Check for user input.
	if (evt.type == SDL_KEYDOWN)
	{
		SDL_KeyboardEvent &keyboardEvt = evt.key;
		SDL_Keycode &keyCode = keyboardEvt.keysym.sym;
		switch (keyCode)
		{
		case SDLK_UP:
			vel.x += acceleration * directionVector.x * deltaTime;
			vel.y += acceleration * directionVector.y * deltaTime;
			vel.x *= 0.9999999;//very nice effect vs 0.99 not so nice
			vel.y *= 0.9999999;
			break;
		case SDLK_DOWN:
			vel.x -= acceleration * directionVector.x * deltaTime;
			vel.y -= acceleration * directionVector.y * deltaTime;
			vel.x *= 0.9999999;
			vel.y *= 0.9999999;
			break;
		case SDLK_RIGHT:
			rotationRadians -= rotationSpeed * deltaTime;
			if (rotationRadians > pi)
				rotationRadians = -pi;
			else if (rotationRadians < -pi){
				rotationRadians = pi;
			}
			break;
		case SDLK_LEFT:
			rotationRadians += rotationSpeed * deltaTime;
			if (rotationRadians > pi)
				rotationRadians = -pi;
			else if (rotationRadians < -pi){
				rotationRadians = pi;
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
	pos.x = vel.x * deltaTime;
	pos.y = vel.y * deltaTime;
	player.Update(deltaTime);
}

void GameEngine::Draw()
{
	// Set the draw colour for screen clearing.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	// Clear the renderer with the current draw colour.
	SDL_RenderClear(renderer);

	// Set the draw colour for our point.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Draw the player
	player.Draw(renderer, deltaTime);

	// Present what is in our renderer to our window.
	SDL_RenderPresent(renderer);
}