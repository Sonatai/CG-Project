#pragma once

#include "ofMain.h"
#include <vector>
#include "Cooky.h";
#include "Enemy.h";
#include "Tree.h";
#include "Teleporter.h";
#include "Schnabli.h"

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
private: 
	ofEasyCam cam;
	int textureTarget;
	ofPlanePrimitive ground;
	int groundHeight = 300;
	int groundWidth = 300;
	ofTexture* groundTex;
	int testanimation = 0;
	//... gameObjects
	Cooky* cookyObj;
	vector<Enemy*> enemyObjs;
	vector<Tree*> treeObjs;
	Schnabli* player;
	vector<Teleporter*> teleportObjs;
	
};
