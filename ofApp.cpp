#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofNoFill();
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 450, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	float noise_seed_x = ofRandom(1000);
	float noise_seed_y = ofRandom(1000);

	string word = "A";
	auto path_list = this->font.getStringAsPoints(word, true, false);
	for (int point_index = 0; point_index < path_list.size(); point_index++) {

		auto outline = path_list[point_index].getOutline();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(300);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, vertices[vertices_index].y + this->font.stringHeight(word) * 0.5, 0);
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, ofGetFrameNum() * 0.008 + location.y * 0.0005), 0, 1, -PI, PI), glm::vec3(0, 1, 0));

				location = glm::vec4(location, 0) * rotation_y;
				ofVertex(location);
			}
		}
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}