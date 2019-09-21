#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGenBaseLayer.h"

using namespace ofx::Gen;

namespace Layers {
class Layer01_2d : public BaseLayer {
public:
	void setup() {
	}
	void update(const double delta_time) {}
	void draw() {
		ofSetColor(255, 255, 0);
		ofDrawRectangle(200, 200, 300, 300);
	}
	void bang() override {}

private:
};
}