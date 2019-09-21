#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGen.h"
#include "ofxSSAO.h"
#include "ofxDeferredLighting.h"
#include "layers/inc.h"

class ofApp : public ofBaseApp 
{
public:
	void setup();
	void update();
	void draw();
	void gui(ofEventArgs& e);
	void keyPressed(int key);
	void keyReleased(int key);
	void initGuiSkin();
		
	ofxImGui::Gui imgui;
	ImFont* Xlarge_font;
	ImFont* large_font;
	ImFont* midium_font;

	ofFbo final_out_fbo;
	std::unique_ptr<ofxGen> gen_manager;
	std::unique_ptr<ofx::DeferredLighting> ofxdeferredlighting;

};
