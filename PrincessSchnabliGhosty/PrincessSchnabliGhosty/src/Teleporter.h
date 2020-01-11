#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"

class Teleporter
{
public:
	Teleporter();
	Teleporter(ofxAssimpModelLoader* model, ofTexture* texture);
	~Teleporter();
	ofxAssimpModelLoader* getTeleportModel();
	ofTexture* getTeleportTex();
private:
	ofTexture* teleportTex;
	ofxAssimpModelLoader* teleportMesh;
};

