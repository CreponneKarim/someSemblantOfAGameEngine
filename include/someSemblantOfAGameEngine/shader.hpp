#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>

#include <string>
#include <sstream>
#include <fstream>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
	public :
		//	the program ID
		unsigned int programId;
		
		//	constructors
		Shader(const char *vertexPath, const char *fragmentPath){
			std::string 	vertexShaderSource;
			std::string 	fragmentShaderSource;
			std::ifstream	vShaderFile;
			std::ifstream	fShaderFile;

			//	make sure correct exceptions will be raised
			vShaderFile.exceptions(std::ifstream::badbit|std::ifstream::failbit);
			fShaderFile.exceptions(std::ifstream::badbit|std::ifstream::failbit);

			try{
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);

				std::stringstream vShaderStream,fShaderStream;

				//	read the data from the buffer to our streams
				vShaderStream<<vShaderFile.rdbuf();
				fShaderStream<<fShaderFile.rdbuf();

				vShaderFile.close();
				fShaderFile.close();

				vertexShaderSource = vShaderStream.str();
				fragmentShaderSource = fShaderStream.str();

			}catch(std::ifstream::failure){
				std::cout<<"ERROR::SHADER::FILE NOT SUCCESSFULLY READ"<<'\n';
			}

			//	compiling and linking the program stage
			//	creating the shader
			unsigned int vertexShader;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			//	we provide the code of the shader 
			glShaderSource(vertexShader,1,(char**)&vertexShaderSource,NULL);
			//	and we compile it (during runtime so dynamically)
			glCompileShader(vertexShader);

			//	checking the compilation results
			int success;
			char infoLog[512];
			glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
			
			if(!success){
				glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
				std::cout<<"ERROR::SHADER::FAILED TO COMPILE VERTEX SHADER :\n"<<infoLog<<std::endl;
			}

			unsigned int fragmentShader;
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			//	creating the fragment shader
			glShaderSource(fragmentShader,1,(char**)&fragmentShaderSource,NULL);
			//	compiling the fragment shader
			glCompileShader(fragmentShader);

			//	checking the compilation results
			glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
			
			if(!success){
				glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
				std::cout<<"ERROR::SHADER::FAILED TO COMPILE FRAGMENT SHADER :\n"<<infoLog<<std::endl;
			}

			programId = glCreateProgram();
			//	linking the previously created shader to this program
			glAttachShader(programId,vertexShader);
			glAttachShader(programId,fragmentShader);
			glLinkProgram(programId);

			//	checking the linking results
			glGetProgramiv(fragmentShader,GL_LINK_STATUS,&success);
			
			if(!success){
				glGetProgramInfoLog(programId,512,NULL,infoLog);
				std::cout<<"ERROR::SHADER::FAILED TO LINK THE PROGRAM :\n"<<infoLog<<std::endl;
			}

			//	shader cleanup after linkiing it to the program shader
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
		}
		//	to use the shader
		void use(){
			glUseProgram(programId);
		}
		//	uniform functions
		void setBool(const char *name, bool val) const{	
			glUniform1i(glGetUniformLocation(programId,name),val);	
		}
		void setInt(const char *name, int val) const{
			glUniform1i(glGetUniformLocation(programId,name),val);
		}
		void setFloat(const char *name, float val) const{
			glUniform1f(glGetUniformLocation(programId,name),val);
		}
		void setVec3(const char *name, glm::vec3 vect) const{
			glUniform3f(glGetUniformLocation(Shader::programId,name),vect.x,vect.y,vect.z);
		}
		void setVec3(const char *name, float f1, float f2, float f3) const {
			glUniform3f(glGetUniformLocation(Shader::programId,name),f1,f2,f3);
		}
		void setMat4(const char *name, glm::mat4 transformation_matrix)const{
			glUniformMatrix4fv(glGetUniformLocation(programId,name),1,GL_FALSE,glm::value_ptr(transformation_matrix));
		}
		void setCameraVars(glm::mat4 view, glm::mat4 projection, glm::vec3 position){
			Shader::use();
		
			Shader::setMat4("view",view);
			Shader::setMat4("projection",projection);
			Shader::setVec3("position",position);
		}

		void cleanup(){
			glDeleteProgram(programId);
		}

};
#endif