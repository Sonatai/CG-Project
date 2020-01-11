#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"
#include <vector>

class Tree
{
public:
	Tree();
	Tree(std::vector<ofxAssimpModelLoader*> models, std::vector<ofTexture*> textures);
	~Tree();
	std::vector<ofxAssimpModelLoader*> getTreeModelArr();
	std::vector<ofTexture*> getTreeTexArr();
private:
	std::vector<ofTexture*> treeTexArr;
	std::vector<ofxAssimpModelLoader*> treeMeshArr;
};

