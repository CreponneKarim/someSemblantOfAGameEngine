#version 330 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	
	float shininess;	
};
struct Light{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 pos;
	float kc;//constant
	float kl;//linear
	float kq;//quadratic
};

in vec3 normalVect;
in vec3 fragPos;
in mat4 modelMat;
in vec2 texCoords;

out vec4 FragColor;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main()
{
    	
	vec3 ambientLight	= light.ambient * vec3(texture(material.diffuse,texCoords));

	vec3 normal		= mat3(transpose(inverse(modelMat))) * normalize(normalVect);
	vec3 lightVec		= light.pos- fragPos;
	vec3 lightDir		= normalize(lightVec);

	float diff		= max(dot(normal,lightDir),0.0f);
	vec3 diffuseLight	= light.diffuse * (diff * vec3(texture(material.diffuse,texCoords)));
	
	vec3 viewDir		= normalize(viewPos - fragPos);
	vec3 reflectDir		= reflect(-lightDir,normal);
	float spec 		= pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specularLight	= light.specular * (spec  * (vec3(texture(material.specular,texCoords))));
	
	vec3 emissionLight	= vec3(texture(material.emission,texCoords));

	float distance		= length(lightVec);
	float attenuation	= 1.0/(light.kc + light.kl * distance + light.kq * distance * distance);

	//(vec3(texture(material.specular,texCoords))==vec3(0.0f)?specularLight + emissionLight + ambientLight + diffuseLight:specularLight + ambientLight + diffuseLight);
	diffuseLight *= attenuation;
	specularLight*= attenuation;
	ambientLight *= attenuation;
	vec3 result		= specularLight + diffuseLight + ambientLight;

	FragColor = vec4(result,1.0f);
}