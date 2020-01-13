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
	void setupPlayer(int x, int y);
	void setAnimationState(string state);

private:
	ofTexture* texture;
	std::vector<ofxAssimpModelLoader*> models;
	ofxAssimpModelLoader* currentModel;
};

