#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

#include <glm/glm.hpp>
#include <include/someSemblantOfAGameEngine/model.hpp>
#include <include/someSemblantOfAGameEngine/sharedGlobalVars.hpp>

/**
 * @brief represents one single loaded object to the scene
 *
 * drawn o the scene
 * has its own model matrix ;D
 */
class Object{
	public:
		Object(Model& model);
		Object(Model& model,const glm::mat4 modelMat);

		std::string getName();

	private:
		std::string name;
		//	assumming the default cube is always there
		Model* model=nullptr;
		glm::mat4 modelMat{glm::mat4(1.0f)};
};

#endif