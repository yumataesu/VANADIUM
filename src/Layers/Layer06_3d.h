#pragma once
#include "ofMain.h"
#include "ofxGen.h"
#include "ofxAutoReloadedShader.h"
using namespace ofx::Gen;

namespace Layers {
class Layer06_3d : public BaseLayer
{
public:
	void setup() override {

		quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
		quad.addVertex(ofVec3f(5.0, 5.0, 0.0));
		quad.addTexCoord(ofVec2f(1.0f, 1.0f));
		quad.addVertex(ofVec3f(5.0, -5.0, 0.0));
		quad.addTexCoord(ofVec2f(1.0f, 0.0f));
		quad.addVertex(ofVec3f(-5.0, -5.0, 0.0));
		quad.addTexCoord(ofVec2f(0.0f, 0.0f));
		quad.addVertex(ofVec3f(-5.0, 5.0, 0.0));
		quad.addTexCoord(ofVec2f(0.0f, 1.0f));

		up_sp.set("Spd", 0.1f, 0.1f, 10.0f);
		scale.set("Scale", 3.1f, 1.0f, 5.0f);

		parameter_group_.add(up_sp);
		parameter_group_.add(scale);

		ofDisableArbTex();
		ofLoadImage(eye, "ofxGen/Layer06_3d/stripe.jpg");
		eye.setTextureWrap(GL_REPEAT, GL_REPEAT);
		ofEnableArbTex();

		positoins_z.reserve(Layer_Num);
		angles.reserve(Layer_Num);

		for (int i = 0; i < Layer_Num; ++i) {
			positoins_z.emplace_back(ofMap(i, 0, Layer_Num - 1, -80, 0));
			angles.emplace_back(ofMap(i, 0, Layer_Num - 1, 0, 360));
		}

		set3D();
	}
	~Layer06_3d() {}
	void update(const double delta_time) override {
		elapsed_time += delta_time * speed;
		elapsed_time_up += delta_time * up_sp;

		auto result = std::find(bang_intervals.begin(), bang_intervals.end(), frame_num);
		frame_num += 1;
		if (result != bang_intervals.end()) { bang(); }
		if (frame_num > bang_intervals.back()) frame_num = 0;
	}
	void draw() override {
		render_shader_.setUniform1f("u_time", elapsed_time);
		render_shader_.setUniform1f("u_sp", elapsed_time_up);
		render_shader_.setUniform1f("u_scale", scale);
		render_shader_.setUniformTexture("u_src", eye, 0);
		for (int i = 0; i < Layer_Num; ++i) {
			render_shader_.setUniform1f("u_seed", ofMap(i, 0, Layer_Num - 1, 0.0f, 2.0f));

			float scale = ofMap(i, 0, Layer_Num - 1, 50.0f, 3.0f);
			ofMatrix4x4 model;
			model.rotate(elapsed_time + angles[i], -0.9, 0.3, 1);
			model.scale(scale, scale, scale);
			render_shader_.setUniformMatrix4f("model", model);
			quad.draw();
		}


		eye.draw(0, 0);
	}
	void bang() override {
		scale = ofRandom(scale.getMin(), scale.getMax());
	}
private:
	ofFbo fbo;
	ofxAutoReloadedShader shader;
	ofVboMesh quad;
	float elapsed_time = 0.0f;
	float elapsed_time_up = 0.0f;

	ofParameter<float> scale = 2.0f;
	ofParameter<float> up_sp = 1.0f;

	const int Layer_Num = 24;
	std::vector<float> positoins_z;
	std::vector<float> angles;

	ofTexture eye;

	int frame_num;
	std::vector<int> bang_intervals{ 2, 8, 16, 32, 64, 96, 128 };
	int random_bang;
};
}