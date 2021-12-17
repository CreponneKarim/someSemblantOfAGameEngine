#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <vector>
#include <include/someSemblantOfAGameEngine/shader.hpp>
#include <include/someSemblantOfAGameEngine/CommonUsedFunctions.hpp>
#include <include/someSemblantOfAGameEngine/customDataTypes.hpp>

#include <libs/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh{
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
	
		Mesh(	std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures);
		void draw(Shader &shader);
	private:
		unsigned int VAO,VBO,EBO;
		void setupMesh();
};


#endif