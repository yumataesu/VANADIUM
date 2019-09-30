#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	initGuiSkin();
	ofSetVerticalSync(false);
	ofSetFrameRate(30);

	ofFbo::Settings settings;
	settings.width = 1280;
	settings.height = 720;
	settings.useDepth = true;
	settings.useStencil = true;
	settings.depthStencilAsTexture = true;
	settings.textureTarget = GL_TEXTURE_2D;
	settings.internalformat = GL_RGBA32F;
	settings.wrapModeVertical = GL_REPEAT;
	settings.wrapModeHorizontal = GL_REPEAT;
	settings.minFilter = GL_NEAREST;
	settings.maxFilter = GL_NEAREST;

	ofxGen::Manager::registration<Layers::Layer01_2d>("Layer01_2d");
	ofxGen::Manager::registration<Layers::Layer02_2d>("Layer02_2d");
	ofxGen::Manager::registration<Layers::Layer03_2d>("Layer03_2d");

	ofxGen::Manager::registration<Layers::Layer01_3d>("Layer01_3d");
	ofxGen::Manager::registration<Layers::Layer02_3d>("Layer02_3d");
	ofxGen::Manager::registration<Layers::Layer03_3d>("Layer03_3d");
	ofxGen::Manager::registration<Layers::Layer04_3d>("Layer04_3d");
	ofxGen::Manager::registration<Layers::Layer05_3d>("Layer05_3d");
	ofxGen::Manager::registration<Layers::Layer06_3d>("Layer06_3d");

	ofDisableArbTex();
	final_out_fbo.allocate(settings.width, settings.height, GL_RGBA);
	gen_manager = std::make_unique<ofxGen>(8, settings, "Main");
	ofxGen::setupBackyard();
	ofxdeferredlighting = std::make_unique<ofx::DeferredLighting>(settings.width, settings.height);
	ofAddListener(ofEvents().draw, this, &ofApp::gui, OF_EVENT_ORDER_AFTER_APP);
}

//--------------------------------------------------------------
void ofApp::update() {
	gen_manager->update(ofGetLastFrameTime());
	ofxdeferredlighting->process(
		gen_manager->get3DTexture(0),
		gen_manager->get3DTexture(1),
		gen_manager->get3DTexture(2),
		gen_manager->getViewMatrix(),
		gen_manager->getProjectionMatrix(),
		gen_manager->getCameraPosition()
	);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_MAX);
	final_out_fbo.begin();
	ofClear(0);
	ofxdeferredlighting->getTexture().draw(0, 0);
	gen_manager->get2DTexture().draw(0, 0);
	final_out_fbo.end();
	glDisable(GL_BLEND);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(20);
	final_out_fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::gui(ofEventArgs& e) {

	imgui.begin();

	gen_manager->drawSlotGui();
	gen_manager->draw2dGui();
	gen_manager->draw3dGui();
	ofxGen::drawUtilGui();
	ofxGen::drawBackyardGui();

	ofxdeferredlighting->drawGui();

	ofxImGui::Begin("Final");
	ImVec2 window_size = ImGui::GetWindowSize();
	float offset = 4.0f;
	ImVec2 thumbnail_size = ImVec2(window_size.x - offset, (window_size.x - offset) * 9 / 16);
	ImGui::ImageButton((ImTextureID)(uintptr_t)final_out_fbo.getTexture().getTextureData().textureID, thumbnail_size, ImVec2(0, 0), ImVec2(1, 1), 0);
	ofxImGui::End();

	ImGui::Begin("Style Editor");
	ImGui::ShowStyleEditor();
	ImGui::End();

	imgui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

void ofApp::initGuiSkin() {

	imgui.setup();
	ImGuiIO& io = ImGui::GetIO();
	midium_font = io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/Helvetica-Regular.ttf").c_str(), 12);
	large_font = io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/Helvetica-Regular.ttf").c_str(), 24);
	Xlarge_font = io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/Helvetica-Regular.ttf").c_str(), 32);


	auto& style = ImGui::GetStyle();
	style.FrameRounding = 0.f;
	style.WindowPadding = ImVec2(8.f, 8.f);
	style.PopupRounding = 0.f;
	style.FramePadding = ImVec2(2.f, 6.f);
	style.ItemSpacing = ImVec2(8.f, 4.f);
	style.GrabMinSize = 8.f;
	style.ScrollbarSize = 8.f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.05f, 0.08f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.27f, 0.62f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.46f, 0.62f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.83f, 1.00f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 0.99f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.58f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.09f, 0.09f, 0.13f, 0.77f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.09f, 0.09f, 0.09f, 0.77f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.36f, 0.37f, 0.39f, 0.77f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.04f, 0.04f, 0.04f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.04f, 0.04f, 0.04f, 0.86f);
	colors[ImGuiCol_TabActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.86f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}