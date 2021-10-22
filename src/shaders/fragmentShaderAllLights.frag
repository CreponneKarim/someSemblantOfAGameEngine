#version 330 core

#define NB_POINT_LIGHTS	5

struct Material{
	sampler2D texture_diffuse;
	sampler2D texture_specular;
	sampler2D texture_emission;
	
	float shininess;	
};
struct DirLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	vec3 direction;
};

struct PointLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float kc;//constant
	float kl;//linear
	float kq;//quadratic

	vec3 position;
};

struct SpotLight{
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

uniform DirLight	dirLight;
uniform PointLight	pointLight[NB_POINT_LIGHTS];
uniform SpotLight	spotLight;

uniform Material material;
uniform vec3 viewPos;
uniform bool flashLightIsOn;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 fragPos, vec3 viewDir, vec3 normal);
vec3 calcSpotLight(SpotLight light,vec3 fragPos, vec3 normal);

void main()
{
	vec3 viewDir	= normalize(viewPos - fragPos);
	vec3 normal 	= normalize(normalVect);

	vec3 result=vec3(0.0f);
	result	= calcSpotLight(spotLight,fragPos,normal);
	
	for(int i=0;i<NB_POINT_LIGHTS; i++)
		result += calcPointLight(pointLight[i],fragPos,viewDir,normal);

	FragColor= vec4(result,1.0f);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir){

	//	ambient
	vec3 ambient		= light.ambient * vec3(texture(material.texture_diffuse,texCoords));

	//	diffuse
	float diffuseAmount	= max(dot(normal,normalize(-light.direction)),0.0f);
	vec3 diffuse		= light.diffuse * (diffuseAmount * vec3(texture(material.texture_diffuse,texCoords)));
	
	//	specular
	vec3 reflectedLight	= reflect(normalize(light.direction),normal);
	float specularAmount	= pow(max(dot(reflectedLight,viewDir),0.0f),material.shininess);
	vec3 specular		= light.specular * (specularAmount * vec3(texture(material.texture_specular,texCoords)));

	return (specular + ambient + diffuse);
}

vec3 calcPointLight(PointLight light, vec3 fragPos, vec3 viewDir, vec3 normal){

	//	ambient
	vec3 ambient		= light.ambient * vec3(texture(material.texture_diffuse,texCoords));

	//	diffuse
	vec3 lightVec		= light.position - fragPos;
	vec3 lightDirection	= normalize(lightVec);
	float diffuseAmount	= max(dot(normal,lightDirection),0.0f);
	vec3 diffuse		= light.diffuse * (diffuseAmount * vec3(texture(material.texture_diffuse,texCoords)));
	
	//	specular
	vec3 reflectedLight	= reflect(normalize(-lightDirection),normal);
	float specularAmount	= pow(max(dot(reflectedLight,viewDir),0.0f),material.shininess);
	vec3 specular		= light.specular * (specularAmount * vec3(texture(material.texture_specular,texCoords)));

	//	attenuation calculation
	float distance		=length(lightVec);
	float attenuation	= 1.0/(light.kc + light.kl * distance + light.kq * distance * distance);

	//	we apply attenuation of light
	diffuse*=attenuation;
	specular*=attenuation;

	return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light,vec3 fragPos, vec3 normal){
	vec3 lightVec		= light.position - fragPos;
	vec3 lightDir		= normalize(lightVec);

	float distance		= length(lightVec);
	float attenuation	= 1.0/(light.kc + light.kl * distance + light.kq * distance * distance);

	vec3 ambientLight	= light.ambient * vec3(texture(material.texture_diffuse,texCoords));
	ambientLight *= attenuation;
	
	//	flashlight stuff
	float theta= dot(lightDir,normalize(-light.direction));

	if(theta > light.cutoffAngle){
		//	to get the dim effect on the light edges
		float intensity = (theta - light.cutoffAngle)/(light.innerCutoffAngle - light.cutoffAngle);
		intensity = clamp(intensity,0.0f,1.0f);

		vec3 normal		= normalVect;

		float diff		= max(dot(normal,lightDir),0.0f);
		vec3 diffuseLight	= light.diffuse * (diff * vec3(texture(material.texture_diffuse,texCoords)));
		
		vec3 viewDir		= normalize(viewPos - fragPos);
		vec3 reflectDir		= reflect(-lightDir,normal);
		float spec 		= pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
		vec3 specularLight	= light.specular * (spec  * (vec3(texture(material.texture_specular,texCoords))));
		
		vec3 emissionLight	= vec3(texture(material.texture_emission,texCoords));
		
		diffuseLight *= attenuation;
		specularLight*= attenuation;

		diffuseLight *= intensity;
		specularLight*= intensity;

		return (diffuseLight + ambientLight + specularLight);
	}else{
		return ambientLight;
	}
}