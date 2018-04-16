#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    
    
    renderer.setup();
    renderer.setColor(1.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    renderer.setColor(1.0, 1.0, 1.0, ofRandom(1.0));  //Alpha is normally enabled
    renderer.circle(0.2, 0.5, 0.1, true);   // x, y, size, fill
    
    renderer.setColor(1.0);
    renderer.line(0.8, 0.2, 0.8, 0.8, 0.01);    // x1, y1, x2, y2, thick
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    renderer.draw();
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
