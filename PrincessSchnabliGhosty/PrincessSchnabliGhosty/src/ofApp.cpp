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

	//... Setup Trees
	//... Setup Schnabli
	player = new Schnabli(new ofxAssimpModelLoader(), new ofTexture());
	player->getSchnabliModel()->loadModel("Princess/Schnabli.dae");
	ofLoadImage(*player->getSchnabliTex(), "Princess/SchnabliTex.png");
	player -> getSchnabliModel()  -> setLoopStateForAllAnimations(OF_LOOP_NONE);
	cout << player->getSchnabliModel()->getAnimationCount() << endl;
	//... Setup Enemies
	//... Setup Teleportportals
	//... Setup Cooky
	

}
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	cam.begin();
	ofDrawGrid();

	groundTex->bind();
	generateMipMap(groundTex);
	ground.draw();
	groundTex->unbind();

	//... transparence
	player->getSchnabliTex()->bind();
	generateMipMap(player->getSchnabliTex());
	player->getSchnabliModel()->drawFaces();
	player->getSchnabliTex()->unbind();
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
	if (key == ' ') {
		cout << "space" << endl;
		if (testanimation % 3 == 0) {
			testanimation++;
			player->getSchnabliModel()->getAnimation(0).play();
		}
		else if (testanimation % 3 == 1) {
			testanimation++;
			player->getSchnabliModel()->getAnimation(1).play();
		}
		else if (testanimation % 3 == 2) {
			player->getSchnabliModel()->getAnimation(2).play();
		}
	}
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
