#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"

class Enemy
{
public:
	Enemy();
	Enemy(ofxAssimpModelLoader* model, ofTexture* texture);
	~Enemy();
	ofxAssimpModelLoader* getEnemyModel();
	ofTexture* getEnemyTex();
private:
	ofTexture* enemyTex;
	ofxAssimpModelLoader* enemyMesh;
};

