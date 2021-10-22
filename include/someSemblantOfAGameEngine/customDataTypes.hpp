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


class Material
{	
	private:
		std::string name;

		glm::vec3 *ka{nullptr};	//	ambient
		glm::vec3 *kd{nullptr};	//	diffuse
		glm::vec3 *ks{nullptr};	//	specular
		glm::vec3 *ke{nullptr};	//	emissive	
		glm::vec3 *tf{nullptr};	//	transmission filter

		float ns;//	aka shininess
		float d;
		float ni;
	public :
		
		Material();
		~Material();

		//	getters and setters shittery
		std::string getName();
		glm::vec3* getKa();
		glm::vec3* getKd();
		glm::vec3* getKs();
		glm::vec3* getKe();
		glm::vec3* getTf();
		float getNs();
		float getD();
		float getNi();

		void setName(std::string name);
		void setKa(glm::vec3* vec);
		void setKd(glm::vec3* vec);
		void setKs(glm::vec3* vec);
		void setKe(glm::vec3* vec);
		void setTf(glm::vec3* vec);
		void setNs(float f);
		void setD(float f);
		void setNi(float f);

};

class ObjectModel{
	private:
		std::vector<unsigned int> *elementsBufferObject;
		std::string name;

		unsigned int EBO{0};
	public :
		ObjectModel(std::string name);
		~ObjectModel();

		void setData(std::vector<float> *e);
		void setElementBufferObject(std::vector<unsigned int> *e);
		void setName(std::string name);

		std::string getName();
		unsigned int getEBO();
		std::vector<unsigned int>* getElementsBufferObject();

		void loadElementsBufferObjectToMem();
		void drawObj();

};
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