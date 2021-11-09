#include "ParticleSystem.h"
#include "helpers.h"

//--------------------------------------------------------------
void ParticleSystem::setup(int numParticles, float range) {
	myParticles.clear();

	for (int i = 0; i < numParticles; i++) {
		Particle p;
		p.setup(vec3(ofRandom(-range, range), 
			         ofRandom(0, range), 
			         ofRandom(-range, range)), 
			    vec3(0, 0, 0));
		myParticles.push_back(p);
	}
}

//--------------------------------------------------------------
void ParticleSystem::update(BoundingBox* bBox, AttractorRepeller* attr_repel) {
	//first recalculate the grid
	updateGrid();

	for (int i = 0; i < myParticles.size(); i++) {
		
		myParticles[i].update(this, bBox);

		//calculate attraction force
		 forceAttr = attr_repel->attract_repel(myParticles[i])*attractionFactor;
		
		//apply it on particles
		myParticles[i].applyAttractor(forceAttr);
	}
	
}

//--------------------------------------------------------------
void ParticleSystem::draw() {
	ofPushStyle();
	
	for (int i = 0; i < myParticles.size(); i++) {
		myParticles[i].draw();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
int ParticleSystem::getNumParticles() {
	return myParticles.size();
}

//--------------------------------------------------------------
vec3 ParticleSystem::getParticlePos(int i) {
	return myParticles[i].getPos();
}

//--------------------------------------------------------------
vec3 ParticleSystem::getParticleVel(int i) {
	return myParticles[i].getVel();
}

//--------------------------------------------------------------
void ParticleSystem::getNeighbours_simple(vec3 pos, vector<int>* neighbours) {
	for (int i = 0; i < myParticles.size(); i++) {
		float dist = distance(pos, myParticles[i].getPos());
		if (dist < neighbourDist && dist > 0) {
			neighbours->push_back(i);
		}
	}
}


//--------------------------------------------------------------
ivec3 ParticleSystem::getBoxIndex(vec3 pos) {
	// Calculate which (ix, iy, iz) box contains the position pos
	ivec3 boxIndex = (pos - myGridOrigin) / myGridBoxSize;

	// Max sure that the box index isn't outside the grid range
	return clamp(boxIndex, ivec3(0, 0, 0), myBoxMaxIndex);
}

//--------------------------------------------------------------
int ParticleSystem::getGridDataIndex(ivec3 boxIndex) {
	// Calculate where box (ix, iy, iz) is in the array of grid values
	return boxIndex.x
		+ boxIndex.y * myGridSize.x
		+ boxIndex.z * myGridSize.x * myGridSize.y;
}
//--------------------------------------------------------------
void ParticleSystem::updateGrid() {
	// Update the grid data used to accelerate calculations of neighbours
	myGridBoxSize = neighbourDist;

	// Find the minimum and maximum particle positions
	vec3 minPos = myParticles[0].getPos();
	vec3 maxPos = minPos;

	for (int i = 1; i < myParticles.size(); i++) {
		vec3 curPos = myParticles[i].getPos();
		minPos = min(minPos, curPos);
		maxPos = max(maxPos, curPos);
	}

	// Calculate grid origin and number of boxes in each dimension
	myGridOrigin = minPos;
	myGridSize = ceil((maxPos - minPos) / myGridBoxSize);

	// Calculate maximum box index values as we will need it when
	// calculating box index values
	myBoxMaxIndex = myGridSize - ivec3(1, 1, 1);

	// Clear any existing grid data
	myGridData.clear();

	// Create an element for each box in the grid
	int numBoxes = myGridSize.x * myGridSize.y * myGridSize.z;
	myGridData.resize(numBoxes);

	// For each particle, calculate which box in the grid it's in
	for (int i = 1; i < myParticles.size(); i++) {
		ivec3 boxIndex = getBoxIndex(myParticles[i].getPos());
		int gridDataIndex = getGridDataIndex(boxIndex);
		// Place the index for this particle into the box
		myGridData[gridDataIndex].particleIndices.push_back(i);
	}
}


void ParticleSystem::getNeighbours_grid(vec3 pos, vector<int>* neighbours) {
	// Returns a list of indexes for particles that are within the specified radius of pos
	// Uses a grid structure to accelerate calculations
	float radiusSquared = neighbourDist * neighbourDist;

	// Get the range of grid boxes that might have neighbours in them
	ivec3 minBoxIndex = getBoxIndex(pos - vec3(neighbourDist));
	ivec3 maxBoxIndex = getBoxIndex(pos + vec3(neighbourDist));

	// Loop through the boxes and find any valid neigbours
	for (int bx = minBoxIndex.x; bx <= maxBoxIndex.x; bx++) {
		for (int by = minBoxIndex.y; by <= maxBoxIndex.y; by++) {
			for (int bz = minBoxIndex.z; bz <= maxBoxIndex.z; bz++) {
				int gridDataIndex = getGridDataIndex(ivec3(bx, by, bz));
				int numParticlesInBox = myGridData[gridDataIndex].particleIndices.size();
				for (int i = 0; i < numParticlesInBox; i++) {
					int otherIndex = myGridData[gridDataIndex].particleIndices[i];
					vec3 otherPos = myParticles[otherIndex].getPos();
					float distSquared = distance2(otherPos, pos);
					if (distSquared < radiusSquared && distSquared > 0) {
						// We've found a neighbour within the specified radius
						// Add it to the list
						neighbours->push_back(otherIndex);
					}
				}
			}
		}
	}
}
float ParticleSystem::getGridBoxSize() {
	return myGridBoxSize;
}

ivec3 ParticleSystem::getGridSize() {
	return myGridSize;
}

