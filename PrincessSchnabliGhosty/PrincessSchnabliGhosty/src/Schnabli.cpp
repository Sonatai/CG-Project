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
void Schnabli::setupPlayer(int x, int y){
	ofLoadImage(*texture, "Princess/SchnabliTex.png");
	models.push_back(new ofxAssimpModelLoader());
	models.push_back(new ofxAssimpModelLoader());
	models.push_back(new ofxAssimpModelLoader());
	models.at(0)->loadModel("Princess/Schnabli_walk.dae");
	models.at(1)->loadModel("Princess/Schnabli_IdleDefault.dae");
	models.at(2)->loadModel("Princess/Schnabli_IdleSpecial.dae");
	float angle = 180;
	int numRotation;
	ofPoint axis = ofPoint(1.0, 0.0, 0.0);
	for (auto i = models.begin(); i != models.end(); i++) {
		(*i)->setScale(0.05, 0.05, 0.05);
		numRotation = (*i)->getNumRotations();
		(*i)->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
		(*i)->setPosition(x,y,2);
	}
	currentModel = models.at(0);
	cout << "Size of vector: " << models.size();
	currentModel->setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	currentModel->getAnimation(0).play();
}
void Schnabli::setAnimationState(string state){}