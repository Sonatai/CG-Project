#include "Teleporter.h"

Teleporter::Teleporter(){}
Teleporter::Teleporter(ofxAssimpModelLoader* model, ofTexture* texture){
	teleportMesh = model;
	teleportTex = texture;
}
Teleporter::~Teleporter(){}
ofxAssimpModelLoader* Teleporter::getTeleportModel(){
	return teleportMesh;
}
ofTexture* Teleporter::getTeleportTex(){
	return teleportTex;
}