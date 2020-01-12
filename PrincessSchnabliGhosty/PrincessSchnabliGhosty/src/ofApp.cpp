#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	//... Setup General
	ofDisableArbTex();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	//cam.setDistance(200);
	//cam.setPosition(0, 0, 0);
	//cam.tilt(-50);
	cam.enableMouseInput();
	ofSetWindowTitle("Princess Schnabli Ghosty");
	ofSetColor(ofColor::grey);
	ofSetSmoothLighting(true);

	//... Setup Ground
	ground.set(groundWidth, groundHeight);
	ground.setPosition(0, 0, 0);
	ground.setResolution(2, 2);
	groundTex = new ofTexture();
	ofLoadImage(*groundTex, "Ground/groundTex.png");

	

	//... Setup Schnabli
	player = new Schnabli();
	player->setupPlayer(0, 0);
	
	//... Setup Enemies
	//... Setup Teleportportals
	//... Setup Cooky
	//... Setup Trees
	//setupTrees(treeNumber);
}

/*void ofApp::setupTrees(int treeNumber) {
	int x = - 150;
	int z = -150;
	for (int i = 0; i < treeNumber; i++) {
		if (x < 0 && z < 0) {
			NOChunk[NOChunk.size()]
			NOChunk[NOChunk.size()-1].setPlayer(player);
			NOChunk[NOChunk.size() - 1].checkLOD();
		}
		else if (x > 0 && z > 0) {
			SWChunk.push_back(Tree(x, z));
			SWChunk[SWChunk.size() - 1].setPlayer(player);
			SWChunk[SWChunk.size() - 1].checkLOD();
		}
		else if (x > 0 && z < 0) {
			WNChunk.push_back(Tree(x, z));
			WNChunk[WNChunk.size() - 1].setPlayer(player);
			WNChunk[WNChunk.size() - 1].checkLOD();
		}
		else if (x > 0 && z > 0) {
			OSChunk.push_back(Tree(x, z));
			OSChunk[OSChunk.size() - 1].setPlayer(player);
			OSChunk[OSChunk.size() - 1].checkLOD();
		}

		x += 3;
		z += 3;
	}
}*/
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------

/*void ofApp::DrawTrees() {
	for (auto i = OSChunk.begin(); i != OSChunk.end(); i++) {
		i->getTreeTexture()->bind();
		generateMipMap(i->getTreeTexture());
		i->getTreeModel()->drawFaces();
		i->getTreeTexture()->unbind();
	}
	for (auto i = WNChunk.begin(); i != WNChunk.end(); i++) {
		i->getTreeTexture()->bind();
		generateMipMap(i->getTreeTexture());
		i->getTreeModel()->drawFaces();
		i->getTreeTexture()->unbind();
	}
	for (auto i = SWChunk.begin(); i != SWChunk.end(); i++) {
		i->getTreeTexture()->bind();
		generateMipMap(i->getTreeTexture());
		i->getTreeModel()->drawFaces();
		i->getTreeTexture()->unbind();
	}
	for (auto i = NOChunk.begin(); i != NOChunk.end(); i++) {
		i->getTreeTexture()->bind();
		generateMipMap(i->getTreeTexture());
		i->getTreeModel()->drawFaces();
		i->getTreeTexture()->unbind();
	}
}*/

void ofApp::draw(){
	
	cam.begin();
	ofDrawGrid();

	groundTex->bind();
	generateMipMap(groundTex);
	ground.draw();
	groundTex->unbind();

	//DrawTrees();


	//... transparence
	player->getTexture()->bind();
	generateMipMap(player->getTexture());
	player->getPlayer()->drawFaces();
	player->getTexture()->unbind();

	cam.end();
	
}

void ofApp::generateMipMap(ofTexture* texture) {
	textureTarget = texture->getTextureData().textureTarget;
	glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D); // automatically creates midmaps for the loaded texture
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
