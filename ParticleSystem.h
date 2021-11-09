#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "BoundingBox.h"
#include "AttractorRepeller.h"

using namespace glm;

class Particle;
class AttractorRepeller;


struct GridElement {
	vector<int> particleIndices;
};

class ParticleSystem {
public:
	void setup(int numParticles, float range);
	void update(BoundingBox *bBox, AttractorRepeller *attr_repel);
	void draw();
	int getNumParticles();
	vec3 getParticlePos(int i);
	vec3 getParticleVel(int i);
	void getNeighbours_grid(vec3 pos, vector<int>* neighbours);
	void getNeighbours_simple(vec3 pos, vector<int>* neighbours);
	float getGridBoxSize();
	ivec3 getGridSize();

	//parameters from gui to ps
	float separationFactor;
	float alignmentFactor;
	float cohesionFactor;
	float attractionFactor;
	float neighbourDist;
	float targetVel;
	float damping;
	vec3 forceAttr;
	
private:
	vector<Particle> myParticles;
	void updateGrid();
	ivec3 getBoxIndex(vec3 pos);

	vector<GridElement> myGridData;
	ivec3 myGridSize;
	vec3 myGridOrigin;
	float myGridBoxSize;
	ivec3 myBoxMaxIndex;
	int getGridDataIndex(ivec3 boxIndex);
	
};
