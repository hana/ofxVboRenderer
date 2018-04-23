//
//  ofxVboRenderer.cpp
//  ofxVboRenderer
//
//  Created by Hana on 2018/01/24.
//
//

#include "ofxVboRenderer.hpp"

ofxVboRenderer::ofxVboRenderer() {

}

void ofxVboRenderer::setup() {
    circleRenderer.setup();
    lineRenderer.setup();
    triangleRenderer.setup();
}

void ofxVboRenderer::setup(float w, float h) {
    circleRenderer.setup(w, h);
    lineRenderer.setup(w, h);
    triangleRenderer.setup(w, h);
}


void ofxVboRenderer::setScreenSize() {
    circleRenderer.setScreenSize();
    lineRenderer.setScreenSize();
    triangleRenderer.setScreenSize();
}

void ofxVboRenderer::setScreenSize(float w, float h) {
    circleRenderer.setScreenSize(w, h);
    lineRenderer.setScreenSize(w, h);
    triangleRenderer.setScreenSize(w, h);
}

void ofxVboRenderer::setColor(float brightness, float alpha) {
    circleRenderer.setColor(brightness, alpha);
    lineRenderer.setColor(brightness, alpha);
    triangleRenderer.setColor(brightness, alpha);
}

void ofxVboRenderer::setColor(float red, float green, float blue, float alpha) {
    colorBuffer = ofFloatColor(red, green, blue, alpha);
    circleRenderer.setColor(colorBuffer);
    lineRenderer.setColor(colorBuffer);
    triangleRenderer.setColor(colorBuffer);
}

void ofxVboRenderer::setColor(ofFloatColor c) {
    circleRenderer.setColor(c);
    lineRenderer.setColor(c);
    triangleRenderer.setColor(c);
}


void ofxVboRenderer::setCircleBaseRad(int baseRad) {
    circleRenderer.setBaseRad(baseRad);
}

void ofxVboRenderer::draw() {
    circleRenderer.draw();
    lineRenderer.draw();
    triangleRenderer.draw();
}

void ofxVboRenderer::circle(float x, float y, float size, bool fill) {
    circleRenderer.circle(x, y, size, fill);
}

void ofxVboRenderer::line(float x1, float y1, float x2, float y2, float _thick) {
    lineRenderer.line(x1, y1, x2, y2, _thick);
}

void ofxVboRenderer::triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool fill){
    triangleRenderer.triangle(x1, y1, x2, y2, x3, y3, fill);
}


