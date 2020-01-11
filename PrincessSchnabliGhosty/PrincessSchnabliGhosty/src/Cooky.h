#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"

class Cooky
{
public:
	Cooky();
	Cooky(ofxAssimpModelLoader* model, ofTexture* texture);
	~Cooky();
	ofxAssimpModelLoader* getCookyModel();
	ofTexture* getCookyTex();
private:
	ofTexture* cookyTex;
	ofxAssimpModelLoader* cookyMesh;
};

