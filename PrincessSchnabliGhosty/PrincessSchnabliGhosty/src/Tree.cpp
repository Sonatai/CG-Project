#include "Tree.h"

Tree::Tree(){}
Tree::Tree(int x, int z, std::vector<ofxAssimpModelLoader*>& LODmodels, std::vector<ofTexture*>* LODtextures, Schnabli* player) {
	setupTree(x, z, LODmodels,  LODtextures);
	setPlayer(player);
}
Tree::~Tree(){}
void Tree::setLOD1(int x) {
	currentModel = (models.at(x));
	currentTexture = textures->at(x);
}

ofxAssimpModelLoader* Tree::getTreeModel() {
	return currentModel;
}
ofTexture* Tree::getTreeTexture() {
	return currentTexture;
}
void Tree::setPlayer(Schnabli* player) {
	this->player = player;
}
void Tree::checkLOD() {
	float distance = std::sqrt(
		std::pow(currentModel->getPosition().x - player->getPlayer()->getPosition().x, 2) +
		std::pow(currentModel->getPosition().z - player->getPlayer()->getPosition().z, 2)
	);
	if (distance < 150) {
		currentModel = models.at(0);
		currentTexture = textures->at(0);
	}
	else if (distance < 300) {
		currentModel = models.at(1);
		currentTexture = textures->at(1);
	}
	else {
		currentModel = models.at(2);
		currentTexture = textures->at(2);
	}
}

void Tree::setupTree(int x, int z, std::vector<ofxAssimpModelLoader*>& LODmodels, std::vector<ofTexture*>* LODtextures) {
	models.push_back(new ofxAssimpModelLoader(*(LODmodels[0])));
	models.push_back(new ofxAssimpModelLoader(*(LODmodels[1])));
	models.push_back(new ofxAssimpModelLoader(*(LODmodels[2])));

	for (auto i = models.begin(); i != models.end(); i++) {
		ofPushMatrix();
		(*i)->setPosition(x, 0, z);
		ofPopMatrix();
	}
	textures = LODtextures;
	currentModel = models[0];
	currentTexture = textures->at(0);
}