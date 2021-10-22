#ifndef CAMERA
#define CAMERA

#include <libs/stb_image.h>

#include <src/main.hpp>
#include <include/someSemblantOfAGameEngine/camera.hpp>

Camera::Camera(){};

Camera::Camera
(	
	glm::vec3 cameraPos/*position vector*/,
	glm::vec3 cameraFront/*direction vector*/,
	glm::vec3 cameraUp/*up vector*/,
	float fov/*in degrees*/,
	float aspectRatio,
	float minDistance,
	float maxDistance
){
	Camera::camera		= glm::lookAt(cameraPos,cameraFront + cameraPos,cameraUp);
	Camera::perspective	= glm::mat4(1.0f);
	Camera::perspective	= glm::perspective(glm::radians(fov),aspectRatio,minDistance,maxDistance);
	Camera::fov		= fov;
	Camera::minDistance	= minDistance;
	Camera::maxDistance	= maxDistance;
	Camera::aspectRatio	= aspectRatio;
	Camera::cameraPos	= cameraPos;
	Camera::cameraFront	= cameraFront;
	Camera::cameraUp	= cameraUp;
	glm::vec3 cameraFrontProj(cameraFront);

	cameraFrontProj.y=0.0f;
	Camera::cameraFrontProjected = glm::normalize(cameraFrontProj);



}

void Camera::updateFront(float xTurnAmount,float yTurnAmount){
	// glm::vec3 turnVectorX(glm::normalize(glm::cross(Camera::cameraFront,Camera::cameraUp)));
	// glm::vec3 turnVectorY(glm::normalize(glm::cross(turnVectorX,Camera::cameraFront)));

	// float cos89{0.017452};
	// float lookLeftRightRate{glm::dot(Camera::cameraFront,Camera::cameraFrontProjected)};

	// //	only y addition
	// Camera::cameraFront =	Camera::cameraFront + 
	// 			Camera::mouseSens * yTurnAmount * turnVectorY * deltaTime;
				

	// float cosAngle = glm::dot(Camera::cameraFrontProjected, Camera::cameraFront);
	// float ySigne{(Camera::cameraFront.y<0?-1.0f:1.0f)};

	// //	to fix when crossing the 89 degree pitch angle
	// if(cosAngle<0){
	// 	//Camera::cameraFront=ySigne * (Camera::cameraUp);
	// 	Camera::cameraFront= glm::normalize(Camera::cameraFront + cos89/cosAngle * yTurnAmount);
	// }
	// Camera::cameraFront =	Camera::cameraFront + 
	// 			Camera::mouseSens * xTurnAmount * turnVectorX * deltaTime * lookLeftRightRate +
	// Camera::cameraFrontProjected = glm::normalize(Camera::cameraFrontProjected + Camera::mouseSens * xTurnAmount * turnVectorX * deltaTime * lookLeftRightRate);

	// Camera::cameraFront =	glm::normalize(Camera::cameraFront);

	glm::vec3 lookinDirection{
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))			 
	};
	Camera::cameraFront = glm::normalize(lookinDirection);
	Camera::cameraFrontProjected.x=Camera::cameraFront.x;
	Camera::cameraFrontProjected.z=Camera::cameraFront.z;

	Camera::camera = glm::lookAt(Camera::cameraPos,Camera::cameraFront + Camera::cameraPos,Camera::cameraUp);
	
}

void Camera::updatePosition(){
	Camera::cameraPos += Camera::rightFlag * Camera::speed * glm::normalize(glm::cross(Camera::cameraFrontProjected,Camera::cameraUp)) * deltaTime;
	Camera::cameraPos += Camera::forwardFlag * Camera::speed * glm::normalize(Camera::cameraFront) * deltaTime;
	
	//	refresh camera
	Camera::camera = glm::lookAt(Camera::cameraPos,Camera::cameraFront + Camera::cameraPos,Camera::cameraUp);
}

void Camera::updatePerspective(){
	Camera::perspective = glm::perspective(glm::radians(Camera::fov),Camera::aspectRatio,Camera::minDistance,Camera::maxDistance);
}

glm::vec3 Camera::getFront(){
	return Camera::cameraFront;
}
glm::vec3 Camera::getPos(){
	return Camera::cameraPos;
}

float Camera::getFov(){
	return Camera::pitch;
}
float Camera::getYaw(){
	return Camera::yaw;
}
float Camera::getAspectRatio(){
	return Camera::aspectRatio;
}
float Camera::getMinDistance(){
	return Camera::minDistance;
}
float Camera::getMaxDistance(){
	return Camera::maxDistance;
}
float Camera::getPitch(){
	return Camera::pitch;
}
float Camera::getRightFlag(){
	return Camera::rightFlag;
}
float Camera::getForwardFlag(){
	return Camera::forwardFlag;
}
float Camera::getSpeed(){
	return speed;
}
float Camera::getMouseSens(){
	return Camera::mouseSens;
}
glm::mat4 Camera::getCamera(){
	return Camera::camera;
}
glm::mat4 Camera::getProjection(){
	return Camera::perspective;
}


void Camera::setSpeed(float speed){
	Camera::speed=speed;
}
void Camera::setRightFlag(float val){
	Camera::rightFlag = val;
}
void Camera::setForwardFlag(float val){
	Camera::forwardFlag = val;
}
void Camera::setYaw(float yaw){
	Camera::yaw = yaw;
}
void Camera::setPitch(float pitch){
	if(pitch>89.0f)	pitch = 89.0f;
	if(pitch<-89.0f)pitch = -89.0f;
	
	Camera::pitch = pitch;
}
void Camera::setMouseSens(float sens){
	Camera::mouseSens = sens;
}


#endif