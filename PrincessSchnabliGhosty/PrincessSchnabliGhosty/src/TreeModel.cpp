#include "TreeModel.h"

TreeModel::TreeModel() {
	treeMeshArr = new std::vector<ofxAssimpModelLoader*>;
	treeTexArr = new std::vector<ofTexture*>;
}
TreeModel::~TreeModel() {}
std::vector<ofxAssimpModelLoader*>* TreeModel::getTreeModelArr() {
	return treeMeshArr;
}
std::vector<ofTexture*>* TreeModel::getTreeTexArr() {
	return treeTexArr;
}
