#ifndef MAIN_HPP
#define MAIN_HPP

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

//	image data retrieving
#include <libs/stb_image.h>

//	custom headers
#include <include/someSemblantOfAGameEngine/customDataTypes.hpp>
#include <include/someSemblantOfAGameEngine/camera.hpp>
#include <include/someSemblantOfAGameEngine/mesh.hpp>
#include <include/someSemblantOfAGameEngine/model.hpp>
#include <include/someSemblantOfAGameEngine/shader.hpp>


#define ALL_LIGHTING

inline int cameraNumber;
inline constexpr unsigned short cameraCount{1};
inline Camera camera;
inline float deltaTime{0};
#ifdef NORMAL_LIGHTING
inline glm::vec3 lightSourcePos(1.2f, 1.0f, 2.0f);
#endif
#ifdef DIRECTIONAL_LIGHTING
inline glm::vec3 lightSourceDirection(-0.2f, -1.0f, -0.3f);
#endif
#ifdef SPOT_LIGHTING
inline float cutoffAngle{12.5f};
#endif
#ifdef ALL_LIGHTING
inline float cutoffAngle{12.5f};
inline glm::vec3 lightSourceDirection(-0.2f, -1.0f, -0.3f);
inline int nbLights{5};
#endif

inline float kc{1.0f},kl{0.14f},kq{0.07f};

namespace window{
	inline const int width{800},height{800};
};

//	included here, because of bad coding :(. Sadly i'm still a scrub lol
#include <include/someSemblantOfAGameEngine/custom_gl_callbacks.hpp>

#endif