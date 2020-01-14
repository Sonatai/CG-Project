#include "Schnabli.h"

Schnabli::Schnabli(){
	texture = new ofTexture();
}
Schnabli::~Schnabli(){}
ofxAssimpModelLoader* Schnabli::getPlayer() {
	return currentModel;
}
ofTexture* Schnabli::getTexture() {
	return texture;
}
void Schnabli::setupPlayer(int x, int z){
	ofLoadImage(*texture, "Princess/SchnabliTexOpaque.png");
	models.push_back(new ofxAssimpModelLoader());
	models.push_back(new ofxAssimpModelLoader());
	models.push_back(new ofxAssimpModelLoader());
	models.at(0)->loadModel("Princess/Schnabli_walk.dae");
	models.at(1)->loadModel("Princess/Schnabli_IdleDefault.dae");
	models.at(2)->loadModel("Princess/Schnabli_IdleSpecial.dae");
	float angle = -90;
	int numRotation;
	ofPoint axis = ofPoint(1.0, 0.0, 0.0);
	for (auto i = models.begin(); i != models.end(); i++) {
		ofPushMatrix();
		(*i)->setPosition(x, 2.5, z);
		numRotation = (*i)->getNumRotations();
		(*i)->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
		(*i)->setScale(0.04, 0.04, 0.04);
		ofPopMatrix();
	}
	models[0]->setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	models[1]->setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	models[2]->setLoopStateForAllAnimations(OF_LOOP_NONE);
	currentModel = models.at(0);
	currentModel->getAnimation(0).play();
}
void Schnabli::setAnimationState(string state){
	if (state == "WALK");
	if (state == "IDLE");
	if (state == "SPECIAL");
}

float Schnabli::getMSBackward() { return msBackward; }
float Schnabli::getMSFoward() { return msForward; }