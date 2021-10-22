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

	float kc;//constant
	float kl;//linear
	float kq;//quadratic

	vec3 position;
	vec3 direction;
	float cutoffAngle;
	float innerCutoffAngle;
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
    	vec3 lightVec		= light.position - fragPos;
	vec3 lightDir		= normalize(lightVec);

	float distance		= length(lightVec);
	float attenuation	= 1.0/(light.kc + light.kl * distance + light.kq * distance * distance);

	vec3 ambientLight	= light.ambient * vec3(texture(material.diffuse,texCoords));
	ambientLight *= attenuation;
	
	//	flashlight stuff
	float theta= dot(lightDir,normalize(-light.direction));

	vec3 result;
	if(theta > light.cutoffAngle){
		//	to get the dim effect on the light edges
		float intensity = (theta - light.cutoffAngle)/(light.innerCutoffAngle - light.cutoffAngle);
		intensity = clamp(intensity,0.0f,1.0f);

		vec3 normal		= normalVect;

		float diff		= max(dot(normal,lightDir),0.0f);
		vec3 diffuseLight	= light.diffuse * (diff * vec3(texture(material.diffuse,texCoords)));
		
		vec3 viewDir		= normalize(viewPos - fragPos);
		vec3 reflectDir		= reflect(-lightDir,normal);
		float spec 		= pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
		vec3 specularLight	= light.specular * (spec  * (vec3(texture(material.specular,texCoords))));
		
		vec3 emissionLight	= vec3(texture(material.emission,texCoords));
		
		diffuseLight *= attenuation;
		specularLight*= attenuation;

		diffuseLight *= intensity;
		specularLight*= intensity;

		FragColor = vec4(diffuseLight + ambientLight + specularLight,1.0f);
	}else{
		FragColor = vec4(ambientLight,1.0f);
	}
}