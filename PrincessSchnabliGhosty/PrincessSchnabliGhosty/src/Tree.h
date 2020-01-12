#pragma once
#include <iostream>
#include <vector>
#include "TreeModel.h"
#include "Schnabli.h"
#include <cmath> 

class Tree
{
public:
	Tree();
	Tree(int x, int z);
	~Tree();
	void setLOD1(int x);
	ofxAssimpModelLoader* getTreeModel();
	ofTexture* getTreeTexture();
	void setPlayer(Schnabli* player);
	void checkLOD();
	void setupTree(int x, int z);


private:
	std::vector<ofxAssimpModelLoader> models;
	std::vector<ofTexture> textures;
	ofxAssimpModelLoader* currentModel;
	ofTexture* currentTexture;
	Schnabli* player;

};

