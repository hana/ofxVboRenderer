//
//  VboLineRenderer.cpp
//  vboCircle
//
//  Created by Hana on 2018/01/23.
//
//

#include "VboLineRenderer.hpp"

VboLineRenderer::VboLineRenderer() {
    thick = 1.0;
    color = 0.0;
    
}

void VboLineRenderer::setup() {
    setScreenSize();
    
    initVbo();
    initCount();
}

void VboLineRenderer::setup(float w, float h) {
    setScreenSize(w, h);
    
    initVbo();
}

void VboLineRenderer::setScreenSize() {
    width = ofGetWidth();
    height = ofGetHeight();
}

void VboLineRenderer::setScreenSize(float w, float h) {
    width = w;
    height = h;
}

void VboLineRenderer::setColor(float brightness, float alpha) {
    color = ofFloatColor(brightness, alpha);
}

void VboLineRenderer::setColor(ofFloatColor c) {
    color = c;
}


void VboLineRenderer::initVbo() {
    vbo.setVertexData(vertices, VBOLINE_VERTS_MAX, GL_DYNAMIC_DRAW);
    vbo.setColorData(colors, VBOLINE_VERTS_MAX, GL_DYNAMIC_DRAW);
    vbo.setIndexData(indices, VBOLINE_INDICES_MAX, GL_DYNAMIC_DRAW);
}

void VboLineRenderer::initCount() {
    lineCount = 0;
    vertsCount = 0;
    indicesCount = 0;
}

void VboLineRenderer::line(float x1, float y1, float x2, float y2, float _thick) {
    lineCount++;
    
    //Get start and end points and vector
    start = this->getPosition(x1, y1);
    end = this->getPosition(x2, y2);
    ofVec2f vec = start - end;
    ofVec2f normalized = vec.getNormalized();
    ofVec2f w = normalized.getRotatedRad(PI * 0.5) * _thick * 0.5 * width;
    
    
    //Get pos of each corner
    s1 = start + w;
    s2 = start - w;
    e1 = end + w;
    e2 = end - w;
    
    
    //Add verts into array
    addVertex(s1);
    addVertex(s2);
    addVertex(e1);
    addVertex(e2);
    
    addLineIndices();
}


void VboLineRenderer::draw() {
    //update vbo
    vbo.updateVertexData(vertices, vertsCount);
    vbo.updateColorData(colors, vertsCount);
    vbo.updateIndexData(indices, indicesCount);
    
    //draw
    vbo.drawElements(GL_TRIANGLES, indicesCount);
    
    //reset
    initCount();
}

void VboLineRenderer::addVertex(ofVec2f pos) {
    vertices[vertsCount] = pos;
    colors[vertsCount] = color;
    vertsCount++;
}

void VboLineRenderer::addIndex(int index) {
    indices[indicesCount] = index;
    indicesCount++;
}

void VboLineRenderer::addIndex(ofIndexType index) {
    indices[indicesCount] = index;
    indicesCount++;
}

void VboLineRenderer::addLineIndices() {
    int vertIDBegin = (lineCount-1) * 4;
    
    //Triangle A
    addIndex(vertIDBegin);
    addIndex(vertIDBegin+1);
    addIndex(vertIDBegin+2);
    
    //Triangle B
    addIndex(vertIDBegin+1);
    addIndex(vertIDBegin+2);
    addIndex(vertIDBegin+3);
    
}

ofVec2f VboLineRenderer::getPosition(float x, float y) {
    ofVec2f pos = ofVec2f(x * width, y * height);
    return pos;
}
