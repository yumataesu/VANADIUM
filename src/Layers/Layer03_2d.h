#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGenBaseLayer.h"

using namespace ofx::Gen;

namespace Layers {
class Layer03_2d : public BaseLayer {
public:
	void setup() override {
	}
	void update(const double delta_time) override {}
	void draw() override {
		ofSetColor(255, 255, 0);
		ofDrawRectangle(200, 200, 300, 300);
	}
	void bang() override {}

private:
};
}