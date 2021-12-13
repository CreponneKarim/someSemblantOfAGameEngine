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
		ImGui::Text((ImGuiPersonal::selectedModel->getModelName()+ " settings").c_str());
		ImGui::EndChild();
	}
}

void ImGuiPersonal::createSideMenu(){
	float sidePannelWidth=200.0f;
	ImGuiWindowFlags rightSidePannelFlags = ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings;
	ImGuiViewport* mainViewport=ImGui::GetMainViewport();

	if(ImGui::BeginViewportSideBar("#rightSidePannel",mainViewport,ImGuiDir_Right,sidePannelWidth,rightSidePannelFlags)){
		
		ImVec2 loadedObjectsDims=ImVec2(0.0f,sidePannelWidth);
		ImGuiWindowFlags loadedObjectsFlags=	ImGuiWindowFlags_NoMove|
							ImGuiWindowFlags_NoSavedSettings;


		// ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize,0.0f);
		// ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0.0f,0.0f));
			
			
		loadedObjectsFlags=	ImGuiWindowFlags_NoScrollWithMouse|
					ImGuiWindowFlags_NoMove|
					ImGuiWindowFlags_MenuBar;
		// if(ImGui::BeginChild(	"#rightSidePannelLoadedObjectsTopBar",
		// 			ImVec2(0.0f,0.0f),
		// 			true,
		// 			loadedObjectsFlags))
		// {
		// 	ImGui::EndChild();	
		// }

		// loadedObjectsFlags=	ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings;
		// if(ImGui::BeginChild(	"#rightSidePannelLoadedObjectsInner",
		// 			ImVec2(0.0f,0.0f),
		// 			true,
		// 			loadedObjectsFlags))
		// {
		// 	ImGui::EndChild();	
		// }
	
		//ImGui::PopStyleVar(2);
		ImGuiPersonal::createObjectsSettings();
		ImGui::End();	
	}
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

#endif