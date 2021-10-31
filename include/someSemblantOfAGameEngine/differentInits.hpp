#ifndef DIFFERENTINITS_HPP
#define DIFFERENTINITS_HPP

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <filesystem>	

//	gl matrix and math shitery
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

namespace glfwInits{
	//	returns -1 if error
	int init();
	GLFWwindow* initWindow(int width,int height);
}
namespace gladInits{
	//	returns -1 if error
	int init();
}
namespace glInits{
	//	returns -1 if error
	int init();
}

#endif