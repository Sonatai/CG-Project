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
		class Cube
		{
		public:
			Cube();
			~Cube();
			void generateCube();
			void setReferencePlayer(Schnabli& playerRef);
			void sortCube();
			void drawCube();


		private:
			vector<ofPlanePrimitive*> cubeSides;
			Schnabli player;
		};

private: 
	ofEasyCam* cam;
	int textureTarget;
	ofPlanePrimitive ground;
	int groundHeight = 1000;
	int groundWidth = 1000;
	ofTexture* groundTex;
	ofImage sky;
	int idleCount = 0;

	//... cam
	int camOffsetY = 28;
	int camOffsetZ = -30;
	float camDegree = -35;
	bool camBounded = true;

	//... light
	ofLight pointlight;
	ofLight spotlight;

	//... gameObjects

	vector<Tree*> NOChunk;
	vector<Tree*>  OSChunk;
	vector<Tree*>  SWChunk;
	vector<Tree*>  WNChunk;
	vector<ofTexture*> treeLODtexture;
	vector<ofxAssimpModelLoader*> treeLODmodels;
	int treeNumber = 100;
	Tree* testTree1;
	Tree* testTree2;
	Tree* testTree3;
	Tree* testTree4;

	Schnabli* player;
	bool isMoving = false;

	ofApp::Cube* cube;
	
};
