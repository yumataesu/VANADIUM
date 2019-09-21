#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGenBaseLayer.h"

using namespace ofx::Gen;

namespace Layers {
class Layer01_2d : public BaseLayer {
public:
	void setup() {
		parameter_group_.add(position.set("Position", glm::vec2(100.f), glm::vec2(0.f), glm::vec2(width_, height_)));
	}
	void update(const double delta_time) {
		elapsed_time += delta_time * speed;
	}
	void draw() {
		ofSetColor(main_col.get());
		ofDrawCircle(position.get().x, position.get().y, 50 + 50 * sin(elapsed_time));
	}

	void bang() override {

	}

private:
	ofParameter<glm::vec2> position;
	double elapsed_time;
};
}