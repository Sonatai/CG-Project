#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"

class Schnabli
{
public:
	Schnabli();
	Schnabli(ofxAssimpModelLoader* model, ofTexture* texture);
	~Schnabli();
	ofxAssimpModelLoader* getSchnabliModel();
	ofTexture* getSchnabliTex();
private:
	ofTexture* schnabliTex;
	ofxAssimpModelLoader* schnabliMesh;
};

