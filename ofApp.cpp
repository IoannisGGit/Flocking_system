#include "ofApp.h"
#include "helpers.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//set background colour to black
	ofSetBackgroundColor(0);
	ofSetFullscreen(true);

	// Setup Gui
	myGui.setup();
	myGui.add(myFpsLabel.setup("FPS", ofToString(ofGetFrameRate(), 2)));
	myGui.add(paramNumBoids.set("Num Boids", 1500, 0, 10000));
	myGui.add(paramRange.set("Range", 50.0, 0.0, 200.0));
	myGui.add(paramSeparationFactor.set("Separation", 0.1, 0.0, 1.0));
	myGui.add(paramAlignmentFactor.set("Alignment", 0.1, 0.0, 1.0));
	myGui.add(paramCohesionFactor.set("Cohesion", 0.1, 0.0, 1.0));
	myGui.add(paramAttractionFactor.set("Attraction/Repulsion", 0.5, 0.0, 1.0));
	myGui.add(paramNeighbourDist.set("Neighbour dist", 10.0, 0.0, 100.0));
	myGui.add(paramTargetVel.set("Target vel", 0.1, 0.0, 1.0));
	myGui.add(paramDamping.set("Damping", 0.01, 0.0, 1.0));
	myGui.add(displayAttr.set("Display Attractors", false));
	myGui.add(displayBox.set("Display Box", false));
	myGui.add(buttonRestart.setup("Restart"));
	myGui.add(paramSettingsFileName.set("Settings file", "test.txt"));
	myGui.add(buttonSaveSettings.setup("Save Settings"));
	myGui.add(buttonLoadSettings.setup("Load Settings"));

	// Setup listeners for parameters
	buttonRestart.addListener(this, &ofApp::setupBoids);
	buttonSaveSettings.addListener(this, &ofApp::saveSettingsButtonPressed);
	buttonLoadSettings.addListener(this, &ofApp::loadSettingsButtonPressed);


	//Setup the particles
	setupBoids();

	bBox.setup(200);

	attractor.setup(true);

	//Setup EasyCam
	myCamera.setAutoDistance(false);
	myCamera.setPosition(vec3(0.0, 10.0, 100.0));
	myCamera.setTarget(vec3(0.0, 0.0, 0.0));
}

//--------------------------------------------------------------
void ofApp::update(){
	//transfer parameters to particle system
	myParticleSystem.separationFactor = paramSeparationFactor;
	myParticleSystem.alignmentFactor = paramAlignmentFactor;
	myParticleSystem.cohesionFactor = paramCohesionFactor;
	myParticleSystem.attractionFactor = paramAttractionFactor;

	myParticleSystem.neighbourDist = paramNeighbourDist;
	myParticleSystem.targetVel = paramTargetVel;
	myParticleSystem.damping = paramDamping;

	attractor.update();

	//Update the particles
	myParticleSystem.update(&bBox, &attractor);

	// Update Fps label
	myFpsLabel = ofToString(ofGetFrameRate(), 2);

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	myCamera.begin();

	// Draw the particles
	myParticleSystem.draw();

	
	// Draw Bounding Box
	if(displayBox) bBox.draw();

	//draw attractor/repeler
	if (displayAttr) attractor.draw();

	// Finish drawing objects in 3D space
	myCamera.end();
	ofDisableDepthTest();

	//Draw GUI
	if (show_gui) myGui.draw();

}

void ofApp::setupBoids() {
	myParticleSystem.setup(paramNumBoids, paramRange);
}


void ofApp::saveSettingsButtonPressed() {
	// Get the fileName from the GUI parameter
	string fileName = paramSettingsFileName.toString();

	// Get the filepath to save to the data directory
	string filePath = ofToDataPath(fileName);

	// If the data directory doesn't already exist, create it
	if (!ofDirectory::doesDirectoryExist("")) {
		ofDirectory::createDirectory("");
	}

	// Open text file and write data to it
	ofstream outfile(filePath);

	if (!outfile.is_open()) {
		std::cout << "Error: couldn't open file " << paramSettingsFileName << " for writing\n";
		return;
	}

	outfile << paramNumBoids << "\n";
	outfile << paramRange << "\n";
	outfile << paramSeparationFactor << "\n";
	outfile << paramAlignmentFactor << "\n";
	outfile << paramCohesionFactor << "\n";

	outfile.close();
}

//------------------------------------------------
void ofApp::loadSettingsButtonPressed() {
	// Get the fileName from the GUI parameter
	string fileName = paramSettingsFileName.toString();

	// Get the filepath to save to the data directory
	string filePath = ofToDataPath(fileName);

	// Open text file and read data from it
	ifstream infile(filePath);

	if (!infile.is_open()) {
		std::cout << "Error: couldn't open file " << paramSettingsFileName << " for reading\n";
		return;
	}

	infile >> paramNumBoids;
	infile >> paramRange;
	infile >> paramSeparationFactor;
	infile >> paramAlignmentFactor;
	infile >> paramCohesionFactor;

	infile.close();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g') show_gui = !show_gui;
	if(key == 'q')paramSeparationFactor+=0.01;
	if (key == 'w')paramAlignmentFactor += 0.01;
	if (key == 'e')paramCohesionFactor += 0.01;
	if (key == 'r')paramAttractionFactor += 0.01;
	

	if (key == 'a')paramSeparationFactor -= 0.01;
	if (key == 's')paramAlignmentFactor -= 0.01;
	if (key == 'd')paramCohesionFactor -= 0.01;
	if (key == 'f')paramAttractionFactor -= 0.01;
	
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
