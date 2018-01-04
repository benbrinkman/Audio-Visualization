#include "ofApp.h"

void ofApp::setup() 
{
	cubeRotate = 0;
	rotate = 0;
	width = 1280;
	height = 900;
	numParticles = 500;
	for (int i = 0; i < numParticles; i++) {
		for (int j = 0; j < 4; j++) {
			part[j][i].randomize();
			part[j][i].angle = ofRandom(0, 90) + 90 * j;

			//part[j][i].pos.x = ofRandom(0, width / 4) + width/(j+1);
			//part[j][i].pos.x =  (width / 4 / numParticles * i) + (width/4)*(j-2) + 5;
		}
	}
	toneColor[0] = ofColor(ofFloatColor(1.0f, 0.0f, 0.0f));// , circleBrightness[0]));
	toneColor[1] = ofColor(ofFloatColor(0.0f, 1.0f, 0.0f));//, circleBrightness[1]));
	toneColor[2] = ofColor(ofFloatColor(1.0f, 1.0f, 0.0f));//, circleBrightness[2]));
	toneColor[3] = ofColor(ofFloatColor(0.0f, 0.0f, 1.0f));//, circleBrightness[3]));

	toneColorDull[0] = ofColor(ofFloatColor(0.7f, 0.0f, 0.0f));// , circleBrightness[0]));
	toneColorDull[1] = ofColor(ofFloatColor(0.0f, 0.7f, 0.0f));//, circleBrightness[1]));
	toneColorDull[2] = ofColor(ofFloatColor(0.7f, 0.7f, 0.0f));//, circleBrightness[2]));
	toneColorDull[3] = ofColor(ofFloatColor(0.0f, 0.0f, 0.7f));//, circleBrightness[3]));

	partPos = ofVec2f(width/2, height/2);
	toggle = true;
	ofSetVerticalSync(true);
    ofSetWindowShape(width, height);
	
    m_font.load( "fonts/font.ttf", 12, true );
	m_font2.load("fonts/font.ttf", 120, true);
	
    m_soundPlayer.load( "1612.mp3" );
    m_soundPlayer.setLoop( true );
    m_soundPlayer.play();
	//m_soundPlayer.setPositionMS(215000);

    m_audioAnalyser.init( &m_soundPlayer, 20 );
}

void ofApp::update()
{
	if (m_soundPlayer.getPositionMS() / 1000.0f > 221.7){
		for (int i = 0; i < numParticles; i++) {
			for (int j = 0; j < 4; j++) {
				part[j][i].randomize();
				part[j][i].angle = ofRandom(0, 90) + 90 * j;
				rotate = 0;
				//part[j][i].pos.x = ofRandom(0, width / 4) + width/(j+1);
				//part[j][i].pos.x =  (width / 4 / numParticles * i) + (width/4)*(j-2) + 5;
			}
		}
}

	if (m_soundPlayer.getPositionMS() / 1000.0f > 96.3 
		&& m_soundPlayer.getPositionMS() / 1000.0f < 139.5 
		|| m_soundPlayer.getPositionMS() / 1000.0f > 162.5)
		rotate++;
	
	OF_RECTMODE_CENTER;
    m_audioAnalyser.update();

	float drums = m_audioAnalyser.getLinearAverage(0);
	float piano = m_audioAnalyser.getLinearAverage(6);
	float tone1 = m_audioAnalyser.getLinearAverage(14);
	float snare = m_audioAnalyser.getLinearAverage(10);
	
	circleBrightness[0] = ofMap(drums, 200.0f, 350.0f, 0.0f, 1.0f, true);
	circleBrightness[1] = ofMap(piano, 40.0f, 80.0f, 0.0f, 1.0f, true);
	circleBrightness[2] = ofMap(tone1, 26.0f, 56.0f, 0.0f, 1.0f, true);
	circleBrightness[3] = ofMap(snare, 16.0f, 23.0f, 0.0f, 1.0f, true);

	for (int i = 0; i < 4; i++)
		toneColorDull[i].a = circleBrightness[i] * 255;

	volume = m_audioAnalyser.getMixLevel();
	volMod = volume / 0.73;
	cubeRotate += 1 * volMod;
	if (m_soundPlayer.getPositionMS() / 1000.0f < 69 || m_soundPlayer.getPositionMS() / 1000.0f > 72) {
		for (int i = 0; i < numParticles; i++) {
			for (int j = 0; j < 4; j++) {
				if ((part[j][i].pos.x > 780) && circleBrightness[j] > 0.2) {
					part[j][i].speed = circleBrightness[j] * 10 * ofRandom(0, 3.0f);
					part[j][i].pos.x = 0;
				}
				part[j][i].pos.x += part[j][i].speed;

				if (m_soundPlayer.getPositionMS() / 1000.0f > 195) {
					if (part[j][i].opacity > 0)
						part[j][i].opacity--;
				}
				else {

					float percent = part[j][i].pos.x;
					if (percent < 0)
						percent *= -1;
					part[j][i].opacity = 255 - 255 * (percent / 780);
				}

			}
		}
	}
}


void ofApp::draw() 
{
	
    ofBackground( ofColor::black );
   

	
	
	/*************************DRAW PARTICLES****************************/


	
	
	ofPushMatrix(); 
		ofTranslate(partPos);
		ofRotate(rotate);
		ofSetColor(toneColorDull[0]);
		ofDrawRectangle(0, 0, width, width);
		ofSetColor(toneColorDull[1]);
		ofDrawRectangle(-width, -width, width, width);
		ofSetColor(toneColorDull[2]);
		ofDrawRectangle(-width, 0, width, width);
		ofSetColor(toneColorDull[3]);
		ofDrawRectangle(0, -width, width, width);
	ofPopMatrix();

	if (m_soundPlayer.getPositionMS() / 1000.0f > 96.3) {
		ofPushMatrix();
			ofTranslate(partPos);
			ofRotate(rotate);
			ofSetColor(toneColorDull[1]);
			ofDrawRectangle(0, 0, width, width);
			ofSetColor(toneColorDull[0]);
			ofDrawRectangle(-width, -width, width, width);
			ofSetColor(toneColorDull[3]);
			ofDrawRectangle(-width, 0, width, width);
			ofSetColor(toneColorDull[2]);
			ofDrawRectangle(0, -width, width, width);
		ofPopMatrix();

	}


	for (int i = 0; i < numParticles; i++) {
		ofPushMatrix();
			ofTranslate(partPos);
			
			for (int j = 0; j < 4; j++)
			{
				ofPushMatrix();
				ofRotate(part[j][i].direction * rotate);
				ofRotate(part[j][i].angle);
					ofTranslate(part[j][i].pos);
					toneColor[j].a = part[j][i].opacity;
					ofSetColor(toneColor[j]);
					ofDrawCircle(0, 0, part[j][i].diamater + part[j][i].diamater * volMod);
					toneColor[j].a = 255;
				ofPopMatrix();
			}
		ofPopMatrix();
	}
	
	//ofLogNotice("dir: " + ofToString(part[j][i].direction));
	
	

	if (!toggle) {
		ofSetColor(ofColor::white);
		m_font.drawString("Volume Level", 140, 50);
		//Volume levels
		ofDrawCircle(100, 100, m_audioAnalyser.getLeftLevel()  * 100.0f);
		ofDrawCircle(200, 100, m_audioAnalyser.getRightLevel() * 100.0f);
		ofDrawCircle(300, 100, m_audioAnalyser.getMixLevel()   * 100.0f);

		m_font.drawString("Left", 80, 170);
		m_font.drawString("Right", 180, 170);
		m_font.drawString("Mix", 290, 170);

		m_audioAnalyser.drawWaveform(40, 300, 1200, 90);
		m_audioAnalyser.drawSpectrum(40, 460, 1200, 128);
		m_audioAnalyser.drawLinearAverages(40, 650, 1200, 128);

		float songTimeSeconds = m_soundPlayer.getPositionMS() / 1000.0f;
		m_font.drawString("Song time: " + ofToString(songTimeSeconds), 40, 250);

		ofSetColor(toneColor[0]);
		ofDrawCircle(500, 100, 50);

		ofSetColor(toneColor[1]);
		ofDrawCircle(650, 100, 50);

		ofSetColor(toneColor[2]);
		ofDrawCircle(800, 100, 50);

		ofSetColor(toneColor[3]);
		ofDrawCircle(950, 100, 50);

		ofSetColor(ofColor::white);
	}


	ofSetColor(ofColor::white);
	if (m_soundPlayer.getPositionMS() / 1000.0f > 70.5 && m_soundPlayer.getPositionMS() / 1000.0f < 72) {
		m_font2.drawString("FRANK", 640 - 228, 400);
		m_font2.drawString("SINATRA", 640 - 323, 600);
	}
	else if (m_soundPlayer.getPositionMS() / 1000.0f > 69.8 && m_soundPlayer.getPositionMS() / 1000.0f < 72) {
		m_font2.drawString("FRANK", 640 - 228, 400);
	}

	
}

void ofApp::keyPressed(int key) 
{
	if (key = ' ') {
		if (toggle)
			toggle = false;
		else
			toggle = true;
	}
}
