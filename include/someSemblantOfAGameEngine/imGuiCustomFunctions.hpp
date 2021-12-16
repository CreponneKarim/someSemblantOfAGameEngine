#ifndef IMGUICUSTOMFUNCTIONS_HPP
#define IMGUICUSTOMFUNCTIONS_HPP

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <filesystem>

//	included here, because of bad coding :(. Sadly i'm still a scrub lol
#include <include/someSemblantOfAGameEngine/custom_gl_callbacks.hpp>
#include <include/someSemblantOfAGameEngine/sharedGlobalVars.hpp>

#include <libs/imgui.h>
#include <libs/imgui_impl_glfw.h>
#include <libs/imgui_impl_opengl3.h>
#include <libs/imgui_internal.h>
#include <libs/imfilebrowser.h>

namespace ImGuiPersonal{
	inline ImGui::FileBrowser fileDialog;
	//	declared here ro not lose the values after each iteration
	inline Model *selectedModel{nullptr};

	void init(GLFWwindow *window1);
	void createTopBar();
	void createSideMenu();
	void createAll();
	void createObjectsSettings();
	void createAddObjectFromLoaded();
	void createAddObjectFromFile();
}

#endif