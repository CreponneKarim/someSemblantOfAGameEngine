#ifndef OBJECT_HPP
#define OBJECT_HPP

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

	private:
		//	assumming the default cube is always there
		Model& model=loadedStuff::defaultCube;
		glm::mat4 modelMat{glm::mat4(1.0f)};
};

#endif