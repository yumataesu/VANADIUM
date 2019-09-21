#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGenBaseLayer.h"

using namespace ofx::Gen;

namespace Layers {
class Layer02_2d : public BaseLayer {
public:
	void setup() override {
	}
	void update(const double delta_time) {
		elapsed_time += delta_time * speed;
		position.x = ofLerp(position.x, dst_position.x, 0.1);
		position.y = ofLerp(position.y, dst_position.y, 0.1);
	}
	void draw() {
		ofSetColor(main_col.get());
		ofDrawCircle(position.x, position.y, 50 + 50 * sin(elapsed_time));
	}
	void bang() override {
		dst_position = glm::vec2(ofRandom(0, width_), ofRandom(0, height_));
	}

private:
	double elapsed_time;
	glm::vec2 position;
	glm::vec2 dst_position;

};
}