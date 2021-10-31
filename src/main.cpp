#include <src/main.hpp>

int main(int argc, char *argv[]){
	glfwInits::init();
	GLFWwindow* window1 = glfwInits::initWindow(window::width,window::height);
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

	
	camera.setMouseSens(0.1f);
	camera.setSpeed(5.0f);

	glEnable(GL_DEPTH_TEST);

	double lastTime{glfwGetTime()};

	shaderProgram.use();
	stbi_set_flip_vertically_on_load(true);

	//	dear ImGui shittery
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();	//			context creation for dear ImGui
	ImGui::StyleColorsDark();//			specifying the style for dear ImGui

	ImGui_ImplGlfw_InitForOpenGL(window1,true);//	setting up window for ImGui
	ImGui_ImplOpenGL3_Init(glslVersion);

	ImGui::FileBrowser fileDialog;
	fileDialog.SetTitle("load model");
	fileDialog.SetTypeFilters({".obj"});

	//Model cubeModel(std::filesystem::path(""));

	while(!glfwWindowShouldClose(window1)){

		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 model{glm::mat4(1.0f)};
		
		camera.updatePosition();
				
		glBindVertexArray(VAO);
		shaderProgram.use();

		// //	setting additional params to the lights
		// for(int i=0;i<nbLights;i++){
		// 	std::string lightNbr{"pointLight[0]."};
		// 	std::string nbr{std::to_string(i)};
		// 	lightNbr.replace(11,nbr.length(),nbr);
		// 	std::string save = lightNbr;

		// 	shaderProgram.setVec3(lightNbr.append("ambient").c_str(),ambient);lightNbr=save;
		// 	shaderProgram.setVec3(lightNbr.append("diffuse").c_str(),diffuse);lightNbr=save;
		// 	shaderProgram.setVec3(lightNbr.append("specular").c_str(),lightColor);lightNbr=save;

		// 	shaderProgram.setFloat(lightNbr.append("kc").c_str(),kc);lightNbr=save;
		// 	shaderProgram.setFloat(lightNbr.append("kl").c_str(),kl);lightNbr=save;
		// 	shaderProgram.setFloat(lightNbr.append("kq").c_str(),kq);lightNbr=save;

		// 	shaderProgram.setVec3(lightNbr.append("position").c_str(),lightPosition[i]);
		// };

		// //	spotLight params
		// std::string lightNbr{"spotLight."};
		// std::string save = lightNbr;

		// shaderProgram.setVec3(lightNbr.append("ambient").c_str(),ambient);lightNbr=save;
		// shaderProgram.setVec3(lightNbr.append("diffuse").c_str(),diffuse);lightNbr=save;
		// shaderProgram.setVec3(lightNbr.append("specular").c_str(),lightColor);lightNbr=save;

		// shaderProgram.setFloat(lightNbr.append("kc").c_str(),kc);lightNbr=save;
		// shaderProgram.setFloat(lightNbr.append("kl").c_str(),kl);lightNbr=save;
		// shaderProgram.setFloat(lightNbr.append("kq").c_str(),kq);lightNbr=save;

		// shaderProgram.setVec3(lightNbr.append("position").c_str(),camera.getPos());lightNbr=save;
		// shaderProgram.setVec3(lightNbr.append("direction").c_str(),camera.getFront());lightNbr=save;

		// shaderProgram.setFloat(lightNbr.append("cutoffAngle").c_str(),glm::cos(glm::radians(cutoffAngle)));lightNbr=save;
		// shaderProgram.setFloat(lightNbr.append("innerCutoffAngle").c_str(),glm::cos(glm::radians(cutoffAngle-1)));
		

		//shaderProgram.setMat4("model",model);
		shaderProgram.setMat4("view",camera.getCamera());
		shaderProgram.setMat4("projection",camera.getProjection());
		shaderProgram.setVec3("viewPos",camera.getPos());

		//	material stuff
		shaderProgram.setFloat("material.shininess", 64);

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

		//	render loaded models
		for(int i=0; i<loadedModels.size();i++)
			if(!loadedModels[i].getIsALight())loadedModels[i].draw(shaderProgram);

		for(int i=0; i<loadedLights.size();i++){
			//	sets vars for the fragment shader of models
			loadedLights[i].setVars(shaderProgram,i);
			//	automatically set the vars for the fragment shader of the lights
			loadedLights[i].draw(lightShaderProgram,i);
		}

		glBindVertexArray(0);

		glfwPollEvents();
		//	dearImGui stuff
		//	create new frame
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		float sidePannelWidth=200.0f;
		ImGuiWindowFlags rightSidePannelFlags = ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings;
		ImGuiViewport* mainViewport=ImGui::GetMainViewport();

		if(ImGui::BeginViewportSideBar("#rightSidePannel",mainViewport,ImGuiDir_Right,sidePannelWidth,rightSidePannelFlags)){
			for(int i=0;i<loadedModels.size();i++){
				ImGui::Text(loadedModels[i].getModelName().c_str());
			}
			ImGui::End();	
		}

		if(ImGui::BeginMainMenuBar()){
			if(ImGui::BeginMenu("File")){
				if(ImGui::MenuItem("load model")){
					fileDialog.Open();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
		//	displays the dialog when clicked
		
		fileDialog.Display();

		if(fileDialog.HasSelected()){
			std::string slectedModelPath=fileDialog.GetSelected().string();
			std::cout<<"slected file path: "<<slectedModelPath<<'\n';
			//	pas in the default model matrix lol
			loadedModels.push_back(Model(slectedModelPath,model));
			fileDialog.ClearSelected();
		}

		//		renderWindow
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window1);
		

	}

	shaderProgram.cleanup();

	glfwDestroyWindow(window1);
	glfwTerminate();
}