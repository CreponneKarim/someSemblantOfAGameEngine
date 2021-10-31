#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <include/someSemblantOfAGameEngine/shader.hpp>
#include <include/someSemblantOfAGameEngine/model.hpp>
#include <include/someSemblantOfAGameEngine/sharedGlobalVars.hpp>

class Light{
	public:
		Light(	float kc,
			float kl,
			float kq,
			float ambient,
			float diffuse,
			glm::vec3 lightColor,
			Model *model);

		//	create a light with the default values
		Light();

		void setVars(Shader &shader_, int lightIndex);
		void draw(Shader &shader, int lightIndex);

		float getKc();
		float getkq();
		float getkl();
		float getAmbient();
		float getDiffuse();
		
		glm::vec3 getLightColor();

		void setKc(float kc);
		void setKq(float kq);
		void setKl(float kl);
		
		void setLightIndex(int lightIndex);

		void setAmbient(float ambientDeg);
		void setDiffuse(float diffuseDeg);
		void setLightColor(glm::vec3 lightColor);
	private:
		float	kc{LightVars::kcDefault},
			kl{LightVars::klDefault},
			kq{LightVars::kqDefault},
			ambient{LightVars::ambientDefault},
			diffuse{LightVars::diffuseDefault};
		int lightIndex{0};
		glm::vec3 lightColor{LightVars::lightColorDefault};

		Model *model;
};
#endif