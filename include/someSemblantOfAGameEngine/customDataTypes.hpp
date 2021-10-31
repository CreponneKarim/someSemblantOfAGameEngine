#ifndef CUSTOM_DATA_TYPES_HPP
#define CUSTOM_DATA_TYPES_HPP

#include <glm/glm.hpp>
#include <vector>
//	image data retrieving
#include <libs/stb_image.h>
#include <include/someSemblantOfAGameEngine/shader.hpp>
#include <include/someSemblantOfAGameEngine/CommonUsedFunctions.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR '\\' 
#else 
#define PATH_SEPARATOR '/' 
#endif 

struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};
//	texture for opengl stuff
struct Texture{
	unsigned int id;
	std::string type;
	aiString path;	
};
#endif