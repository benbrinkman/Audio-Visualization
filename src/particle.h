#pragma once
#include "ofMain.h"


class particle
{
public:

	ofVec2f pos;
	float diamater;
	float angle;
	float speed;
	float opacity;
	int direction;

	particle();
	~particle();

	void randomize();
};

