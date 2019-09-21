#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGenBaseLayer.h"

using namespace ofx::Gen;

namespace Layers {
class Layer02_2d : public BaseLayer {
public:
	void setup() override {
		shader.load("ofxGen/Layer02_2d/shader");

		quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
		quad.addVertex(ofVec3f(1.0, 1.0, 0.0));
		quad.addTexCoord(ofVec2f(1.0f, 1.0f));
		quad.addVertex(ofVec3f(1.0, -1.0, 0.0));
		quad.addTexCoord(ofVec2f(1.0f, 0.0f));
		quad.addVertex(ofVec3f(-1.0, -1.0, 0.0));
		quad.addTexCoord(ofVec2f(0.0f, 0.0f));
		quad.addVertex(ofVec3f(-1.0, 1.0, 0.0));
		quad.addTexCoord(ofVec2f(0.0f, 1.0f));

	}
	void update(const double delta_time) {
		elapsed_time += delta_time * speed;
	}
	void draw() {
		shader.begin();
		shader.setUniform1f("u_time", elapsed_time);
		quad.draw();
		shader.end();
	}
	void bang() override {
		dst_position = glm::vec2(ofRandom(0, width_), ofRandom(0, height_));
	}

private:
	double elapsed_time;
	glm::vec2 position;
	glm::vec2 dst_position;
	ofxAutoReloadedShader shader;
	ofVboMesh quad;

};
}