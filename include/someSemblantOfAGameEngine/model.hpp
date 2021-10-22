#ifndef MODEL_HPP
#define MODEL_HPP

//	GL STUFF
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <vector>
#include "shader.hpp"
#include "CommonUsedFunctions.hpp"
#include "customDataTypes.hpp"
#include "mesh.hpp"

#include <libs/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR '\\' 
#else 
#define PATH_SEPARATOR '/' 
#endif 

class Model{
	public:
		Model(std::string path){
			Model::loadModel(path);
		}
		void draw(Shader &shader){
			for(int i=0;i<Model::meshes.size();i++)
				Model::meshes[i].draw(shader);
		}
	private:
		std::vector<Mesh> meshes;
		std::string directory;
		std::vector<Texture> textures_loaded;

		void loadModel(std::string path){
			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
				std::cout<<"ERROR::ASSIMP//::"<<importer.GetErrorString()<<'\n';
				return;
			}
			Model::directory= path.substr(0,path.find_last_of(PATH_SEPARATOR));
			processNode(scene->mRootNode,scene);
		}
		void processNode(aiNode *node,const aiScene *scene){
			//	we process the mesh for the node
			for(unsigned int i=0;i<node->mNumMeshes;i++){
				aiMesh *mesh	=scene->mMeshes[node->mMeshes[i]];
				Model::meshes.push_back(processMesh(mesh,scene));
			}

			//	we do the same for the children nodes
			//	by doing recursive calls
			for(unsigned int i=0;i<node->mNumChildren;i++){
				processNode(node->mChildren[i],scene);
			}
		}

		Mesh processMesh(aiMesh *mesh,const aiScene *scene){
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<Texture> textures;

			//	retrieving the mesh's vertex data
			for(unsigned int i=0;i<mesh->mNumVertices;i++){
				Vertex vertex;

				glm::vec3 position;
				position.x = mesh->mVertices[i].x;
				position.y = mesh->mVertices[i].y;
				position.z = mesh->mVertices[i].z;
				vertex.position = position;
				if(mesh->HasNormals()){
					glm::vec3 normal;
					normal.x = mesh->mNormals[i].x;
					normal.y = mesh->mNormals[i].y;
					normal.z = mesh->mNormals[i].z;
					vertex.normal = normal;

				}

				if(mesh->mTextureCoords[0]){
					glm::vec2 texCoords;

					texCoords.x = mesh->mTextureCoords[0][i].x;
					texCoords.y = mesh->mTextureCoords[0][i].y;
					vertex.texCoords = texCoords;
				}else{
					vertex.texCoords = glm::vec2(0.0f,0.0f);
				}

				vertices.push_back(vertex);
			}

			for(unsigned int i=0;i<mesh->mNumFaces;i++){
				aiFace face = mesh->mFaces[i];
				for(unsigned int j=0;j<face.mNumIndices;j++)
					indices.push_back(face.mIndices[j]);
			}

			if(mesh->mMaterialIndex>=0){
				aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
				std::vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE,"texture_diffuse");
				textures.insert(textures.end(),diffuseMaps.begin(),diffuseMaps.end());
				std::vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR,"texture_specular");
				textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
			}

			return Mesh(vertices,indices,textures);
		}

		std::vector<Texture> loadMaterialTextures(aiMaterial *mat,aiTextureType type,std::string typeName){
			std::vector<Texture> textures;
			for(unsigned int i=0;i<mat->GetTextureCount(type);i++){
				aiString str;
				mat->GetTexture(type,i,&str);
				Texture texture;
				if(textureExists(str.C_Str())!=-1){
					textures.push_back(Model::textures_loaded[i]);
				}else{
					texture.id =Model::TextureFromFile(str.C_Str(),Model::directory);
					texture.type = typeName;
					texture.path = str;
					textures.push_back(texture);
					Model::textures_loaded.push_back(texture);
				}
			}
			return textures;
		}
		unsigned int TextureFromFile(const char str[],std::string path){
			std::string fullPath= path + PATH_SEPARATOR + str;

			unsigned int texture_{0};
			glGenTextures(1,&texture_);

			int width,height,channels;
			unsigned char *img{stbi_load(fullPath.c_str(),&width,&height,&channels,0)};
			if(img){
				GLenum format;
				if	(channels==1)
					format = GL_RED;
				else if (channels==2)
					format = GL_RG;
				else if	(channels==3)
					format = GL_RGB;
				else if (channels==4)
					format = GL_RGBA;


				glBindTexture(GL_TEXTURE_2D,texture_);

				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,img);
				glGenerateMipmap(GL_TEXTURE_2D);

				stbi_image_free(img);
			}else{
				std::cout<<"customDataTypes::TextureFromFile >> unable to load texture, Path: "<<fullPath<<'\n';
				stbi_image_free(img);
			}

			return texture_;
		}
		int textureExists(const char str[])const{
			for(int i=0;i<Model::textures_loaded.size();i++){
				if(std::strcmp(Model::textures_loaded[i].path.C_Str(),str)==0){
					return i;
				}
			}
			return -1;
		}
};

#endif