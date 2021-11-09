#include "BoundingBox.h"
void BoundingBox::setup(float range){

	myBoxMesh.setMode(OF_PRIMITIVE_LINES);
	_range = range;
	setupPlanes(_range);
	
}

void BoundingBox::setup(float rangeX, float rangeY, float rangeZe) {

}
void BoundingBox::setupPlanes(float range) {
	glPointSize(5);
	int gridSizeX = 20;
	int gridSizeY = 20;
	int gridSizeZ = 20;

	//top plane
	for (int i = 0; i < gridSizeX; i++)
		for (int j = 0; j < gridSizeZ; j++) {
			vec3 pos = vec3(
				ofMap(i, 0, gridSizeX - 1, -0.5 * range, 0.5 * range),
				0.5 *range,
				ofMap(j, 0, gridSizeZ - 1, -0.5 * range, 0.5 * range));
			myBoxMesh.addVertex(pos);
		}

	//bottom plane
	for (int i = 0; i < gridSizeX; i++)
		for (int j = 0; j < gridSizeZ; j++) {
			vec3 pos = vec3(
				ofMap(i, 0, gridSizeX - 1, -0.5 * range, 0.5 * range),
				-0.5 * range,
				ofMap(j, 0, gridSizeZ - 1, -0.5 * range, 0.5 * range));
			myBoxMesh.addVertex(pos);
		}
	//left plane
	for (int i = 0; i < gridSizeY; i++)
		for (int j = 0; j < gridSizeZ; j++) {
			vec3 pos = vec3(
				+0.5 * range,
				ofMap(i, 0, gridSizeY - 1, -0.5 * range, 0.5 * range),
				ofMap(j, 0, gridSizeZ - 1, -0.5 * range, 0.5 * range));
			myBoxMesh.addVertex(pos);
		}
	//right plane
	for (int i = 0; i < gridSizeY; i++)
		for (int j = 0; j < gridSizeZ; j++) {
			vec3 pos = vec3(
				-0.5 * range,
				ofMap(i, 0, gridSizeY - 1, -0.5 * range, 0.5 * range),
				ofMap(j, 0, gridSizeZ - 1, -0.5 * range, 0.5 * range));
			myBoxMesh.addVertex(pos);
		}

	//front plane
	for (int i = 0; i < gridSizeX; i++)
		for (int j = 0; j < gridSizeY; j++) {
			vec3 pos = vec3(
				ofMap(i, 0, gridSizeX - 1, -0.5 * range, 0.5 * range),
				ofMap(j, 0, gridSizeY - 1, -0.5 * range, 0.5 * range),
				-0.5 * range);
			myBoxMesh.addVertex(pos);
		}
	//back plane
	for (int i = 0; i < gridSizeX; i++)
		for (int j = 0; j < gridSizeY; j++) {
			vec3 pos = vec3(
				ofMap(i, 0, gridSizeX - 1, -0.5 * range, 0.5 * range),
				ofMap(j, 0, gridSizeY - 1, -0.5 * range, 0.5 * range),
				0.5 * range);
			myBoxMesh.addVertex(pos);
		}
}
void BoundingBox::setupCorners(float range) {
	glPointSize(20);
	

	vec3 p1 = vec3(-range / 2, range / 2, -range / 2);
	vec3 p2 = vec3(-range / 2, range / 2, range / 2);

	vec3 p3 = vec3(range / 2, range / 2, -range / 2);
	vec3 p4 = vec3(range / 2, range / 2, range / 2);

	vec3 p5 = vec3(-range / 2, -range / 2, -range / 2);
	vec3 p6 = vec3(-range / 2, -range / 2, range / 2);

	vec3 p7 = vec3(range / 2, -range / 2, -range / 2);
	vec3 p8 = vec3(range / 2, -range / 2, range / 2);

	myBoxMesh.addVertex(p1);
	myBoxMesh.addVertex(p2);
	myBoxMesh.addVertex(p3);
	myBoxMesh.addVertex(p4);
	myBoxMesh.addVertex(p5);
	myBoxMesh.addVertex(p6);
	myBoxMesh.addVertex(p7);
	myBoxMesh.addVertex(p8);
}

void BoundingBox::update() {

}

void BoundingBox::draw() {
	ofPushStyle();
	ofSetColor(0, 255, 70);
	myBoxMesh.draw();
	ofPopStyle();
}

float BoundingBox::getBoxRange() {
	return _range;
}
