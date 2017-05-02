#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include "WindowClass.h"
#include "ShaderClass.h"
#include "MeshClass.h"
#include "TransformClass.h"
#include "TextureClass.h"

enum class State{PLAY, QUIT};

class CoreGame
{
public:

	CoreGame();
	~CoreGame();

	void runGame();

	void keyPress(SDL_Keycode key);

private:

	void initialiseGame();
	void pollInput();
	void mainLoop();
	void renderGame();

	WindowClass _gameWindow;
	State _currentState;

	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;

	Camera camera;

};