#pragma once

#include "ofMain.h"
#include "Cooky.h";
#include "Enemy.h";
#include "Tree.h";
#include "Teleporter.h";

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void generateMipMap(ofTexture* texture);
		void rotatePlayer(int position);
		int getRightRotation(int position);
		void movePlayer(ofPoint position);
private: 
	ofEasyCam cam;
	int textureTarget;
	ofPlanePrimitive ground;
	int groundHeight = 300;
	int groundWidth = 300;
	ofTexture* groundTex;
	ofImage sky;
	int idleCount = 0;

	//... cam
	int camOffsetY = 7;
	int camOffsetZ = -20;
	float camDegree = -35;
	bool camBounded = true;

	//... light
	ofLight pointlight;

	//... gameObjects
	Cooky* cookyObj;
	Enemy** enemies;
	vector<Tree*> NOChunk;
	vector<Tree*>  OSChunk;
	vector<Tree*>  SWChunk;
	vector<Tree*>  WNChunk;
	int treeNumber = 100;
	Schnabli* player;
	Tree** teleportObjs;
	
};
