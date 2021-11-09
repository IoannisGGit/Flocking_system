#include "AttractorRepeller.h"
void AttractorRepeller::setup(bool _isAttractor) {
	pos = vec3(0, 0, 0);
	isAttractor = _isAttractor;

}

void AttractorRepeller::update() {
	t = ofGetElapsedTimef();
	pos = orbitRadius *vec3(sin(t),cos(t),sin(t));
}

void AttractorRepeller::draw() {
	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofDrawSphere(pos,10);
	ofPopStyle();
}

vec3 AttractorRepeller::attract_repel(Particle p) {

	vec3 dir = normalize(pos - p.getPos());
	float d = length(pos - p.getPos());
	float force;
	if (isAttractor) force = 1 * 100 / ( d);
	else  force = -1 * 100 / ( d);
	return dir*force;

}