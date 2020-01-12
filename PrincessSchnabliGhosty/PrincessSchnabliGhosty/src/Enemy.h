#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"

class Enemy
{
public:
	Enemy();
	~Enemy();
	std::vector<ofxAssimpModelLoader*> getEnemyModel();
	ofTexture* getEnemyTex();
private:
	ofTexture* enemyTex;
	std::vector<ofxAssimpModelLoader*> enemyMesh;
};

