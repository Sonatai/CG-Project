#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//... Setup General
	ofDisableArbTex();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("Princess Schnabli Ghosty");
	ofSetColor(ofColor::grey);
	ofSetSmoothLighting(true);
	ofLoadIdentityMatrix();

	//... Sky
	sky.load("skybox.jpeg");

	//... Setup Ground
	
	ground.set(groundWidth, groundHeight);
	ground.setPosition(0, 0, 0);
	ground.setResolution(2, 2);
	groundTex = new ofTexture();
	ofLoadImage(*groundTex, "Ground/groundTex.png");

	//... Setup Schnabli
	player = new Schnabli();
	player->setupPlayer(0, 0);
	
	//... Setup Cam
	glm::vec3 rotationAxis = glm::vec3(1, 0, 0);
	cam.rotateDeg(camDegree, rotationAxis);
	cam.disableMouseInput();
	glm::vec3 sesitivity = glm::vec3(0, 0.25, 0);
	cam.setRotationSensitivity(sesitivity);


	//... Setup Enemies
	//... Setup Teleportportals
	//... Setup Cooky
	//... Setup Trees
	
		//... Pointlight
	pointlight.setPointLight();
	pointlight.setPosition(0, 30, 0);
	pointlight.setAttenuation(0.5, 0.5, 0.5);
	pointlight.setSpecularColor(ofColor(73, 104, 191, 50));
	pointlight.setDiffuseColor(ofColor(24, 35, 64, 20));
	pointlight.setAmbientColor(ofColor(97, 139, 255, 50));
}


//--------------------------------------------------------------


void ofApp::update() {
	idleCount++;
	if (idleCount > 600) {
		player->setAnimationState("SPECIAL");
		idleCount = 0;
	}
	player -> checkeSpecialMove();
	player->getPlayer()->update();
	if (camBounded) {
		ofPushMatrix();
		cam.setPosition(player->getPlayer()->getPosition().x, player->getPlayer()->getPosition().y +camOffsetY, player->getPlayer()->getPosition().z-camOffsetZ);
		ofPopMatrix();
	}

}

//--------------------------------------------------------------


void ofApp::draw(){

	ofEnableLighting();
	pointlight.enable();
	glDisable(GL_DEPTH_TEST);

	sky.draw(0, 0);

	glEnable(GL_DEPTH_TEST);
	cam.begin();
	ofDrawGrid();

	ofPushMatrix();
	ofRotateX(90);
	groundTex->bind();
	generateMipMap(groundTex);
	ground.draw();
	groundTex->unbind();
	ofPopMatrix();

	//... Player 

	player->getTexture()->bind();
	generateMipMap(player->getTexture());
	player->getPlayer()->drawFaces();
	player->getTexture()->unbind();

	//... transparence
	

	cam.end();
	glDisable(GL_DEPTH_TEST);
	pointlight.disable();
	ofDisableLighting();

}

void ofApp::generateMipMap(ofTexture* texture) {
	textureTarget = texture->getTextureData().textureTarget;
	glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D); // automatically creates midmaps for the loaded texture
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'w') {
		ofPoint position = player->getPlayer()->getPosition();
		position.z -= player->getMSFoward();
		
		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(0);
			player->setAnimationState("WALK");
		}
	}
	else if (key == 's') {
		ofPoint position = player->getPlayer()->getPosition();
		position.z += player->getMSFoward();

		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(2);
			player->setAnimationState("WALK");
		}
	}
	else if (key == 'a') {
		ofPoint position = player->getPlayer()->getPosition();
		position.x -= player->getMSFoward();

		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(1);
			player->setAnimationState("WALK");
		}
	}
	else if (key == 'd') {
		ofPoint position = player->getPlayer()->getPosition();
		position.x += player->getMSFoward();

		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(3);
			player->setAnimationState("WALK");
		}
	}
	player->IsRotated(true);
	
}
void ofApp::movePlayer(ofPoint position) {
	ofPushMatrix();
	player->getPlayer()->setPosition(position.x, position.y, position.z);
	ofPopMatrix();
	for (auto i = player->getModels().begin(); i != player->getModels().end(); i++) {
		ofPushMatrix();
		(*i)->setPosition(position.x, position.y, position.z);
		ofPopMatrix();
	}
}
void ofApp::rotatePlayer(int position) {
	int angle = getRightRotation(position);
	ofPoint axis = ofPoint(0.0, 0.0, 1.0);
	int numRotation = player->getPlayer()->getNumRotations();
	ofPushMatrix();
	player->getPlayer()->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
	ofPopMatrix();
	for (auto i = player->getModels().begin(); i != player->getModels().end(); i++) {
		ofPushMatrix();
		numRotation = (*i)->getNumRotations();
		(*i)->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
		ofPopMatrix();
	}
}

int ofApp::getRightRotation(int position) {
	int playerPosition = player->RotationPosition();
	int angle;
	switch (position) {
	case 0:
		(playerPosition == 0) ? angle = 0 :
			(playerPosition == 1) ? angle = -90 :
			(playerPosition == 2) ? angle = -180 :
			angle = -270;
		break;
	case 1:
		(playerPosition == 0) ? angle = -270 :
			(playerPosition == 1) ? angle = 0 :
			(playerPosition == 2) ? angle = -90 :
			angle = -180;
		break;
	case 2:
		(playerPosition == 0) ? angle = -180 :
			(playerPosition == 1) ? angle = -270 :
			(playerPosition == 2) ? angle = 0 :
			angle = -90;
		break;
	case 3:
		(playerPosition == 0) ? angle = -90 :
			(playerPosition == 1) ? angle = -180 :
			(playerPosition == 2) ? angle = -270 :
			angle = 0;
		break;
	}
	player->RotationPosition(position);
	return angle;
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == ' ') {
		camBounded = !camBounded;
		if (camBounded)
			cam.disableMouseInput();
		else
			cam.enableMouseInput();
	}
	player->IsRotated(false);
	player->setAnimationState("IDLE");
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
