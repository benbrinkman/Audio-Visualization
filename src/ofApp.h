#pragma once

#include "ofMain.h"
#include "AudioAnalyser.h"
#include "particle.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	int width;
	int height;

    ofFmodSoundPlayer   m_soundPlayer;
	AudioAnalyser   m_audioAnalyser;
	ofTrueTypeFont  m_font;
	ofTrueTypeFont  m_font2;
	

	bool	toggle;

	float			circleBrightness[4];

	ofColor			toneColor[4];
	ofColor			toneColorDull[4];
	float volume;
	float volMod;
	float rotate;
	float cubeRotate;


	int numParticles;
	ofVec2f partPos;
	particle part[4][500];
};
