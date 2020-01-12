#include "Tree.h"

Tree::Tree(){}
Tree::Tree(int x, int z) {
	setupTree(x, z);
}
Tree::~Tree(){}
void Tree::setLOD1(int x) {
	currentModel = &(models.at(x));
	currentTexture = &(textures.at(x));
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
		std::pow(currentModel->getPosition().y - player->getPlayer()->getPosition().y, 2) +
		std::pow(currentModel->getPosition().z - player->getPlayer()->getPosition().z, 2)
	);
	if (distance < 50) {
		currentModel = &models.at(0);
		currentTexture = &textures.at(0);
	}
	else if (distance < 100) {
		currentModel = &models.at(1);
		currentTexture = &textures.at(1);
	}
	else {
		currentModel = &models.at(2);
		currentTexture = &textures.at(2);
	}
}

void Tree::setupTree(int x, int z) {
	models.push_back(ofxAssimpModelLoader());
	models.push_back(ofxAssimpModelLoader());
	models.push_back(ofxAssimpModelLoader());
	models.at(0).loadModel("Tree/LOD1/SpookyTree650.obj");
	models.at(1).loadModel("Tree/LOD2/SpookyTree250.obj");
	models.at(2).loadModel("Tree/LOD3/SpookyTree100.obj");
	float angle = 90.0;
	int numRotation;
	ofPoint axis = ofPoint(1.0, 0.0, 0.0);
	for (auto i = models.begin(); i != models.end(); i++) {
		i->setScale(0.25, 0.25, 0.25);
		numRotation = i->getNumRotations();
		i->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
		i->setPosition(x, 0, z);
	}
	textures.push_back(ofTexture());
	textures.push_back(ofTexture());
	textures.push_back(ofTexture());
	ofLoadImage(textures.at(0), "Tree/LOD1/SpookyTree650Tex.png");
	ofLoadImage(textures.at(1), "Tree/LOD2/SpookyTree250Tex.png");
	ofLoadImage(textures.at(2), "Tree/LOD3/SpookyTree100Tex.png");
	currentModel = &models[0];
	currentTexture = &textures[0];
}