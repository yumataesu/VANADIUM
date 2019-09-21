#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxGenBaseLayer.h"

using namespace ofx::Gen;

namespace Layers {
class Layer03_2d : public BaseLayer {
public:
	void setup() override {
		shader.load("ofxGen/Layer03_2d/shader");

		quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
		quad.addVertex(ofVec3f(1.0, 1.0, 0.0));
		quad.addTexCoord(ofVec2f(1.0f, 1.0f));
		quad.addVertex(ofVec3f(1.0, -1.0, 0.0));
		quad.addTexCoord(ofVec2f(1.0f, 0.0f));
		quad.addVertex(ofVec3f(-1.0, -1.0, 0.0));
		quad.addTexCoord(ofVec2f(0.0f, 0.0f));
		quad.addVertex(ofVec3f(-1.0, 1.0, 0.0));
		quad.addTexCoord(ofVec2f(0.0f, 1.0f));

		//parameter_group_.add(up_sp);
		parameter_group_.add(speed.set("Spd", 0.5, 0.1, 10.f));
		parameter_group_.add(point.set("Point", glm::vec2(0., 0.), glm::vec2(0., 0.), glm::vec2(width_, height_)));
	}
	void update(const double delta_time) override {
		elapsed_time += delta_time * speed;
	}
	void draw() override {
		shader.begin();
		shader.setUniform1f("u_alpha", alpha_);
		shader.setUniform1f("u_time", elapsed_time);
		shader.setUniform2f("u_resolution", width_, height_);
		shader.setUniform2f("u_point", point);
		quad.draw();
		shader.end();
	}
	void bang() override {}

private:
	ofParameter<glm::vec2> point;
	ofParameter<float> up_sp = 1.0f;
	ofParameter<float> length_z;

	ofxAutoReloadedShader shader;
	ofVboMesh quad;
	float elapsed_time;

};
}