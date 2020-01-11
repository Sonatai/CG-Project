#include "Schnabli.h"

Schnabli::Schnabli(){}
Schnabli::Schnabli(ofxAssimpModelLoader* model, ofTexture* texture) {
	schnabliMesh = model;
	schnabliTex = texture;
}
Schnabli::~Schnabli(){}
ofxAssimpModelLoader* Schnabli::getSchnabliModel() {
	return schnabliMesh;
}
ofTexture* Schnabli::getSchnabliTex() {
	return schnabliTex;
}