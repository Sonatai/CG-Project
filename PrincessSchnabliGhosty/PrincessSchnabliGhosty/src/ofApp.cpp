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
	
	/****************
	*	Setup Cam	*
	*****************/
	cam = new ofEasyCam();
	glm::vec3 rotationAxis = glm::vec3(1, 0, 0);
	cam->rotateDeg(camDegree, rotationAxis);
	cam->disableMouseInput();
	glm::vec3 sesitivity = glm::vec3(0, 0.25, 0);
	cam->setRotationSensitivity(sesitivity);

	/********************
	*	Setup Trees		*
	*********************/
	//ofxAssimpModelLoader* testModelCopy = new ofxAssimpModelLoader(*(testModel));
	
	//... Load one time texture and set reference in objects
	treeLODtexture.push_back(new ofTexture());
	treeLODtexture.push_back(new ofTexture());
	treeLODtexture.push_back(new ofTexture());
	ofLoadImage(*treeLODtexture[0], "Tree/LOD1/SpookyTree650Tex.png");
	ofLoadImage(*treeLODtexture[1], "Tree/LOD2/SpookyTree250Tex.png");
	ofLoadImage(*treeLODtexture[2], "Tree/LOD3/SpookyTree100Tex.png");

	//... load one time models and copy them?
	treeLODmodels.push_back(new ofxAssimpModelLoader());
	treeLODmodels.push_back(new ofxAssimpModelLoader());
	treeLODmodels.push_back(new ofxAssimpModelLoader());
	treeLODmodels[0]->loadModel("Tree/LOD1/SpookyTree650.obj");
	treeLODmodels[1]->loadModel("Tree/LOD2/SpookyTree250.obj");
	treeLODmodels[2]->loadModel("Tree/LOD3/SpookyTree100.obj");

	float angle = 180.0;
	int numRotation;
	ofPoint axis = ofPoint(1.0, 0.0, 0.0);
	for (auto i = treeLODmodels.begin(); i != treeLODmodels.end(); i++) {
		numRotation = (*i)->getNumRotations();
		ofPushMatrix();
		(*i)->setScale(0.05, 0.05, 0.05);
		(*i)->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
		(*i)->setPosition(0, 0, 0);
		ofPopMatrix();
	}

	testTree1 = new Tree(10, 10, treeLODmodels, &treeLODtexture);
	testTree2 = new Tree(60, 60, treeLODmodels, &treeLODtexture);
	testTree3 = new Tree(100, 100, treeLODmodels, &treeLODtexture);
	testTree4 = new Tree(200, -200, treeLODmodels, &treeLODtexture);
	NOChunk.push_back(new Tree(10, 10, treeLODmodels, &treeLODtexture));

	testTree1->setPlayer(player);
	testTree2->setPlayer(player);
	testTree3->setPlayer(player);
	testTree4->setPlayer(player);

	//... ofCube?
	cube = new Cube();
	cube->generateCube();
	
	//... Pointlight ... Dunno how it works -> changes dont matter
	pointlight.setPointLight();
	glm::vec3 sizeOfPointlight = glm::vec3(100, 100, 100);
	ofPushMatrix();
	pointlight.setScale(sizeOfPointlight);
	pointlight.setPosition(0, 100, 0);
	ofPopMatrix();
	pointlight.setAttenuation(0.5, 0.1, 0.5); //0,0,0 -> schwarz
	pointlight.setSpecularColor(ofColor(255, 255, 255, 0));
	pointlight.setDiffuseColor(ofColor(255, 255, 255, 0));
	pointlight.setAmbientColor(ofColor(255, 255, 255, 0));
	pointlight.lookAt(ofVec3f(0, 0, 0));

	spotlight.setSpotlight();
	spotlight.setSpotlightCutOff(80); //Wie flach/breit der Kegel ist
	spotlight.setSpotConcentration(650); //Wie weit der Kegel streut
	spotlight.setAttenuation(0.8, 0, 0); //Gesamtschwächung von Lichtenergie
	spotlight.setSpecularColor(ofColor(181, 225, 255, 100)); //... higlight reflection, dependent on the direction
	spotlight.setDiffuseColor(ofColor(105, 195, 255, 100));  //... direct light, dependent on the incident angle
	spotlight.setAmbientColor(ofColor(91, 113, 128, 50));  //... bouncing light mutiple times

	ofPushMatrix();
	spotlight.setPosition(0, 1000, 0); //... Höhe bestimmt wieviel Licht überhaupt gestreut werden kann
	spotlight.setScale(4, 4, 4);
	spotlight.tiltDeg(-90);
	ofPopMatrix();
}


//--------------------------------------------------------------
void addTree(int x, int z, std::vector<ofxAssimpModelLoader*>& LODmodels, std::vector<ofTexture*>* LODtextures) {
	//add a tree to a chunck.
}

void ofApp::update() {
	idleCount++;
	if (idleCount > 600 && !isMoving) {
		player->setAnimationState("SPECIAL");
		idleCount = 0;
	}
	player -> checkeSpecialMove();
	player->getPlayer()->update();
	if (camBounded) {
		ofPushMatrix();
		cam->setPosition(player->getPlayer()->getPosition().x, player->getPlayer()->getPosition().y +camOffsetY, player->getPlayer()->getPosition().z-camOffsetZ);
		ofPopMatrix();
	}
	testTree1->checkLOD();
	testTree2->checkLOD();
	testTree3->checkLOD();
	testTree4->checkLOD();

}

//--------------------------------------------------------------


void ofApp::draw(){

	ofEnableLighting();

	glDisable(GL_DEPTH_TEST);
	sky.draw(0, 0);
	glEnable(GL_DEPTH_TEST);

	spotlight.enable();
	//pointlight.enable();

	cam->begin();
	ofDrawGrid();

	ofPushMatrix();
	ofRotateXDeg(90);
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

	//... Trees
	testTree1->getTreeTexture()->bind();
	generateMipMap(testTree1->getTreeTexture());
	testTree1->getTreeModel()->drawFaces();
	testTree1->getTreeTexture()->unbind();

	testTree2->getTreeTexture()->bind();
	generateMipMap(testTree2->getTreeTexture());
	testTree2->getTreeModel()->drawFaces();
	testTree2->getTreeTexture()->unbind();

	testTree3->getTreeTexture()->bind();
	generateMipMap(testTree3->getTreeTexture());
	testTree3->getTreeModel()->drawFaces();
	testTree3->getTreeTexture()->unbind();

	testTree4->getTreeTexture()->bind();
	generateMipMap(testTree4->getTreeTexture());
	testTree4->getTreeModel()->drawFaces();
	testTree4->getTreeTexture()->unbind();

	//... transparence
	cube->drawCube();

	cam->end();
	glDisable(GL_DEPTH_TEST);
	spotlight.disable();
	//pointlight.disable();
	ofDisableLighting();
	//pointlight.draw();
	//spotlight.draw();
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
		isMoving = true;
	}
	else if (key == 's') {
		ofPoint position = player->getPlayer()->getPosition();
		position.z += player->getMSFoward();

		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(2);
			player->setAnimationState("WALK");
		}
		isMoving = true;
	}
	else if (key == 'a') {
		ofPoint position = player->getPlayer()->getPosition();
		position.x -= player->getMSFoward();

		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(1);
			player->setAnimationState("WALK");
		}
		isMoving = true;
	}
	else if (key == 'd') {
		ofPoint position = player->getPlayer()->getPosition();
		position.x += player->getMSFoward();

		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(3);
			player->setAnimationState("WALK");
		}
		isMoving = true;
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
		if (camBounded) {
			cout << "cam bounded" << endl;
			cam->disableMouseInput();
			cam->disableMouseMiddleButton();
		}
		else {
			cout << "cam not bounded" << endl;
			cam->setDistance(30);
			cam->enableMouseInput();
			cam->enableMouseMiddleButton();
		}
	}
	player->IsRotated(false);
	isMoving = false;
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


ofApp::Cube::Cube() {}
ofApp::Cube::~Cube() {}
void ofApp::Cube::generateCube() {
	cubeSides.push_back(new ofPlanePrimitive());
	cubeSides.push_back(new ofPlanePrimitive());
	cubeSides.push_back(new ofPlanePrimitive());
	cubeSides.push_back(new ofPlanePrimitive());
	cubeSides.push_back(new ofPlanePrimitive());
	cubeSides.push_back(new ofPlanePrimitive());
	
	ofPushMatrix();
	cubeSides[0]->set(5, 5);
	cubeSides[0]->setPosition(0, 0, 0);
	cubeSides[0]->setResolution(2, 2);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[1]->set(5, 5);
	cubeSides[1]->setPosition(0, 5, 0);
	cubeSides[1]->setResolution(2, 2);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[2]->set(5, 5);
	cubeSides[2]->setPosition(2.5, 0, 0);
	cubeSides[2]->setResolution(2, 2);
	ofRotateXDeg(90);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[3]->set(5, 5);
	cubeSides[3]->setPosition(-2.5, 0, 0);
	cubeSides[3]->setResolution(2, 2);
	ofRotateXDeg(90);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[4]->set(5, 5);
	cubeSides[4]->setPosition(0, 0, 2.5);
	cubeSides[4]->setResolution(2, 2);
	ofRotateZDeg(90);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[5]->set(5, 5);
	cubeSides[5]->setPosition(0, 0, -2.5);
	cubeSides[5]->setResolution(2, 2);
	ofRotateZDeg(90);
	ofPopMatrix();

}
void ofApp::Cube::setReferencePlayer(Schnabli& playerRef) {
	player = playerRef;
}
void ofApp::Cube::sortCube() {

}
void ofApp::Cube::drawCube() {
	cubeSides[0]->drawFaces();
	cubeSides[1]->drawFaces();
	cubeSides[2]->drawFaces();
	cubeSides[3]->drawFaces();
	cubeSides[4]->drawFaces();
	cubeSides[5]->drawFaces();
}
