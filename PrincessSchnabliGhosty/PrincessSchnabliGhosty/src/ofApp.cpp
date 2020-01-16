#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	//... Setup General
	srand(time(0));
	ofDisableArbTex();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("Princess Schnabli Ghosty");
	ofSetColor(ofColor::whiteSmoke);
	ofSetSmoothLighting(true);
	ofLoadIdentityMatrix();

	//... Setup Fog
	fog = ofxFog();
	fog.setfogColor(ofColor(100, 180, 180,100));
	fog.setDensity(0.01);
	fog.setFogMode(GL_EXP2);
	fog.setFogStartEnd(900, 1000);
	fog.enable();

	//... Setup Sky - doesnt work :)
	sky.load("skybox.jpeg");
	sky.setAnchorPoint(1, 1);

	//... Setup Ground
	
	ground.set(groundWidth, groundHeight);
	ground.setPosition(0, 0, 0);
	ground.setResolution(2, 2);
	groundTex = new ofTexture();
	ofLoadImage(*groundTex, "Ground/groundTex.png");

	generateMipMap(groundTex);

	//... Setup Schnabli
	player = new Schnabli();
	player->setupPlayer(0, 0);
	generateMipMap(player->getTexture());
	
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
		(*i)->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
		(*i)->setPosition(0, 0, 0);
		ofPopMatrix();
	}
	int* arr;
	for (int i = 0; i < 400; i++) {
		arr = spwanPoint();
		addTree(arr[0], arr[1], treeLODmodels, &treeLODtexture);
	}
	checkPlayerChunk(1, 1, 1, 1);

	generateMipMap(treeLODtexture[0]);
	generateMipMap(treeLODtexture[1]);
	generateMipMap(treeLODtexture[2]);

	//... ofCube?
	cube = new Cube();
	cube->setReferenceCam(cam);
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

int* ofApp::spwanPoint() { 
	int spawnpoint[2];
	int vX = (rand() % 2);
	int vY = (rand() % 2);
	spawnpoint[0] = (rand() % 1000)-500;
	spawnpoint[1] = (rand() % 1000)-500;
	return spawnpoint;
}
//--------------------------------------------------------------
void ofApp::addTree(int x, int z, std::vector<ofxAssimpModelLoader*>& LODmodels, std::vector<ofTexture*>* LODtextures) {
	int angle = (z - (rand() % 360)) % 360;
	int numRotation;
	ofPoint axis = ofPoint(0.0, 1.0, 0.0);
	float scalingFactor = ((rand() % 100) + 1) * 0.0003;
	float scaling = 0.04 + scalingFactor;

	for (auto i = LODmodels.begin(); i != LODmodels.end(); i++) {
		numRotation = (*i)->getNumRotations();
		ofPushMatrix();
		(*i)->setScale(scaling,scaling,scaling);
		(*i)->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
		ofPopMatrix();
	}
	if (z > 0 && x < 0) {
		WNChunk.push_back(new Tree(x, z, treeLODmodels, &treeLODtexture,player));
	}
	else if (z > 0 && x > 0) {
		NOChunk.push_back(new Tree(x, z, treeLODmodels, &treeLODtexture,player));
	}
	else if (z < 0 && x>0) {
		OSChunk.push_back(new Tree(x, z, treeLODmodels, &treeLODtexture,player));
	}
	else if (z < 0 && x < 0) {
		SWChunk.push_back(new Tree(x, z, treeLODmodels, &treeLODtexture,player));
	}
}

void ofApp::update() {
	idleCount++;
	if (idleCount > 600 && !isMoving) {
		player->setAnimationState("SPECIAL");
		idleCount = 0;
	}
	if(!isMoving)
		player -> checkeSpecialMove();
	player->getPlayer()->update();
	if (camBounded) {
		ofPushMatrix();
		cam->setPosition(player->getPlayer()->getPosition().x, player->getPlayer()->getPosition().y +camOffsetY, player->getPlayer()->getPosition().z-camOffsetZ);
		ofPopMatrix();
	}
	LODCount--;
	if (LODCount < 0) {
		int z = player->getPlayer()->getPosition().z;
		int x = player->getPlayer()->getPosition().x;

		if ( z<= -100 && x <= -100) {
			checkPlayerChunk(0, 0, 1, 0);
		}
		else if (z<=-100 && x>-100 && x <= 100) {
			checkPlayerChunk(0, 1, 1, 0);
		}
		else if (z <= -100 && x > 100) {
			checkPlayerChunk(0, 1, 0, 0);
		}
		else if (z > -100 && z <= 100 && x <= 100) {
			checkPlayerChunk(0, 0, 1, 1);
		}
		else if (z > -100 && z <= 100 && x > -100 && x <= 100) {
			checkPlayerChunk(1, 1, 1, 1);
		}
		else if (z > -100 && z <= 100 && x > 100) {
			checkPlayerChunk(1, 1, 0, 0);
		}
		else if (z > 100 && x <= -100) {
			checkPlayerChunk(0, 0, 0, 1);
		}
		else if (z > 100 && x > -100 && x <= 100) {
			checkPlayerChunk(1, 0, 0, 1);
		}
		else if (z > 100 && x > 100) {
			checkPlayerChunk(1, 0, 0, 0);
		}
		//checkPlayerChunk(1, 1, 1, 1);
		
		
		LODCount = 30;
	}
	cube->sortCube();

}
void ofApp::checkPlayerChunk(bool NO, bool OS, bool SW, bool WN) {
	if (NO) {
		for (auto i = NOChunk.begin(); i != NOChunk.end(); i++) {
			(*i)->checkLOD();
		}
	}
	if (OS) {
		for (auto i = OSChunk.begin(); i != OSChunk.end(); i++) {
			(*i)->checkLOD();
		}
	}
	if (SW) {
		for (auto i = SWChunk.begin(); i != SWChunk.end(); i++) {
			(*i)->checkLOD();
		}
	}
	if (WN) {
		for (auto i = WNChunk.begin(); i != WNChunk.end(); i++) {
			(*i)->checkLOD();
		}
	}
}

//--------------------------------------------------------------


void ofApp::draw(){

	ofEnableLighting();

	glDisable(GL_DEPTH_TEST);
	sky.draw(1, 1);
	glEnable(GL_DEPTH_TEST);

	spotlight.enable();
	//pointlight.enable();

	cam->begin();
	ofDrawGrid();
	glEnable(GL_NORMALIZE);

	ofPushMatrix();
	ofRotateXDeg(90);
	groundTex->bind();
	ground.draw();
	groundTex->unbind();
	ofPopMatrix();

	//... Player 

	player->getTexture()->bind();
	player->getPlayer()->drawFaces();
	player->getTexture()->unbind();

	

	for (auto i = NOChunk.begin(); i != NOChunk.end(); i++) {
		(*i)->getTreeTexture()->bind();
		(*i)->getTreeModel()->drawFaces();
		(*i)->getTreeTexture()->unbind();
	}
	for (auto i = OSChunk.begin(); i != OSChunk.end(); i++) {
		(*i)->getTreeTexture()->bind();
		(*i)->getTreeModel()->drawFaces();
		(*i)->getTreeTexture()->unbind();
	}
	for (auto i = SWChunk.begin(); i != SWChunk.end(); i++) {
		(*i)->getTreeTexture()->bind();
		(*i)->getTreeModel()->drawFaces();
		(*i)->getTreeTexture()->unbind();
	}
	for (auto i = WNChunk.begin(); i != WNChunk.end(); i++) {
		(*i)->getTreeTexture()->bind();
		(*i)->getTreeModel()->drawFaces();
		(*i)->getTreeTexture()->unbind();
	}

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
	else if (key == 'd') {
		ofPoint position = player->getPlayer()->getPosition();
		position.x += player->getMSFoward();

		movePlayer(position);
		if (!player->IsRotated()) {
			rotatePlayer(1);
			player->setAnimationState("WALK");
		}
		isMoving = true;
	}
	else if (key == 'a') {
		ofPoint position = player->getPlayer()->getPosition();
		position.x -= player->getMSFoward();

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
	//TODO FIX BUG ROTATION SUCKS
	int angle = getRightRotation(position);
	ofPoint axis = ofPoint(0.0, 0.0, 1.0);
	int numRotation;
	for (auto i = player->getModels().begin(); i != player->getModels().end(); i++) {
			numRotation = (*i)->getNumRotations();
		ofPushMatrix();
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
			(playerPosition == 2) ? angle = 180 :
			angle = -270;
		break;
	case 1:
		(playerPosition == 0) ? angle = 90 :
			(playerPosition == 1) ? angle = 0 :
			(playerPosition == 2) ? angle = -90 :
			angle = 180;
		break;
	case 2:
		(playerPosition == 0) ? angle = 180 :
			(playerPosition == 1) ? angle = 90 :
			(playerPosition == 2) ? angle = 0 :
			angle = -90;
		break;
	case 3:
		(playerPosition == 0) ? angle = -90 :
			(playerPosition == 1) ? angle = 180 :
			(playerPosition == 2) ? angle = 90 :
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
	if (key == 'f') {
		if (isFog) {
			fog.disable();
			isFog = false;
		}
		else {
			fog.enable();
			isFog = true;
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
	cubeSides[0]->setPosition(2.5, 5, 0);
	cubeSides[0]->setResolution(2, 2);
	cubeSides[0]->enableColors();
	cubeSides[0]->rotateDeg(90, 0, 1, 0);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[1]->set(5, 5);
	cubeSides[1]->setPosition(-2.5, 5, 0);
	cubeSides[1]->setResolution(2, 2);
	cubeSides[1]->enableColors();
	cubeSides[1]->rotateDeg(-90, 0, 1, 0);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[2]->set(5, 5);
	cubeSides[2]->setPosition(0, 7.5, 0);
	cubeSides[2]->setResolution(2, 2);
	cubeSides[2]->enableColors();
	cubeSides[2]->rotateDeg(90, 1, 0, 0);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[3]->set(5, 5);
	cubeSides[3]->setPosition(0, 2.5, 0);
	cubeSides[3]->setResolution(2, 2);
	cubeSides[3]->enableColors();
	cubeSides[3]->rotateDeg(-90, 1, 0, 0);
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[4]->set(5, 5);
	cubeSides[4]->setPosition(0, 5,2.5);
	cubeSides[4]->setResolution(2, 2);
	cubeSides[4]->enableColors();
	ofPopMatrix();

	ofPushMatrix();
	cubeSides[5]->set(5, 5);
	cubeSides[5]->setPosition(0, 5, -2.5);
	cubeSides[5]->setResolution(2, 2);
	cubeSides[5]->enableColors();
	cubeSides[5]->rotateDeg(180, 0, 1, 0);
	ofPopMatrix();

}
void ofApp::Cube::setReferenceCam(ofEasyCam* camRef) {
	cam = camRef;
}
void ofApp::Cube::sortCube() {
	for (int i = 0; i < cubeSides.size() - 1; i++) {
		for (int j = 0; j < cubeSides.size() - i - 1; j++) {
			ofVec3f cPos1 = cubeSides[j]->getPosition();
			ofVec3f cPos2 = cubeSides[j + 1]->getPosition();
			if (cPos1.squareDistance(cam->getPosition()) < cPos2.squareDistance(cam->getPosition())) {
				std::swap(cubeSides[j], cubeSides[j + 1]);
			}
		}
	}

}
void ofApp::Cube::drawCube() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ofSetColor(ofColor(255, 0, 200, 90));
	cubeSides[0]->drawFaces();
	cubeSides[1]->drawFaces();
	cubeSides[2]->drawFaces();
	cubeSides[3]->drawFaces();
	cubeSides[4]->drawFaces();
	cubeSides[5]->drawFaces();
	glDisable(GL_BLEND);
	ofSetColor(ofColor::whiteSmoke);

}
