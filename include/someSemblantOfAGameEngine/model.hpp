#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

//	GL STUFF
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <include/someSemblantOfAGameEngine/shader.hpp>
#include <include/someSemblantOfAGameEngine/CommonUsedFunctions.hpp>
#include <include/someSemblantOfAGameEngine/customDataTypes.hpp>
#include <include/someSemblantOfAGameEngine/mesh.hpp>

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
		glm::mat4 model=glm::mat4(1.0f);	//	for scaling, rotating and translating
		//glm::mat4 position;			//	for future shit lol

		Model(std::string path);
		Model(std::string path,glm::mat4 model);
		void draw(Shader &shader);
		bool getIsALight();
		void switchLight();
		std::string getModelName();
	private:
		std::vector<Mesh> meshes;
		std::string directory;
		std::string modelName;
		std::vector<Texture> textures_loaded;
		bool isALight{false};

		void loadModel(std::string path);
		void processNode(aiNode *node,const aiScene *scene);
		Mesh processMesh(aiMesh *mesh,const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial *mat,aiTextureType type,std::string typeName);
		unsigned int TextureFromFile(const char str[],std::string path);
		int textureExists(const char str[])const;
};

#endif