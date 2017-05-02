#include "CoreGame.h"
#include <iostream>
#include <string>

Transform transform;

CoreGame::CoreGame(){

	// Set the current state as playing and then create our windowclass.
	_currentState = State::PLAY;
	WindowClass* _gameWindow = new WindowClass();

	// Create 3 seperate meshes.
	Mesh* mesh1(); 
	Mesh* mesh2();
	Mesh* mesh3();

}

// Used to move camera with keypress, doesn't work at the moment.
void CoreGame::keyPress(SDL_Keycode key){

	if (key == SDLK_LEFT){

		camera.MoveCamLeft(100.0f);

	}
	if (key == SDLK_RIGHT){

		camera.MoveCamRight(100.0f);

	}
	if (key == SDLK_UP){

		camera.MoveCamForward(100.0f);

	}
	if (key == SDLK_DOWN){

		camera.MoveCamBack(100.0f);

	}
	if (key == SDLK_a){


	}
	if (key == SDLK_d){


	}

}
	

CoreGame::~CoreGame(){


}

void CoreGame::runGame(){

	// Create the game window and then run the game loop
	initialiseGame();
	mainLoop();

}

void CoreGame::initialiseGame(){

	// Creation of the application window
	_gameWindow.createWindow(); // Create the game window.
	mesh1.loadModel("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\monkey3.obj"); // Load the first model from the file path input.
	mesh2.loadModel("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\BENQ.obj"); // Load the second model from the file path input.
	mesh3.loadModel("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\monkey3.obj"); // Load the third model from the file path input.
	camera.CreateCamera(glm::vec3(0, 0, -5), 70.0f,
		(float)_gameWindow.getResWidth() / _gameWindow.getResHeight(), 0.01f, 1000.0f); // Create the camera.

}

void CoreGame::mainLoop(){

	// When the game is running, poll the inputs and draw the game
	while (_currentState != State::QUIT){
		
		pollInput();
		renderGame();

	}

}

void CoreGame::pollInput(){

	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)){
		switch (sdlEvent.type)
		{
			// Change the state to quit, this will exit the application.
		case SDL_QUIT:
			_currentState = State::QUIT;
			break;

			// If a key is pressed send the key pressed into the keyPress() method. (Meant to be used to move the camera, doesn't work.)
		case SDL_KEYDOWN:
			keyPress(sdlEvent.key.keysym.sym);
			break;

		}
	}
}

void CoreGame::renderGame(){

	_gameWindow.clearWindow(0.0f, 0.0f, 0.0f, 1.0f); // Clear colours.

	Shader shader(".\\res\\shader"); // Create new shader.
	TextureClass texture1("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\white.jpg"); // create new texture using the file given.
	TextureClass texture2("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\bricks.jpg");
	TextureClass texture3("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\water.jpg");

	transform.SetPosition(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRotation(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));

	shader.BindShader(); // Bind the Shader.
	shader.Update(transform); // Update the shader with the transform.
	texture1.BindTexture(0); // Bind the first texture.
	mesh1.RenderMesh(); // Render the first model.
	texture2.BindTexture(0); // Bind the second texture.
	mesh2.RenderMesh(); // Render the second model.
	texture3.BindTexture(0); // Bind the third texture.
	mesh3.RenderMesh(); // Render the second model.


	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameWindow.swapBuffer(); // Swap the buffer.


}