#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

// Preprocessor directive to ensure that this header will only be included once. -- Generally used for all environments.
/*#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#endif // _GAME_ENGINE_H_*/

#include "MathUtils.h"
#include "Player.h"
// Forward declaring our renderer and window.
// Because we're using them as pointers, we don't need to know their size
// at compile time to define this class.
struct SDL_Renderer;
struct SDL_Window;

class GameEngine
{
public:
	static GameEngine* CreateInstance();

	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	~GameEngine();

protected:
	GameEngine();

	static GameEngine *_instance;

	SDL_Window *window;
	SDL_Renderer *renderer;
	Player player; 
	// Using the default member-wise initializer for our new struct.
	Vector2 pos;
	Vector2 vel;
	Vector2 directionVector;
	Vector2 endPointOffSet;
	
	float oldTime, currentTime, deltaTime;
	const float pi = 3.1415926535f;
	float speed;
	float acceleration;
	float rotationRadians;
	float rotationDegrees;
	float rotationSpeed;
};