#ifndef LIGHT_CPP
#define LIGHT_CPP

#include <include/someSemblantOfAGameEngine/light.hpp>

Light::Light(	float kc,
		float kl,
		float kq,
		float ambient,
		float diffuse,
		glm::vec3 lightColor,
		Model *model){
	Light::kc = kc;
	Light::kq = kq;
	Light::kl = kl;

	Light::ambient	= ambient;
	Light::diffuse	= diffuse;
	Light::lightColor = lightColor;

	if(model!=nullptr)	Light::model=model;
}
Light::Light(){}
void Light::setVars(Shader &shader_, int lightIndex){
	std::string lightNbr{"pointLight[0]."};
	std::string nbr{std::to_string(lightIndex)};
	lightNbr.replace(11,nbr.length(),nbr);
	std::string save = lightNbr;

	shader_.setVec3(lightNbr.append("ambient").c_str(),Light::ambient * Light::lightColor);lightNbr=save;
	shader_.setVec3(lightNbr.append("diffuse").c_str(),Light::diffuse * Light::lightColor);lightNbr=save;
	shader_.setVec3(lightNbr.append("specular").c_str(),Light::lightColor * Light::lightColor);lightNbr=save;

	shader_.setFloat(lightNbr.append("kc").c_str(),Light::kc);lightNbr=save;
	shader_.setFloat(lightNbr.append("kl").c_str(),Light::kl);lightNbr=save;
	shader_.setFloat(lightNbr.append("kq").c_str(),Light::kq);lightNbr=save;

	//	for light shader
	shader_.setFloat(lightNbr.append("lightColor").c_str(),Light::kq);lightNbr=save;
}
void Light::draw(Shader &shader, int lightIndex){
	shader.use();
	setVars(shader,lightIndex);
	shader.setVec3("lightColor",Light::lightColor);
	if(Light::model!=nullptr)	Light::model->draw(shader);
}
float Light::getKc(){
	return Light::kc;
}
float Light::getkq(){
	return Light::kq;
}
float Light::getkl(){
	return Light::kl;
}

float Light::getAmbient(){
	return Light::ambient;
}
float Light::getDiffuse(){
	return Light::diffuse;
}
glm::vec3 Light::getLightColor(){
	return Light::lightColor;
}
void Light::setKc(float kc){
	Light::kc = kc;
}
void Light::setKq(float kq){
	Light::kq = kq;
}
void Light::setKl(float kl){
	Light::kl = kl;
}
void Light::setLightIndex(int lightIndex){
	Light::lightIndex = lightIndex;
}

void Light::setAmbient(float ambient){
	Light::ambient = ambient;
}
void Light::setDiffuse(float diffuse){
	Light::diffuse = diffuse;
}
void Light::setLightColor(glm::vec3 lightColor){
	Light::lightColor = lightColor;
}

#endif