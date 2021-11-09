#include "Particle.h"
#include "helpers.h"

//--------------------------------------------------------------
void Particle::setup(vec3 pos, vec3 vel) {
	myPos = pos;
	myVel = vel;
}

//--------------------------------------------------------------
void Particle::update(ParticleSystem *psystem) {


	vec3 separationForce = vec3(0, 0, 0);
	vec3 averagePos = vec3(0, 0, 0);
	vec3 averageVel = vec3(0, 0, 0);
	

	vector<int> neighbours;
	psystem->getNeighbours_grid(myPos,&neighbours);
	int numNeighbours = neighbours.size();
	for (int i = 0; i < numNeighbours; i++) {
		int neighbourIndex = neighbours[i];
		vec3 otherPos = psystem->getParticlePos(neighbourIndex);
		separationForce += normalize(myPos - otherPos);
		averagePos += otherPos;
		averageVel += psystem->getParticleVel(neighbourIndex);
		
		
	}

	if (numNeighbours > 0) {
		averagePos /= numNeighbours;
		averageVel /= numNeighbours;

		myVel += 0.01 * psystem->separationFactor * separationForce;
		myVel += 0.01 * psystem->alignmentFactor * averageVel;
		myVel += 0.01 * psystem->cohesionFactor * (averagePos - myPos);

		
		
	}
	

	myPos += myVel;
}
//--------------------------------------------------------------
void Particle::update(ParticleSystem* psystem, BoundingBox* bbox) {


	vec3 separationForce = vec3(0, 0, 0);
	vec3 averagePos = vec3(0, 0, 0);
	vec3 averageVel = vec3(0, 0, 0);
	vec3 bounceBackForce = vec3(0, 0, 0);


	neighbours.clear();
	neighboursPos.clear();

	psystem->getNeighbours_grid(myPos, &neighbours);
	int numNeighbours = neighbours.size();
	for (int i = 0; i < numNeighbours; i++) {
		int neighbourIndex = neighbours[i];
		vec3 otherPos = psystem->getParticlePos(neighbourIndex);
		neighboursPos.push_back(otherPos);
		separationForce += normalize(myPos - otherPos);
		averagePos += otherPos;
		averageVel += psystem->getParticleVel(neighbourIndex);


	}

	
	

	if (numNeighbours > 0) {
		averagePos /= numNeighbours;
		averageVel /= numNeighbours;

		myVel +=  0.01*psystem->separationFactor * separationForce;
		myVel += 0.01 * psystem->alignmentFactor * averageVel;
		myVel += 0.01 * psystem->cohesionFactor * (averagePos - myPos);


	}

	//check boundaries
	boundaries(bbox->getBoxRange() / 2);

	if (length(myVel) > maxVelocity) {
		myVel = glm::normalize(myVel) * maxVelocity;
	}
	
	myPos += myVel;

	
}

//--------------------------------------------------------------
void Particle::draw() {
	
	ofSetColor(255);
	ofDrawSphere(myPos, 0.2);
	
	for (int i = 0; i < neighboursPos.size(); i++) {
		vec3 otherPos = neighboursPos[i];
		ofSetColor(255, ofMap(neighboursPos.size(), 0, 20, 200, 50));
		ofDrawLine(myPos, otherPos);
	}
}
void Particle::applyAttractor(vec3 _force) {
	myVel += 0.01 * _force;
}

void Particle::boundaries(float range) {
	if (myPos.x > range) {
		myPos.x = range;
		myVel.x *= -1;
	}

	if (myPos.x < -range) {
		myPos.x = -range;
		myVel.x *= -1;
	}
	if (myPos.y > range) {
		myPos.y = range;
		myVel.y *= -1;
	}
	if (myPos.y < -range) {
		myPos.y = -range;
		myVel.y *= -1;
	}
	if (myPos.z > range) {
		myPos.z = range;
		myVel.z *= -1;
	}
	if (myPos.z < -range) {
		myPos.z = -range;
		myVel.z *= -1;
	}
}

//--------------------------------------------------------------
vec3 Particle::getPos() {
	return myPos;
}

//--------------------------------------------------------------
vec3 Particle::getVel() {
	return myVel;
}
