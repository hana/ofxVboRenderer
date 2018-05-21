//
//  ofxVboRenderer.cpp
//  ofxVboRenderer
//
//  Created by Hana on 2018/01/24.
//
//

#include "ofxVboRenderer.hpp"

void ofxVboRenderer::setup() {
    circleRenderer.setup();
    lineRenderer.setup();
    triangleRenderer.setup();
    rectangleRenderer.setup();
    arcRenderer.setup();
    waveRenderer.setup();
}

void ofxVboRenderer::setup(float w, float h) {
    circleRenderer.setup(w, h);
    lineRenderer.setup(w, h);
    triangleRenderer.setup(w, h);
    rectangleRenderer.setup(w, h);
    arcRenderer.setup(w, h);
    waveRenderer.setup(w, h);
}


void ofxVboRenderer::setScreenSize() {
    circleRenderer.setScreenSize();
    lineRenderer.setScreenSize();
    triangleRenderer.setScreenSize();
    rectangleRenderer.setScreenSize();
    arcRenderer.setScreenSize();
    waveRenderer.setScreenSize();
}

void ofxVboRenderer::setScreenSize(float w, float h) {
    circleRenderer.setScreenSize(w, h);
    lineRenderer.setScreenSize(w, h);
    triangleRenderer.setScreenSize(w, h);
    rectangleRenderer.setScreenSize(w, h);
    arcRenderer.setScreenSize(w, h);
    waveRenderer.setup(w, h);
}

void ofxVboRenderer::setColor(float brightness, float alpha) {
    circleRenderer.setColor(brightness, alpha);
    lineRenderer.setColor(brightness, alpha);
    triangleRenderer.setColor(brightness, alpha);
    rectangleRenderer.setColor(brightness, alpha);
    arcRenderer.setColor(brightness, alpha);
    waveRenderer.setColor(brightness, alpha);
}

void ofxVboRenderer::setColor(float red, float green, float blue, float alpha) {
    colorBuffer = ofFloatColor(red, green, blue, alpha);
    circleRenderer.setColor(colorBuffer);
    lineRenderer.setColor(colorBuffer);
    triangleRenderer.setColor(colorBuffer);
    rectangleRenderer.setColor(colorBuffer);
    arcRenderer.setColor(colorBuffer);
    waveRenderer.setColor(colorBuffer);
}

void ofxVboRenderer::setColor(ofFloatColor c) {
    circleRenderer.setColor(c);
    lineRenderer.setColor(c);
    triangleRenderer.setColor(c);
    rectangleRenderer.setColor(c);
    arcRenderer.setColor(c);
    waveRenderer.setColor(c);
}


void ofxVboRenderer::setCircleBaseDiameter(int baseDiameter) {
    circleRenderer.setBaseDiameter(baseDiameter);
}

void ofxVboRenderer::draw() {
    ofEnableAlphaBlending();
    circleRenderer.draw();
    lineRenderer.draw();
    triangleRenderer.draw();
    rectangleRenderer.draw();
    arcRenderer.draw();
    waveRenderer.draw();
}

void ofxVboRenderer::circle(float x, float y, float diameter, bool fill) {
    circleRenderer.circle(x, y, diameter, fill);
}

void ofxVboRenderer::line(float x1, float y1, float x2, float y2, float _thick) {
    lineRenderer.line(x1, y1, x2, y2, _thick);
}

void ofxVboRenderer::triangle(float x, float y, float size, float angle, bool fill)  {
    triangleRenderer.triangle(x, y, size, angle, fill);
}

void ofxVboRenderer::triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool fill){
    triangleRenderer.triangle(x1, y1, x2, y2, x3, y3, fill);
}

void ofxVboRenderer::square(float x, float y, float size, float angle, bool fill) {
    rectangleRenderer.square(x, y, size, angle, fill);
}

void ofxVboRenderer::rect(float x1, float y1, float x2, float y2, float  angle, bool fill) {
    rectangleRenderer.rectangle(x1, y1, x2, y2, angle, fill);
}

void ofxVboRenderer::rect(ofVec2f pos, float w, float h, float angle, bool fill) {
    rectangleRenderer.rectangle(pos, w, h, angle, fill);
}

void ofxVboRenderer::arc(float x1, float y1, float x2, float y2, float arcHeight, float expose, float thick) {
    arcRenderer.arc(x1, y1, x2, y2, arcHeight, expose, thick);
}

void ofxVboRenderer::wave(float x1, float y1, float x2, float y2, float freq, float amplitude, float phase, float thick) {
    waveRenderer.wave(x1, y1, x2, y2, freq, amplitude, phase, thick);
}
