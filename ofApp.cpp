#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	ofColor color;
	vector<int> hex_list = { 0xf44336, 0x9C27B0, 0x3F51B5, 0x03A9F4, 0x009688, 0x8BC34A, 0xFFEB3B, 0xFF9800 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->base_color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int x = 90; x < ofGetWindowWidth(); x += 180) {

		for (int y = 90; y < ofGetWindowHeight(); y += 180) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (int radius = 30; radius < 75; radius += 3) {

				ofMesh face, line;
				line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

				int color_index = ofRandom(this->base_color_list.size());

				int start_deg = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, 0, 360);
				int deg_len = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, -240, 240);

				face.addVertex(glm::vec3());
				face.addColor(ofColor(255, 32));
				for (int deg = start_deg; deg < start_deg + deg_len; deg += 2) {

					face.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
					face.addColor(ofColor(255, 64));

					line.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
					line.addColor(255);

					if (deg != start_deg) {

						face.addIndex(0);
						face.addIndex(face.getNumVertices() - 1);
						face.addIndex(face.getNumVertices() - 2);

						line.addIndex(line.getNumVertices() - 1);
						line.addIndex(line.getNumVertices() - 2);
					}
				}

				face.draw();
				line.draw();
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}