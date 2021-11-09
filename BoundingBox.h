#pragma once
#include "ofMain.h"
using namespace glm;

class BoundingBox
{
	public:
		void setup(float range);
		void setupCorners(float range);
		void setupPlanes(float range);
		void setup(float rangeX, float rangeY, float rangeZ);
		void update();
		void draw();

		ofMesh myBoxMesh;
		float getBoxRange();

private:
	float _range;
};

