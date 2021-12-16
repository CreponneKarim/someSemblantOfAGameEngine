#ifndef DIFFERENTINITS_CPP
#define DIFFERENTINITS_CPP

#include <include/someSemblantOfAGameEngine/differentInits.hpp>

int glfwInits::init(){
	//	opengl init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	return 0;
}

GLFWwindow* glfwInits::initWindow(int width,int height,std::string name){
	//	window creation
	GLFWwindow *window1 = glfwCreateWindow(width,height,name.c_str(),NULL,NULL);
	if(window1==NULL){
		std::cout<<"ERROR::GLFW >> couldn't create window.\n";
		glfwTerminate();
		return nullptr;
	}

	//	setting different contextes and callbacks
	glfwMakeContextCurrent(window1);	
	glfwSetInputMode(window1,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	return window1;
}

int gladInits::init(){
	//	glad init
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout<<"ERROR::GLAD >> couldn't load the glad resources.\n";
		glfwTerminate();
		return -1;
	}
	return 0;
}

int glInits::init(){


	return 0;
}

#endif