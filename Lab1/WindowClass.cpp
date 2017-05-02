#include "WindowClass.h"

WindowClass::WindowClass(){

	_window = nullptr;

	_displayWidth = 1024;
	_displayHeight = 768;


}

WindowClass::~WindowClass(){

	SDL_GL_DeleteContext(openglContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();

}

float WindowClass::getResWidth(){ return _displayWidth; }
float WindowClass::getResHeight(){ return _displayHeight; }

void WindowClass::throwException(std::string exception){

	std::cout << exception << std::endl;
	std::cout << "press any key to quit.";
	int in;
	std::cin >> in;
	SDL_Quit();

}

void WindowClass::clearWindow(float r, float g, float b, float a){

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both colour and depth buffer.

}

void WindowClass::createWindow(){

	SDL_Init(SDL_INIT_EVERYTHING); // Initialising everything from SDL.

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); // Set up the depth buffer.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Set up the double buffer.

	_window = SDL_CreateWindow("GraphicsProgCoursework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		(int)_displayWidth, (int)_displayHeight, SDL_WINDOW_OPENGL); // Method used to create the application window.


	openglContext = SDL_GL_CreateContext(_window); // Creation of the openGL context.

	GLenum error = glewInit();

	if (_window == nullptr){ // In case of window being null.

		throwException("Application failed to create the window.");
	}

	if (openglContext == nullptr){ // In case of openGL context being null.

		throwException("Application failed to create the OpenGL Context.");

	}

	if (error != GLEW_OK){ // If GLEW isn't OK throw and exception.

		throwException("Application failed to initialize GLEW.");

	}

	glEnable(GL_DEPTH_TEST); // Z-Buffering.
	glEnable(GL_CULL_FACE); // Cull any faces not pointing towards camera.

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);


}

void WindowClass::swapBuffer(){

	SDL_GL_SwapWindow(_window);

}

