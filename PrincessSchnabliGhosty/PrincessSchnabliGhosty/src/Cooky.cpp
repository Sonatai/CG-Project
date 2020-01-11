#include "Cooky.h"
Cooky::Cooky(){}
Cooky::Cooky(ofxAssimpModelLoader* model, ofTexture* texture){
	cookyMesh = model;
	cookyTex = texture;
}
Cooky::~Cooky(){}
ofxAssimpModelLoader* Cooky::getCookyModel() {
	return cookyMesh;
}
ofTexture* Cooky::getCookyTex() {
	return cookyTex;
}