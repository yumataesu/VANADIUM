#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 5);
	settings.setSize(1280, 720);
	settings.decorated = true;
	std::shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> guiApp(new ofApp);

	ofRunApp(guiWindow, guiApp);
	ofRunMainLoop();

}
