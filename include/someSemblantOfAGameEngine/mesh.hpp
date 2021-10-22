#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <vector>
#include "shader.hpp"
#include "CommonUsedFunctions.hpp"
#include "customDataTypes.hpp"

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
			std::vector<Texture> textures)
		{
			this->vertices	= vertices;
			this->indices	= indices;
			this->textures	= textures;

			setupMesh();
		}
		
		void draw(Shader &shader){
			//	we setup the textures
			shader.use();
			unsigned int diffuseNbr=1;
			unsigned int specularNbr=1;
			for(int i=0; i<Mesh::textures.size();i++){
				Texture tex	= Mesh::textures[i];
				glActiveTexture(GL_TEXTURE0 + tex.id);
				std::string type= tex.type;
				std::string nbr;
				if	(type=="texture_diffuse")
					nbr = std::to_string(diffuseNbr++);
				else if	(type=="texture_specular")
					nbr = std::to_string(specularNbr++);

				shader.setInt(("material." + type ).c_str(),tex.id);
				glBindTexture(GL_TEXTURE_2D, tex.id);
			}
			//	draw mesh
			glBindVertexArray(Mesh::VAO);
			glDrawElements(GL_TRIANGLES,Mesh::indices.size(),GL_UNSIGNED_INT,0);
			glBindVertexArray(0);

			//	reset
			glActiveTexture(GL_TEXTURE0);
		}
	private:
		unsigned int VAO,VBO,EBO;
		void setupMesh(){
			glGenBuffers(1,&(Mesh::VBO));
			glGenBuffers(1,&(Mesh::EBO));
			glGenVertexArrays(1,&(Mesh::VAO));

			glBindVertexArray(Mesh::VAO);
			glBindBuffer(GL_ARRAY_BUFFER,Mesh::VBO);

			glBufferData(GL_ARRAY_BUFFER,Mesh::vertices.size() * sizeof(Vertex),&(Mesh::vertices[0]),GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Mesh::EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,Mesh::indices.size() * sizeof(unsigned int),&(Mesh::indices[0]),GL_STATIC_DRAW);

			//	vertex attributes
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*) 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,normal));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,texCoords));

			glBindVertexArray(0);
		}
};


#endif