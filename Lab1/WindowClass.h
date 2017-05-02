#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

using namespace std;

class WindowClass
{
public:

	WindowClass();
	~WindowClass();
	void createWindow();
	void swapBuffer();
	void clearWindow(float r, float g, float b, float a);

	float getResWidth();
	float getResHeight();

private:

	// used to throw an error within the console
	void throwException(std::string exception);

	// application window properties
	SDL_Window* _window;
	float _displayWidth;
	float _displayHeight;

	SDL_GLContext openglContext;

};