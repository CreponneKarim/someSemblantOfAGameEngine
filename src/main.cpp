#include <src/main.hpp>

int main(int argc, char *argv[]){
	glfwInits::init();
	GLFWwindow* window1 = glfwInits::initWindow(window::width,window::height,"name");
	if(window1==nullptr)	return -1;

	//	callbacks association
	glfwSetKeyCallback(window1,key_input_callback);
	glfwSetCursorPosCallback(window1,mouseCallback);
	glfwSetFramebufferSizeCallback(window1,framebuffer_size_callback);
	
	if(gladInits::init()==-1)	return -1;

	Shader shaderProgram("./src/shaders/vertexShader.vert","./src/shaders/fragmentShaderAllLights.frag");

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

	glBindVertexArray(0);

	shaderProgram.setInt("material.texture_diffuse",0);
	shaderProgram.setInt("material.texture_specular",1);
	shaderProgram.setInt("material.texture_emission",2);
	shaderProgram.setFloat("mixAmount",.4f);

	
	camera.setMouseSens(0.1f);
	camera.setSpeed(5.0f);

	glEnable(GL_DEPTH_TEST);

	double lastTime{glfwGetTime()};

	shaderProgram.use();
	stbi_set_flip_vertically_on_load(true);

	//	dear ImGui shittery
	ImGuiPersonal::init(window1);

	Model cubeModel(std::filesystem::path("models/cube/w5c7yv4l7sgo.obj"));
	loadedStuff::loadedModels.push_back(cubeModel);
	loadedStuff::loadedLights.push_back(Light(	LightVars::kcDefault,
							LightVars::klDefault,
							LightVars::kqDefault,
							LightVars::ambientDefault,
							LightVars::diffuseDefault,
							LightVars::lightColorDefault,
							&cubeModel)
						);


	while(!glfwWindowShouldClose(window1)){

		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 model{glm::mat4(1.0f)};
		
		camera.updatePosition();
				
		glBindVertexArray(VAO);

		//	camera settings
		lightShaderProgram.setCameraVars(camera.getCamera(),camera.getProjection(),camera.getPos());

		for(int i=0; i<loadedStuff::loadedLights.size();i++){
			//	automatically set the vars for the fragment shader of the lights
			//loadedStuff::loadedLights[i].
			loadedStuff::loadedLights[i].draw(lightShaderProgram,i);
		}

		//shaderProgram.setMat4("model",model);
		shaderProgram.setCameraVars(camera.getCamera(),camera.getProjection(),camera.getPos());

		//	material stuff
		shaderProgram.use();
		//	different shader program
		for(int i=0; i<loadedStuff::loadedLights.size();i++){
			//	sets vars for the fragment shader of models
			loadedStuff::loadedLights[i].setVars(shaderProgram,i);
		}
		
		shaderProgram.setFloat("material.shininess", 64);

		//	render loaded models
		for(int i=0; i<loadedStuff::loadedModels.size();i++)
			loadedStuff::loadedModels[i].draw(shaderProgram);

		glBindVertexArray(0);

		glfwPollEvents();
		
		//	dearImGui stuff
		ImGuiPersonal::createAll();

		glfwSwapBuffers(window1);
	}

	shaderProgram.cleanup();

	glfwDestroyWindow(window1);
	glfwTerminate();
}
