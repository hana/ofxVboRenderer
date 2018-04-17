//
//  VboCircle.cpp
//  vboCircle
//
//  Created by Hana on 2018/01/22.
//
//

#include "VboCircleRenderer.hpp"

constexpr float M_2XPI = M_PI * 2.0;

VboCircleRenderer::VboCircleRenderer() {
    lineWidth = 4.0;
}

void VboCircleRenderer::setup() {
    setScreenSize();
    baseRad = width;
    
    initVbo();
}

void VboCircleRenderer::setup(float w, float h) {
    setScreenSize(w, h);
    baseRad = width;
    
    initVbo();
}

void VboCircleRenderer::setScreenSize() {
    width = ofGetWidth();
    height = ofGetHeight();
}

void VboCircleRenderer::setScreenSize(float w, float h) {
    width = w;
    height = h;
}

void VboCircleRenderer::setColor(ofFloatColor _color) {
    color = _color;
}

void VboCircleRenderer::setColor(float c) {
    color = ofFloatColor(c, c, c);
}

void VboCircleRenderer::initVbo() {
    filledCircleVbo.setVertexData(filledCirclePos, VERTICES_MAX, GL_DYNAMIC_DRAW);
    filledCircleVbo.setIndexData(filledCircleIndices, VERTICES_MAX, GL_DYNAMIC_DRAW);
    filledCircleVbo.setColorData(filledCircleColors, VERTICES_MAX, GL_DYNAMIC_DRAW);
    
    noFillCircleVbo.setVertexData(noFillCirclePos, VERTICES_MAX, GL_DYNAMIC_DRAW);
    noFillCircleVbo.setIndexData(noFillCircleIndices, VERTICES_MAX, GL_DYNAMIC_DRAW);
    noFillCircleVbo.setColorData(noFillCircleColors, VERTICES_MAX, GL_DYNAMIC_DRAW);
}

void VboCircleRenderer::setBaseRad(int _baseRad) {
    baseRad = _baseRad;
}

void VboCircleRenderer::draw() {
    filledCircleVbo.updateVertexData(filledCirclePos, filledCounter.vertex);
    filledCircleVbo.updateIndexData(filledCircleIndices, filledCounter.index);
    filledCircleVbo.updateColorData(filledCircleColors, filledCounter.color);
    
    filledCircleVbo.drawElements(GL_TRIANGLES ,  filledCounter.index);
    
    glLineWidth(lineWidth);
    noFillCircleVbo.updateVertexData(noFillCirclePos, noFillCounter.vertex);
    noFillCircleVbo.updateIndexData(noFillCircleIndices, noFillCounter.index);
    noFillCircleVbo.updateColorData(noFillCircleColors, noFillCounter.color);
    
    noFillCircleVbo.drawElements(GL_LINES, noFillCounter.index);
    
    resetCounter();
}

void VboCircleRenderer::circle(float x, float y, float size, bool fill) {
    if(fill) {
        filledCircle(x, y, size);
    } else {
        noFillCircle(x, y, size);
    }
}


void VboCircleRenderer::filledCircle(float x, float y, float size) {
    
    int res = getResolution(size);
    float oneStep = M_2XPI / res;
    int baseIndex = filledCounter.vertex;
    
    //Set Center vertex
    ofVec2f center = ofVec2f(x * width, y * height);
    addVertex(true, center);  //Add Center first
    addColor(true, color);
    
    float rad = 0;
    ofVec2f pos;
    for(int i = 0; i < res; i++) {
        rad = oneStep * i;
        pos = getVertPos(x, y, rad, size);
        addVertex(true, pos);
        //cout << "Vertex :" << pos << endl;
        
        //Center Vertex
        addIndex(true, baseIndex);
        addColor(true, color);
        
        //First
        addIndex(true, baseIndex + i + 1);
        addColor(true, color);
        
        //Second
        if(i == (res - 1)) {
            addIndex(true, baseIndex + 1);
            addColor(true, color);
        } else {
            addIndex(true, baseIndex + i + 2);
            addColor(true, color);
        }
    }
}


void VboCircleRenderer::noFillCircle(float x, float y, float size) {
    int res = getResolution(size);
    
    float oneStep = M_2XPI / res;
    int baseIndex = noFillCounter.vertex;
    
    float rad = 0;
    ofVec2f pos;
    for(int i = 0; i < res; i++) {
        rad = oneStep * i;
        pos = getVertPos(x, y, rad, size);
        addVertex(false, pos); //put into base index
        
        //This Vertex
        addIndex(false, baseIndex + i);
        addColor(false, color);
        
        //Second
        if(i == (res - 1)) {
            addIndex(false, baseIndex);
            addColor(false, color);
        } else {
            addIndex(false, baseIndex + i + 1);
            addColor(false, color);
        }
    }
}


ofVec2f VboCircleRenderer::getVertPos(float centerX, float centerY, float rad, float size) {
    
//    float x = cos(rad) * size * width; //Get Circle track X
//    float y = sin(rad) * size * width; //Get Circle track Y

    float x = cos(rad) * size * baseRad; //Get Circle track X
    float y = sin(rad) * size * baseRad; //Get Circle track Y
    
    float px = centerX * width + x;     //Get position X
    float py = centerY * height + y;    //Get position
    
    return ofVec2f(px, py);
}

int VboCircleRenderer::getResolution(float size) {  //Set resolution depening on circle size
    int resolution = 120;
    if(1.0 <= size)  resolution = 120;
    else if (0.5 <= size && size < 1.0) resolution = 90;
    else if (0.3 <= size && size < 0.5) resolution = 60;
    else if (0.1 <= size && size < 0.3) resolution = 45;
    else if (0.05 <= size && size < 0.1) resolution = 30;
    else resolution = 15;
    
    return resolution;
}


void VboCircleRenderer::addVertex(bool isFilled, ofVec2f pos) {
    if(isFilled){
        filledCirclePos[filledCounter.vertex] = pos;
        filledCounter.vertex++;
    }else{
        noFillCirclePos[noFillCounter.vertex] = pos;
        noFillCounter.vertex++;

    }
}

void VboCircleRenderer::addColor(bool isFilled, ofFloatColor color) {
    if(isFilled){
        filledCircleColors[filledCounter.color] = color;
        filledCounter.color++;
    }else{
        noFillCircleColors[noFillCounter.color] = color;
        noFillCounter.color++;
    }
}

void VboCircleRenderer::addIndex(bool isFilled, ofIndexType index) {
    if(isFilled){
        filledCircleIndices[filledCounter.index] = index;
        filledCounter.index++;

    }else{
        noFillCircleIndices[noFillCounter.index] = index;
        noFillCounter.index++;
    }
}

void VboCircleRenderer::resetCounter() {
    noFillCounter.vertex = 0;
    noFillCounter.index = 0;
    noFillCounter.color = 0;
    
    filledCounter.vertex = 0;
    filledCounter.index = 0;
    filledCounter.color = 0;
}
