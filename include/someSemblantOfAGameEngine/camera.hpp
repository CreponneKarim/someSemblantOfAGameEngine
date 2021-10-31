#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

//	gl matrix and math shitery
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//	image data retrieving
#include <libs/stb_image.h>

class Camera{
	private:
		float rightFlag{0};
		float forwardFlag{0};

		glm::vec3 cameraPos/*position vector*/;
		glm::vec3 cameraFront/*direction vector*/;
		glm::vec3 cameraUp/*up vector*/;
		glm::vec3 cameraFrontProjected;
		float aspectRatio;
		float minDistance;
		float maxDistance;
		float fov;
		float speed;
		float mouseSens;

		float yaw	{-90.0f};
		float pitch	{0.0f};

		glm::mat4 camera;//		view matrix
		glm::mat4 perspective;//	projection matrix
		//	model doesn't have to do anything with camera
		//	it rather acts on objects
		//	so we stick with projection and view matrix
	public :
		//	constructors
		Camera();
		Camera(	glm::vec3 cameraPos/*position vector*/,
			glm::vec3 cameraFront/*direction vector*/,
			glm::vec3 cameraUp/*up vector*/,
			float fov/*in degrees*/,
			float aspectRatio,
			float minDistance,
			float maxDistance);

		//	"methods"(more like functions.. meh whatever)
		void updateFront(float xTurnAmount,float yTurnAmount);
		void updatePosition();
		void updatePerspective();

		//getters and setters
		glm::vec3 getFront();
		glm::vec3 getPos();
		float getFov();
		float getYaw();
		float getAspectRatio();
		float getMinDistance();
		float getMaxDistance();
		float getPitch();
		float getRightFlag();
		float getForwardFlag();
		float getSpeed();
		float getMouseSens();
		glm::mat4 getCamera();
		glm::mat4 getProjection();

		void setSpeed(float speed);
		void setRightFlag(float val);
		void setForwardFlag(float val);
		void setYaw(float yaw);
		void setPitch(float pitch);
		void setMouseSens(float sens);
		void setAspectRatio(float aspectRatio);
};

#endif