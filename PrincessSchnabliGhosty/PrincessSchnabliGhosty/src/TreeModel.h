#pragma once
#include "ofxAssimpModelLoader.h"
#include <vector>
class TreeModel
{
public:
	TreeModel();
	~TreeModel();
	std::vector<ofxAssimpModelLoader*>* getTreeModelArr();
	std::vector<ofTexture*>* getTreeTexArr();
private:
	std::vector<ofTexture*>* treeTexArr;
	std::vector<ofxAssimpModelLoader*>* treeMeshArr;

};

