#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera{

public: 

	Camera(){ // Empty constructor.
	
	}
	
	void CreateCamera(const glm::vec3& position, float fov, float aspectRatio, float zNear, float zFar){ // Used to create a camera, takes in a position, field of view,
																										 // aspect ratio of the display and both the near and far clipping planes.
		this->position = position; // Camera position.
		this->forwardVec = glm::vec3(0.0f, 0.0f, 1.0f); // Forward vector.
		this->upVec = glm::vec3(0.0f, 1.0f, 0.0f); // Up vector.
		this->projMat = glm::perspective(fov, aspectRatio, zNear, zFar); // Projection matrix for the camera taking in everything explicitly passed into CreateCamera() other than the position.

	}

	inline glm::mat4 FetchProjection() const{ // Used to return the projection matrix of the camera.

		return projMat*glm::lookAt(position, position + forwardVec, upVec); // Return the updated projection matrix.

	}

	// Following methods to move camera do not work currently.
	//void OnKeyDown(SDL_Keycode key);

	void MoveCamForward(float distance){

		position += forwardVec * distance; // Add the forward vector multiplied by the distance to the position to move forward.

	}

	void MoveCamBack(float distance){

		position -= forwardVec * distance; // Subtract the forward vector multiplied by the distance to the position the move backwards.

	}

	void MoveCamRight(float distance){

		position += glm::cross(upVec, forwardVec) * distance; // Add the cross product of the up vector and forward vector multiplied by distance to strafe right.

	}

	void MoveCamLeft(float distance){

		position -= glm::cross(upVec, forwardVec) * distance; // Subtract the cross product of the up vector and forward vector multiplied by distance to strafe right.

	}

private:

	glm::vec3 position;
	glm::vec3 forwardVec;
	glm::vec3 upVec;
	glm::mat4 projMat;

};