#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGenBaseLayer.h"

using namespace ofx::Gen;

namespace Layers {
class Layer01_2d : public BaseLayer {
public:
	void setup() {
		parameter_group_.add(num.set("Num", 0.5, 0, 1.0));
		parameter_group_.add(grid.set("Grid", glm::vec2(10), glm::vec2(1), glm::vec2(50)));
		shader.load("ofxGen/Layer01_2d/shader");
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
		shader.setUniform1f("num", num);
		shader.setUniform2f("u_grid", grid.get().x, grid.get().y);
		quad.draw();
		shader.end();
	}

	void bang() override {

	}

private:
	ofParameter<float> num;
	ofParameter<float> up_sp = 1.0f;
	ofParameter<glm::vec2> grid;
	double elapsed_time;

	ofVboMesh quad;
	ofxAutoReloadedShader shader;
};
}