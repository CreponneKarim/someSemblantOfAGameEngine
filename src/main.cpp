#include <src/main.hpp>

int main(int argc, char *argv[]){
	//	opengl init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//	window creation
	GLFWwindow *window1 = glfwCreateWindow(window::width,window::height,"multiple cube rendering",NULL,NULL);
	if(window1==NULL){
		std::cout<<"ERROR::GLFW >> couldn't create window.\n";
		glfwTerminate();
		return -1;
	}

	//	setting different contextes and callbacks
	glfwMakeContextCurrent(window1);	
	glfwSetFramebufferSizeCallback(window1,framebuffer_size_callback);
	glfwSetInputMode(window1,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window1,mouseCallback);

	//	callbacks association
	glfwSetKeyCallback(window1,key_input_callback);
	

	//	glad init
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout<<"ERROR::GLAD >> couldn't load the glad resources.\n";
		glfwTerminate();
		return -1;
	}

	//	some data
	float vertices[] ={
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};	//	36 vertices lol

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};	//	10 of em

	glm::vec3 lightPosition[] = {
		glm::vec3( 0.7f,  0.2f,  2.0f),
		glm::vec3( 2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3( 0.0f,  0.0f, -3.0f),
		glm::vec3( -1.0f,  5.0f, 12.0f)
	};

#ifdef NORMAL_LIGHTING
	Shader shaderProgram("./src/shaders/vertexShader.vert","./src/shaders/fragmentShader.frag");
#endif
#ifdef DIRECTIONAL_LIGHTING
	Shader shaderProgram("./src/shaders/vertexShader.vert","./src/shaders/fragmentShaderDirectionalLight.frag");
#endif
#ifdef SPOT_LIGHTING
	Shader shaderProgram("./src/shaders/vertexShader.vert","./src/shaders/fragmentShaderSpotLight.frag");
#endif
#ifdef ALL_LIGHTING
	Shader shaderProgram("./src/shaders/vertexShader.vert","./src/shaders/fragmentShaderAllLights.frag");
#endif
	Shader lightShaderProgram("./src/shaders/vertexShader.vert","./src/shaders/lightFragmentShader.frag");
	
	shaderProgram.use();

	//	data handling now
	unsigned int VBO,VAO,lightVAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	glGenVertexArrays(1,&lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glVertexAttribPointer(0,3,GL_FLOAT,false,8 * sizeof(float),(void *) 0);
	glEnableVertexAttribArray(0);
	//	texture
	unsigned int texture1,texture2,texture3;
	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D,texture1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	//	load images
	int imgWidth1,imgWidth2,imgHeight1,imgHeight2,nbrChannels1,nbrChannels2;
	unsigned char *image1{stbi_load("./images/container2.png",&imgWidth1,&imgHeight1,&nbrChannels1,0)};
	
	if(image1==NULL){
		std::cout<<"ERROR::STBI>> couldn't load image1.\n";
		glfwTerminate();
		return -1;
	}

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth1,imgHeight1,0,GL_RGBA,GL_UNSIGNED_BYTE,image1);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image1);
	
	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D,texture2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//	reverse image 2
	unsigned char *image2{stbi_load("./images/container2_specular.png",&imgWidth2,&imgHeight2,&nbrChannels2,0)};
	
	if(image2==NULL){
		std::cout<<"ERROR::STBI>> couldn't load image2.\n";
		glfwTerminate();
		return -1;
	}

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth2,imgHeight2,0,GL_RGBA,GL_UNSIGNED_BYTE,image2);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image2);

	glGenTextures(1,&texture3);
	glBindTexture(GL_TEXTURE_2D,texture3);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	

	int height3,width3,nbrChannels3;
	unsigned char *image3{stbi_load("./images/container2_emission.jpg",&width3,&height3,&nbrChannels3,0)};
	if(image3==NULL){
		std::cout<<"ERROR::STBI>> couldn't load image3.\n";
		glfwTerminate();
		return -1;
	}
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width3,height3,0,GL_RGB,GL_UNSIGNED_BYTE,image3);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image3);

	glBindVertexArray(0);

	shaderProgram.setInt("material.texture_diffuse",0);
	shaderProgram.setInt("material.texture_specular",1);
	shaderProgram.setInt("material.texture_emission",2);
	shaderProgram.setFloat("mixAmount",.4f);

	camera=Camera(
		glm::vec3(0.0f,0.0f,3.0f),
		glm::vec3(0.0f,0.0f,-1.0f),
		glm::vec3(0.0f,1.0f,0.0f),
		45.0f,
		window::width/window::height,
		0.1f,
		100.0f
	);

	
	camera.setMouseSens(0.1f);
	camera.setSpeed(5.0f);

	glEnable(GL_DEPTH_TEST);

	double lastTime{glfwGetTime()};

	shaderProgram.use();
	stbi_set_flip_vertically_on_load(true);
	Model modelone(std::filesystem::path("./models/backpack_obj/backpack.obj"));

	while(!glfwWindowShouldClose(window1)){

		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,texture2);
		
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D,texture3);
		
		glm::mat4 model{glm::mat4(1.0f)};
		
		camera.updatePosition();
		
		glm::vec3 	lightColor(1.0f);
		glm::vec3	ambient{0.1f * lightColor};
		glm::vec3	diffuse{0.7f * lightColor};		

		glBindVertexArray(VAO);
		shaderProgram.use();

		//	light stuff

#ifdef ALL_LIGHTING
		//	light params specification
		shaderProgram.setVec3("dirLight.ambient",ambient);
		shaderProgram.setVec3("dirLight.diffuse",diffuse);
		shaderProgram.setVec3("dirLight.specular",lightColor);
		shaderProgram.setVec3("dirLight.direction",lightSourceDirection);

		//	setting additional params to the lights
		for(int i=0;i<nbLights;i++){
			std::string lightNbr{"pointLight[0]."};
			std::string nbr{std::to_string(i)};
			lightNbr.replace(11,nbr.length(),nbr);
			std::string save = lightNbr;

			shaderProgram.setVec3(lightNbr.append("ambient").c_str(),ambient);lightNbr=save;
			shaderProgram.setVec3(lightNbr.append("diffuse").c_str(),diffuse);lightNbr=save;
			shaderProgram.setVec3(lightNbr.append("specular").c_str(),lightColor);lightNbr=save;

			shaderProgram.setFloat(lightNbr.append("kc").c_str(),kc);lightNbr=save;
			shaderProgram.setFloat(lightNbr.append("kl").c_str(),kl);lightNbr=save;
			shaderProgram.setFloat(lightNbr.append("kq").c_str(),kq);lightNbr=save;

			shaderProgram.setVec3(lightNbr.append("position").c_str(),lightPosition[i]);
		};

		//	spotLight params
		std::string lightNbr{"spotLight."};
		std::string save = lightNbr;

		shaderProgram.setVec3(lightNbr.append("ambient").c_str(),ambient);lightNbr=save;
		shaderProgram.setVec3(lightNbr.append("diffuse").c_str(),diffuse);lightNbr=save;
		shaderProgram.setVec3(lightNbr.append("specular").c_str(),lightColor);lightNbr=save;

		shaderProgram.setFloat(lightNbr.append("kc").c_str(),kc);lightNbr=save;
		shaderProgram.setFloat(lightNbr.append("kl").c_str(),kl);lightNbr=save;
		shaderProgram.setFloat(lightNbr.append("kq").c_str(),kq);lightNbr=save;

		shaderProgram.setVec3(lightNbr.append("position").c_str(),camera.getPos());lightNbr=save;
		shaderProgram.setVec3(lightNbr.append("direction").c_str(),camera.getFront());lightNbr=save;

		shaderProgram.setFloat(lightNbr.append("cutoffAngle").c_str(),glm::cos(glm::radians(cutoffAngle)));lightNbr=save;
		shaderProgram.setFloat(lightNbr.append("innerCutoffAngle").c_str(),glm::cos(glm::radians(cutoffAngle-1)));
		
#endif
		model=glm::mat4(1.0f);

		//shaderProgram.setMat4("model",model);
		shaderProgram.setMat4("view",camera.getCamera());
		shaderProgram.setMat4("projection",camera.getProjection());
		shaderProgram.setVec3("viewPos",camera.getPos());

// 		glBindVertexArray(VAO);
		shaderProgram.use();

		//	material stuff
		shaderProgram.setFloat("material.shininess", 64);

// 		//	drawing cubes
// 		for(unsigned int i = 0; i < 10; i++)
// 		{
// 		    glm::mat4 model = glm::mat4(1.0f);
// 		    model = glm::translate(model, cubePositions[i]);
// 		    float angle = 20.0f * i;
// 		    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
// 		    shaderProgram.setMat4("model", model);

// 		    glDrawArrays(GL_TRIANGLES, 0, 36);
// 		}

#ifdef ALL_LIGHTING

		glBindVertexArray(lightVAO);
		lightShaderProgram.use();

		lightShaderProgram.setVec3("lightColor",lightColor);

		//	draw the different lights
		for(int i=0;i<nbLights;i++){	

			glm::mat4 model(1.0f);
			model = glm::translate(model,lightPosition[i]);
			model = glm::scale(model,glm::vec3(0.2f));

			shaderProgram.setMat4("model",model);
			shaderProgram.setMat4("view",camera.getCamera());
			shaderProgram.setMat4("projection",camera.getProjection());
			glDrawArrays(GL_TRIANGLES,0,36);
		}
#endif
		shaderProgram.use();
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model,(float)glm::radians(50.0f * cos(glfwGetTime())),glm::vec3(0.0f,1.0f,0.0f));
		shaderProgram.setMat4("model",model);
		
		modelone.draw(shaderProgram);

		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window1);
	}

	shaderProgram.cleanup();

	glfwDestroyWindow(window1);
	glfwTerminate();
}