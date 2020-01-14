#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"
#include "ofxFBX.h"

class Schnabli
{
public:
	Schnabli();
	~Schnabli();
	ofxAssimpModelLoader* getPlayer();
	ofTexture* getTexture();
	void setupPlayer(int x, int z);
	void setAnimationState(string state);
	float getMSBackward();
	float getMSFoward();

private:
	ofTexture* texture;
	std::vector<ofxAssimpModelLoader*> models;
	ofxAssimpModelLoader* currentModel;
	float msForward = 0.5;
	float msBackward = 0.25;
};

