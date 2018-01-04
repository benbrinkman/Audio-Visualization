#pragma once

#include "particle.h"

particle::particle() {
	
}

particle::~particle() {


}

void particle::randomize() {
	angle = ofRandom(0, 90);
	diamater = ofRandom(5, 20);
	pos = ofVec2f(0, 0);
	speed = ofRandom(0, 3.0f);
	opacity = 1.0f;
	direction = ofRandom(0, 2);
	if (direction == 0)
		direction = -1;
}