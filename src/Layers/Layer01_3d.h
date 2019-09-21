#pragma once
#include "ofMain.h"
#include "ofxGen.h"
#include "ofxAutoReloadedShader.h"
using namespace ofx::Gen;

namespace Layers {
class Layer01_3d : public BaseLayer
{
public:
	void setup() override {
		parameter_group_.add(position.set("Pos", glm::vec3(0.f), glm::vec3(-100.f), glm::vec3(100.f)));
		parameter_group_.add(scale.set("Scl", glm::vec3(1.f), glm::vec3(0.f), glm::vec3(10.f)));

		positions.reserve(Num);
		float r = 500.f;
		for (int i = 0; i < Num; ++i) {
			positions.emplace_back(glm::vec3(ofRandom(-r, r), ofRandom(-r, r), ofRandom(-r, r)));
		}

		set3D();
	}
	~Layer01_3d() {}
	void update(const double delta_time) override {}
	void draw() override {
		ofSpherePrimitive b;

		for (const auto& p : positions) {
			glm::mat4 model;
			model *= glm::translate(p);
			model *= glm::scale(scale.get());
			render_shader_.setUniformMatrix4f("model", model);
			b.draw();
		}
	}

	void bang() override {}
private:
	ofParameter<glm::vec3> position;
	ofParameter<glm::vec3> scale;

	const int Num = 300;
	std::vector<glm::vec3> positions;
};
}