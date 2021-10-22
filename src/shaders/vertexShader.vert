#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normalVector;
layout (location = 2) in vec2 textureCoords;

out vec3 normalVect;
out vec3 fragPos;
out mat4 modelMat;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position	= projection * view * model * vec4(aPos, 1.0);
	fragPos		= vec3(model * vec4(aPos,1.0f));
	normalVect	= mat3(transpose(inverse(model))) * normalize(normalVector);
	modelMat	= model;
	texCoords	= textureCoords;
}