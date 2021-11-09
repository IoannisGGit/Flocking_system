#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ParticleSystem.h"
#include "BoundingBox.h"
#include "AttractorRepeller.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void setupBoids();
		
		void saveSettingsButtonPressed();
		void loadSettingsButtonPressed();

		ParticleSystem myParticleSystem;
		AttractorRepeller attractor;
		BoundingBox bBox;
		
		//gui parameters
		ofxLabel myFpsLabel;
		ofParameter<int> paramNumBoids;
		ofParameter<float> paramRange;
		ofParameter<float> paramSeparationFactor;
		ofParameter<float> paramAlignmentFactor;
		ofParameter<float> paramCohesionFactor;
		ofParameter<float> paramAttractionFactor;
		ofParameter<float> paramNeighbourDist;
		ofParameter<float> paramTargetVel;
		ofParameter<float> paramDamping;
		ofParameter<bool> displayAttr;
		ofParameter<bool> displayBox;
		ofParameter<string> paramSettingsFileName;
		ofxButton buttonRestart;
		ofxButton buttonSaveSettings;
		ofxButton buttonLoadSettings;
		ofxPanel myGui;

		ofEasyCam myCamera;

		bool show_gui = true;

	
		
};
