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
    baseDiameter = width;
    
    initVbo();
}

void VboCircleRenderer::setup(float w, float h) {
    setScreenSize(w, h);
    baseDiameter = width;
    
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

void VboCircleRenderer::setColor(float brightness, float alpha) {
    color = ofFloatColor(brightness, alpha);
}

void VboCircleRenderer::initVbo() {
    filledVbo.setVertexData(filledPos, VBOCIRCLE_VERTICES_MAX, GL_DYNAMIC_DRAW);
    filledVbo.setIndexData(filledIndices, VBOCIRCLE_VERTICES_MAX, GL_DYNAMIC_DRAW);
    filledVbo.setColorData(filledColors, VBOCIRCLE_VERTICES_MAX, GL_DYNAMIC_DRAW);
    
    noFillVbo.setVertexData(noFillPos, VBOCIRCLE_VERTICES_MAX, GL_DYNAMIC_DRAW);
    noFillVbo.setIndexData(noFillIndices, VBOCIRCLE_VERTICES_MAX, GL_DYNAMIC_DRAW);
    noFillVbo.setColorData(noFillColors, VBOCIRCLE_VERTICES_MAX, GL_DYNAMIC_DRAW);
}


void VboCircleRenderer::draw() {
    filledVbo.updateVertexData(filledPos, filledCounter.vertex);
    filledVbo.updateIndexData(filledIndices, filledCounter.index);
    filledVbo.updateColorData(filledColors, filledCounter.color);
    
    filledVbo.drawElements(GL_TRIANGLES, filledCounter.index);
    
    glLineWidth(lineWidth);
    noFillVbo.updateVertexData(noFillPos, noFillCounter.vertex);
    noFillVbo.updateIndexData(noFillIndices, noFillCounter.index);
    noFillVbo.updateColorData(noFillColors, noFillCounter.color);
    
    noFillVbo.drawElements(GL_LINES, noFillCounter.index);
    
    resetCounter();
}

void VboCircleRenderer::circle(float x, float y, float diameter, bool fill) {
    if(fill) {
        filled(x, y, diameter);
    } else {
        noFill(x, y, diameter);
    }
}


void VboCircleRenderer::filled(float x, float y, float diameter) {
    
    int res = getResolution(diameter);
    float oneStep = M_2XPI / res;
    int baseIndex = filledCounter.vertex;
    
    //Set Center vertex
    ofVec2f center = ofVec2f(x * width, y * height);
    addVertex(true, center);
    addColor(true, color);
    
    float rad = 0;
    ofVec2f pos;
    for(int i = 0; i < res; i++) {
        rad = oneStep * i;
        pos = getVertPos(x, y, rad, diameter);
        addVertex(true, pos);
        
        
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


void VboCircleRenderer::noFill(float x, float y, float diameter) {
    int res = getResolution(diameter);
    
    float oneStep = M_2XPI / res;
    int baseIndex = noFillCounter.vertex;
    
    float rad = 0;
    ofVec2f pos;
    for(int i = 0; i < res; i++) {
        rad = oneStep * i;
        pos = getVertPos(x, y, rad, diameter);
        addVertex(pos, false); //put into base index
        
        //This Vertex
        addIndex(baseIndex + i, false);
        addColor(color, false);
        
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


ofVec2f VboCircleRenderer::getVertPos(float centerX, float centerY, float rad, float diameter) {
    
    //    float x = cos(rad) * size * width; //Get Circle track X
    //    float y = sin(rad) * size * width; //Get Circle track Y
    
    float x = cos(rad) * diameter * baseDiameter * 0.5; //Get Circle track X
    float y = sin(rad) * diameter * baseDiameter * 0.5; //Get Circle track Y
    
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
    if(isFilled) {
        filledPos[filledCounter.vertex] = pos;
        filledCounter.vertex++;
    } else {
        noFillPos[noFillCounter.vertex] = pos;
        noFillCounter.vertex++;
    }
    
}

void VboCircleRenderer::addColor(bool isFilled, ofFloatColor _color) {
    if (isFilled) {
        filledColors[filledCounter.color] = _color;
        filledCounter.color++;
    } else {
        noFillColors[noFillCounter.color] = _color;
        noFillCounter.color++;
    }
    
}

void VboCircleRenderer::addIndex(bool isFilled, ofIndexType index) {
    if (isFilled) {
        filledIndices[filledCounter.index] = index;
        filledCounter.index++;
    } else {
        noFillIndices[noFillCounter.index] = index;
        noFillCounter.index++;
    }
}

//
void VboCircleRenderer::addVertex(ofVec2f pos, bool isFilled) {
    if(isFilled) {
        filledPos[filledCounter.vertex] = pos;
        filledCounter.vertex++;
    } else {
        noFillPos[noFillCounter.vertex] = pos;
        noFillCounter.vertex++;
    }
    
}

void VboCircleRenderer::addColor(ofFloatColor _color, bool isFilled) {
    if (isFilled) {
        filledColors[filledCounter.color] = _color;
        filledCounter.color++;
    } else {
        noFillColors[noFillCounter.color] = _color;
        noFillCounter.color++;
    }
    
}

void VboCircleRenderer::addIndex(ofIndexType index, bool isFilled) {
    if (isFilled) {
        filledIndices[filledCounter.index] = index;
        filledCounter.index++;
    } else {
        noFillIndices[noFillCounter.index] = index;
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
