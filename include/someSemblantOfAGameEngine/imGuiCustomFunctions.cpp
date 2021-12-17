#ifndef IMGUICUSTOMFUNCTIONS_CPP
#define IMGUICUSTOMFUNCTIONS_CPP

#include <include/someSemblantOfAGameEngine/imGuiCustomFunctions.hpp>

void ImGuiPersonal::init(GLFWwindow *window1){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();	//			context creation for dear ImGui
	ImGui::StyleColorsDark();//			specifying the style for dear ImGui

	ImGui_ImplGlfw_InitForOpenGL(window1,true);//	setting up window for ImGui
	ImGui_ImplOpenGL3_Init(glslVersion);

	fileDialog.SetTitle("load model");
	fileDialog.SetTypeFilters({".obj"});
}

void ImGuiPersonal::createTopBar(){

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
	glm::mat4 model(1.0f);

	if(fileDialog.HasSelected()){
		std::string slectedModelPath=fileDialog.GetSelected().string();
		std::cout<<"slected file path: "<<slectedModelPath<<'\n';
		//	pas in the default model matrix lol
		loadedStuff::loadedModels.push_back(Model(slectedModelPath,model));
		fileDialog.ClearSelected();
	}

}

void ImGuiPersonal::createObjectsSettings(){

	ImVec2 selectedObjectsDims=ImVec2(0.0f,0.0f);
	ImGuiWindowFlags selectedObjectFlags=ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings;
	if(ImGui::BeginChild(	"#SelectedObjectOptions",
				selectedObjectsDims,
				false,
				selectedObjectFlags)
				&& selectedModel!=nullptr)
	{
		ImGui::Text("%s",(ImGuiPersonal::selectedModel->getModelName()+ " settings").c_str());
	}
	ImGui::EndChild();
}

void ImGuiPersonal::createSideMenu(){
	/*
		static variables
	*/
	static bool button_createObjectFromLoaded	=false;
	static bool button_createObjectFromFile		=false;

	float sidePannelWidth=200.0f;

	ImGuiWindowFlags rightSidePannelFlags = ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings;
	ImGuiViewport* mainViewport=ImGui::GetMainViewport();
	// ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0.0f,0.0f));
	
	//	to remove padding between child windows
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize,0.0f);		
	
	if(ImGui::BeginViewportSideBar("#rightSidePannel",mainViewport,ImGuiDir_Right,sidePannelWidth,rightSidePannelFlags)){
		
		ImVec2 loadedObjectsDims=ImVec2(0.0f,sidePannelWidth);
		ImGuiWindowFlags loadedObjectsFlags=	ImGuiWindowFlags_NoMove|
							ImGuiWindowFlags_NoSavedSettings;


			
		loadedObjectsFlags=	ImGuiWindowFlags_NoScrollWithMouse|
					ImGuiWindowFlags_NoMove;

		ImVec2 menubarDims(0.0f,0.0f);
		if(ImGui::BeginChild(	"#rightSidePannelLoadedObjectsTopBar",
					menubarDims,
					true,
					loadedObjectsFlags))
		{
			if(ImGui::Button("+ object from loaded",ImVec2(-1.0f,0.0f))){
				button_createObjectFromLoaded=!button_createObjectFromLoaded;
			}
			if(ImGui::Button("+ object from file",ImVec2(-1.0f,0.0f))){
				fileDialog.Open();
				button_createObjectFromFile=!button_createObjectFromFile;
			}

			if(button_createObjectFromLoaded)	ImGuiPersonal::createAddObjectFromLoaded();
			if(button_createObjectFromFile)		ImGuiPersonal::createAddObjectFromFile();
		}ImGui::EndChild();

		loadedObjectsFlags=	ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings;
		ImVec2 objectsMenuDims(0.0f,200.0f);
		if(ImGui::BeginChild(	"#rightSidePannelLoadedObjectsInner",
					ImVec2(0.0f,200.0f),
					true,
					loadedObjectsFlags))
		{	
		}ImGui::EndChild();
	
		ImGuiPersonal::createObjectsSettings();
	}ImGui::End();
	ImGui::PopStyleVar(1);
	
}

void ImGuiPersonal::createAll(){

	//	create new frame
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGuiPersonal::createSideMenu();
	ImGuiPersonal::createTopBar();

	//		renderWindow
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
}

void ImGuiPersonal::createAddObjectFromLoaded(){
	int loadedModelsSize=loadedStuff::loadedModels.size();
	if(loadedModelsSize==0)	return;

	ImVec2 listSize(-1.0f,0.0f);
	
	ImGui::SetNextItemWidth(100.0f);
	ImGui::ListBoxHeader("##",listSize);
	int i=0;
	for(Model item : loadedStuff::loadedModels){
		bool selected =false;
		ImVec2 itemSize(0.0f,0.0f);
		ImGuiSelectableFlags flags=	ImGuiSelectableFlags_SelectOnClick;
		std::string itemName=item.getModelName();
		
		ImGui::SetNextItemWidth(100.0f);
		if(ImGui::Selectable(itemName.c_str(),&selected,flags,itemSize)){
			loadedStuff::loadedObjects.push_back	(	Object(
									loadedStuff::loadedModels[i]
									)
								);
		}
		i++;
	}
	ImGui::ListBoxFooter();
}

void ImGuiPersonal::createAddObjectFromFile(){
	fileDialog.Display();
	glm::mat4 model(1.0f);

	if(fileDialog.HasSelected()){
		std::string slectedModelPath=fileDialog.GetSelected().string();
		std::cout<<"slected file path: "<<slectedModelPath<<'\n';
		loadedStuff::loadedModels.push_back(Model(slectedModelPath,model));

		//	create the appropriate object
		loadedStuff::loadedObjects.push_back	(	Object(
								loadedStuff::loadedModels.back()
								)
							);

		fileDialog.ClearSelected();
	}

}

void ImGuiPersonal::createObjectSettings(){
	static bool isOpened=false;
	if(ImGui::Begin("new object settings",&isOpened)){
		ImGui::End();
	}
}

void ImGuiPersonal::createObjectsList(){
	if(ImGui::BeginChild("##ObjectListChildWindow")){
		ImGui::
	}
}
#endif