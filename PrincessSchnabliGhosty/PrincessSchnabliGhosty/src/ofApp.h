#pragma once

#include <ctime>  
#include <cstdlib> 
#include "ofMain.h"
#include "Tree.h"
#include "ofxFog.h"

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
		void addTree(int x, int z, std::vector<ofxAssimpModelLoader*>& LODmodels, std::vector<ofTexture*>* LODtextures);
		int* spwanPoint();
		
		class Cube
		{
		public:
			Cube();
			~Cube();
			void generateCube();
			void setReferenceCam(ofEasyCam* camRef);
			void sortCube();
			void drawCube();


		private:
			vector<ofPlanePrimitive*> cubeSides;
			ofEasyCam* cam;
		};

		void checkPlayerChunk(bool NO, bool OS, bool SW, bool WN);

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
	int camOffsetZ = -40;
	float camDegree = -30;
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
	int LODCount = 30;
	vector<ofPlanePrimitive*> grinchySkybox;
	ofTexture* grinchySkyboxTexture;

	Schnabli* player;
	bool isMoving = false;

	ofxFog fog;
	bool isFog = true;

	ofApp::Cube* cube;
	
};
