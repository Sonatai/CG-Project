#include "Enemy.h"

Enemy::Enemy(){
	enemyTex = new ofTexture();
}
Enemy::~Enemy(){}
std::vector<ofxAssimpModelLoader*> Enemy::getEnemyModel(){
	return enemyMesh;
}
ofTexture* Enemy::getEnemyTex() {
	return enemyTex;
}
