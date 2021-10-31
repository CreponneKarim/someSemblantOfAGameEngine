#ifndef	GL_CUSTOM_CALLBACKS
#define	GL_CUSTOM_CALLBACKS

#include <include/someSemblantOfAGameEngine/custom_gl_callbacks.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width,int height){
	glViewport(0,0,width,height);
}
void key_input_callback(GLFWwindow *window,int key, int scancode,int action, int mods){
	if(	key == GLFW_KEY_T && action == GLFW_PRESS){
		renderingMode=!renderingMode;
	
		if(renderingMode)	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
		else			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
	}
	if(renderingMode){
		if(	key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
			glfwSetWindowShouldClose(window,true);
		}if(	key == GLFW_KEY_Q && action == GLFW_PRESS){
			if(!(callbackGlobals::wireframeOn)){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		callbackGlobals::wireframeOn= !callbackGlobals::wireframeOn;
		}if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
			if(callbackGlobals::cameraNumber==0)	callbackGlobals::cameraNumber+=3;
			callbackGlobals::cameraNumber--;
		}if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
			callbackGlobals::cameraNumber++;
		}else if(	key == GLFW_KEY_W && action == GLFW_PRESS){	forwardFlag +=+1;
		}else if(	key == GLFW_KEY_S && action == GLFW_PRESS){	forwardFlag +=-1;
		}else if(	key == GLFW_KEY_D && action == GLFW_PRESS){	rightFlag   +=+1;
		}else if(	key == GLFW_KEY_A && action == GLFW_PRESS){	rightFlag   +=-1;
		}else if(	key == GLFW_KEY_W && action == GLFW_RELEASE){	forwardFlag +=-1;
		}else if(	key == GLFW_KEY_S && action == GLFW_RELEASE){	forwardFlag +=+1; 
		}else if(	key == GLFW_KEY_D && action == GLFW_RELEASE){	rightFlag   +=-1;
		}else if(	key == GLFW_KEY_A && action == GLFW_RELEASE){	rightFlag   +=+1;
		}
	}


	camera.setForwardFlag(forwardFlag);
	camera.setRightFlag(rightFlag);

}
void mouseCallback(GLFWwindow *win,double xpos,double ypos){
	if(renderingMode){
		if(callbackGlobals::firstMouseMovement){
			callbackGlobals::lastMouseXpos		= xpos;
			callbackGlobals::lastMouseYpos		= ypos;

			callbackGlobals::firstMouseMovement	= false;
		}

		float Xmargin = xpos - callbackGlobals::lastMouseXpos;
		float Ymargin = callbackGlobals::lastMouseYpos - ypos;
		
		callbackGlobals::lastMouseXpos = xpos;
		callbackGlobals::lastMouseYpos = ypos;


		float yaw	{camera.getYaw() + Xmargin * camera.getMouseSens()};
		float pitch	{camera.getPitch() + Ymargin * camera.getMouseSens()};

		camera.setYaw(yaw);
		camera.setPitch(pitch);
		
		camera.updateFront(Xmargin,Ymargin);
	}
}
#endif