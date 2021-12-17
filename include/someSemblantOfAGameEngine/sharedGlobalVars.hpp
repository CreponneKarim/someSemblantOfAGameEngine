#ifndef SHAREDGLOBALVARS_HPP
#define SHAREDGLOBALVARS_HPP

#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

namespace LightVars{
	inline float kcDefault			{1.0f};
	inline float klDefault			{0.14f};
	inline float kqDefault			{0.07f};

	inline float klMax			{0.7f};
	inline float kqMax			{1.8f};

	inline float klMin			{0.0014f};
	inline float kqMin			{0.000007f};

	inline glm::vec3 lightColorDefault	(1.0f);
	inline float ambientDefault		{0.07f};
	inline float diffuseDefault		{0.1f};

	inline float AmbientMax			{1.0f};
	inline float diffuseMax			{1.0f};

	inline float ambientMin			{0.01f};
	inline float diffuseMin			{0.01f};
};

namespace window{
	inline const int width{800},height{800};
};

class Model;
class Light;

#include <include/someSemblantOfAGameEngine/light.hpp>
#include <include/someSemblantOfAGameEngine/model.hpp>

namespace loadedStuff{
	inline Model defaultCube(std::filesystem::path("models/cube/w5c7yv4l7sgo.obj"));
	inline std::vector<Model> loadedModels;
	inline std::vector<Light> loadedLights;
}

#endif