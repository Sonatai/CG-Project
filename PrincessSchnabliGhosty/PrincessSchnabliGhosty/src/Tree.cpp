#include "Tree.h"

Tree::Tree(){}
Tree::Tree(std::vector<ofxAssimpModelLoader*> models, std::vector<ofTexture*> textures){
	treeMeshArr = models;
	treeTexArr = textures;
}
Tree::~Tree(){}
std::vector<ofxAssimpModelLoader*> Tree::getTreeModelArr(){
	return treeMeshArr;
}
std::vector<ofTexture*> Tree::getTreeTexArr(){
	return treeTexArr;
}