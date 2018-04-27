#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);


    renderer.setup();
    renderer.setColor(1.0);
    angle = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

    renderer.setColor(1.0);
    renderer.circle(0.25, 0.25, 0.1, true);   // x, y, diameter, fill
    renderer.line(0.8, 0.2, 0.8, 0.8, 0.01);    // x1, y1, x2, y2, thick
    renderer.triangle(0.5, 0.25, 0.1, angle, false); //x, y, size, angle, fill
    
    renderer.setColor(1.0, 0.0, 0.0, 0.5);  //rgba
    renderer.square(0.5, 0.75, 0.1, angle, false);   //x, y, size, angle, fill
    
    ofVec2f pos = ofVec2f(0.25, 0.75);
    renderer.rect(pos, 0.1, 0.05, angle, true);  //center, width, height, fill
//    renderer.rect(0.35, 0.8, 0.4, 0.9, angle, false);   //x1, y1, x2, y2, angle, fill
    
    angle += 0.01;
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
