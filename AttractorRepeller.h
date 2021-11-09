#pragma once
#include "ofMain.h"
#include "Particle.h"
using namespace glm;

class Particle;
class AttractorRepeller
{
public:
	void setup(bool _isAttractor);
	void update();
	void draw();
	vec3 attract_repel(Particle p);

	bool isAttractor = true;
	float orbitRadius = 50;
	float t;
	vec3 pos;
	vec3 vel;
};

