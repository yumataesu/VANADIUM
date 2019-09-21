#pragma once
#include "ofMain.h"
#include "ofxGen.h"
#include "ofxAutoReloadedShader.h"
#include <future>

using namespace ofx::Gen;

namespace Layers {
class Layer02_3d : public BaseLayer
{
public:
	void setup() override {

		parameter_group_.add(scale.set("Scl", glm::vec3(1.f), glm::vec3(0.f), glm::vec3(100.f)));

		ofDisableArbTex();
		loaded = false;

		r = std::async(std::launch::async, [&]() {
			ofLoadImage(pix, "ofxGen/Layer02_3d/tex.jpg");
			loaded = true;
			return pix;
			});

		sphere.set(300, 60);
		vbomesh = sphere.getMesh();	
		set3D();
	}
	~Layer02_3d() {}
	void update(const double delta_time) override {
		static bool setteduniform_once = false;
		ofDisableArbTex();
		if (loaded && !setteduniform_once) {
			tex.loadData(pix);
			sphere.mapTexCoordsFromTexture(tex);
			if (tex.isAllocated()) {
				render_shader_.begin();
				
				render_shader_.end();
				setteduniform_once = true;
			}
		}
	}
	void draw() override {
		
		ofMatrix4x4 model;
		model.rotate(elapsed_time, -0.9, 0.3, 1);
		model.scale(scale.get());
		render_shader_.setUniformMatrix4f("model", model);
		if (tex.isAllocated())render_shader_.setUniformTexture("u_src", tex, 0);
		vbomesh.draw();
	}
	void bang() override {}
private:
	ofParameter<glm::vec3> scale;
	float elapsed_time;

	bool loaded;
	ofTexture tex;
	std::future<ofPixels> r;
	ofPixels pix;
	ofVboMesh vbomesh;
	ofSpherePrimitive sphere;

};
}