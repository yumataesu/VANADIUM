# vanadium
vanadium is a Visual Contents Management System for openFrameworks Intermediates, especially Vj etc.

<b>This is a fragment of code!!</b>


![ss](https://github.com/yumataesu/vanadium/blob/master/docs/ss.png)


## Feature
* Drag&Drop Interface
* Multi Preset
* render 2D&3D scene
* create normal from world coordnate (you dont need to normal always)
* Flat Shading only
* Deferred Rendering
* SSAO
* Bloom


## How to build

* openFrameworks v0.10.1
* windows 10 (not tested on mac)

0. Update oF's GLFW library
 This project is using imgui on experimental branch to use a docking system.
So to build this project, you have to replace glfw to latest now.

1. <b>git clone</b>
```
git clone --recursive https://github.com/yumataesu/vanadium
```

2. <b>create project from PG.</b>
3. <b>Build</b>

## How to add your visual
1. Add the following template to Layers folder
If you write 3D scene, you have to add `set3D()` in setup.

```C++
#pragma once
#include "ofMain.h"
#include "ofxGen.h"
#include "ofxAutoReloadedShader.h"
using namespace ofx::Gen;

namespace Layers {
class Your_layer : public BaseLayer
{
public:
	void setup() override {
		set3D();
	}
	~Your_layer() {}
	void update(const double delta_time) override {}
	void draw() override {}
	void bang() override {}
private:
};
}
```

2. Write your scene with these variable
* <b>width_</b> : canvas width
* <b>height_</b> : canvas height
* <b>parameter_group_</b> : parameter group for save/load
   (If you save/load parameter, write `parameter_group_.add(your_v.set("Value", 0.0, 0.0, 10.0))` in setup 
* <b>render_shader_</b> : it is important if you render 3d scene. see [this](https://github.com/yumataesu/vanadium/blob/master/src/Layers/Layer05_3d.h)


3. register your class to manager class

```C++
ofxGen::Manager::registeration<Layers::Your_layer>("Your_layer"); // in ofApp::setup

```


## UI


<div style="text-align: left;">
	
![slot](https://github.com/yumataesu/vanadium/blob/master/docs/slot2.png)

</div>


<div style="text-align: right;">
	
|   |   |
|--:|---|
| 1  | Layer Delete Button  |
|  2 |  Layer Alpha |
|  3 | Preset Combo Box  |
|  4 | User defined parames(ofParameter)  |
|  5 |  Update(save) currrent preset |
|  6 |  Add new preset as json |
|  7 |  Get screenshot for thumbnnail |
	
</div>
