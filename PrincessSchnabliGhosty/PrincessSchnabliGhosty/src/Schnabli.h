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
	bool IsRotated();
	bool IsRotated(bool rotated);
	int RotationPosition();
	int RotationPosition(int value);
	std::vector<ofxAssimpModelLoader*>& getModels();
	void checkeSpecialMove();

private:
	ofTexture* texture;
	std::vector<ofxAssimpModelLoader*> models;
	ofxAssimpModelLoader* currentModel;
	float msForward = 0.75;
	float msBackward = 0.45;
	bool isRotated = false;
	int position = 0;
	bool specialIdle = false;
};

