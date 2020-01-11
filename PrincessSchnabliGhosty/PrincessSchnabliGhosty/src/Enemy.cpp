#include "Enemy.h"

Enemy::Enemy(){}
Enemy::Enemy(ofxAssimpModelLoader* model, ofTexture* texture){
	enemyMesh = model;
	enemyTex = texture;
}
Enemy::~Enemy(){}
ofxAssimpModelLoader* Enemy::getEnemyModel(){
	return enemyMesh;
}
ofTexture* Enemy::getEnemyTex() {
	return enemyTex;
}
