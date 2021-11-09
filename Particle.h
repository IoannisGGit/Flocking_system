#pragma once

#include "ofMain.h"
#include "ParticleSystem.h"
#include "BoundingBox.h"

using namespace glm;

class ParticleSystem;
class BoundingBox;


class Particle {
public:
	void setup(vec3 pos, vec3 vel);
	void update(ParticleSystem *psystem);
	void update(ParticleSystem *psystem, BoundingBox *bbox);
	void boundaries(float range);
	void applyAttractor(vec3 _force);
	

	void draw();
	vec3 getPos();
	vec3 getVel();
	vector<int> neighbours;
	vector<vec3>neighboursPos;
	float redCoef;
	float greenCoef;
	float blueCoef;
	float size = 1;
private:
	vec3 myPos;
	vec3 myVel;
	float maxVelocity = 0.5;
};
