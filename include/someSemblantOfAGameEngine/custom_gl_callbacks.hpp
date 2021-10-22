#ifndef	GL_CUSTOM_CALLBACKS_HPP
#define	GL_CUSTOM_CALLBACKS_HPP

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
#include <src/main.hpp>

namespace callbackGlobals{
	inline int cameraNumber;
	inline int lastMouseXpos{window::width/2};
	inline int lastMouseYpos{window::height/2};
	inline bool firstMouseMovement{true};
	inline bool wireframeOn{false};
};

inline int rightFlag{0};
inline int forwardFlag{0};

//	framebuffer callback (in case of resizing for example)
void framebuffer_size_callback(GLFWwindow *window, int width,int height);
//	keyboard input callback
void key_input_callback(GLFWwindow *window,int key, int scancode,int action, int mods);
//	mouse movement callbacc
void mouseCallback(GLFWwindow *win,double xpos,double ypos);
#endif