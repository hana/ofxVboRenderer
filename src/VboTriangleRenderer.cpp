//
//  VboTriangleRenderer.cpp
//  vboRendererDev
//
//  Created by Momoha Matsuhashi on 2018/04/16.
//
//

#include "VboTriangleRenderer.hpp"

constexpr double ROOT_3 = 1.73205;
constexpr double ROOT_3_DIV_3 = 0.57735;
constexpr double ROOT_3_DIV_6 = 0.288675;

VboTriangleRenderer::VboTriangleRenderer() {
    lineWidth = 4.0;
}

void VboTriangleRenderer::setup() {
    setScreenSize();
    
    initVbo();
}

void VboTriangleRenderer::setup(float w, float h) {
    setScreenSize(w, h);
    
    initVbo();
}

void VboTriangleRenderer::setScreenSize() {
    width = ofGetWidth();
    height = ofGetHeight();
}

void VboTriangleRenderer::setScreenSize(float w, float h) {
    width = w;
    height = h;
}

void VboTriangleRenderer::setColor(ofFloatColor _color) {
    color = _color;
}

void VboTriangleRenderer::setColor(float brightness, float alpha) {
    color = ofFloatColor(brightness, alpha);
}

void VboTriangleRenderer::initVbo() {
    filledTriangleVbo.setVertexData(filledTrianglePos, VBOTRIGANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    filledTriangleVbo.setIndexData(filledTriangleIndices, VBOTRIGANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    filledTriangleVbo.setColorData(filledTriangleColors, VBOTRIGANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    
    noFillTriangleVbo.setVertexData(noFillTrianglePos, VBOTRIGANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    noFillTriangleVbo.setIndexData(noFillTriangleIndices, VBOTRIANGLE_INDICES_MAX, GL_DYNAMIC_DRAW);
    noFillTriangleVbo.setColorData(noFillTriangleColors, VBOTRIGANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
}

void VboTriangleRenderer::draw() {
    filledTriangleVbo.updateVertexData(filledTrianglePos, filledCounter.vertex);
    filledTriangleVbo.updateIndexData(filledTriangleIndices, filledCounter.index);
    filledTriangleVbo.updateColorData(filledTriangleColors, filledCounter.color);
    
    filledTriangleVbo.drawElements(GL_TRIANGLES,  filledCounter.index);
    
    glLineWidth(lineWidth);
    noFillTriangleVbo.updateVertexData(noFillTrianglePos, noFillCounter.vertex);
    noFillTriangleVbo.updateIndexData(noFillTriangleIndices, noFillCounter.index);
    noFillTriangleVbo.updateColorData(noFillTriangleColors, noFillCounter.color);
    
    noFillTriangleVbo.drawElements(GL_LINES, noFillCounter.index);
    
    resetCounter();
}

void VboTriangleRenderer::triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool fill){
    if(fill) {
        fillTriangle(x1, y1, x2, y2, x3, y3);
    } else {
        noFillTriangle(x1, y1, x2, y2, x3, y3);
    }
}

void VboTriangleRenderer::triangle(float x, float y, float size, float angle, bool fill) {
    //Prepare Variables
    float scaledSize = width * size;
    
    //Culcrate relative pos on each vert from size
    center.set(x * width, y * height);
    normalizedTop.set(0, -ROOT_3_DIV_3);
    normalizedLeft.set(-0.5, ROOT_3_DIV_6);
    normalizedRight.set(0.5, ROOT_3_DIV_6);
    
    //Rotate
    normalizedTop.rotate(360 * angle);
    normalizedLeft.rotate(360 * angle);
    normalizedRight.rotate(360 * angle);
    
    //Get absolute pos on each vertex
    top = normalizedTop * scaledSize + center;
    left = normalizedLeft * scaledSize + center;
    right = normalizedRight * scaledSize + center;
    
    if (fill) {
        filledTriangle(top, left, right);
    } else {
        noFilledTriangle(top, left, right);
    }

}

void VboTriangleRenderer::filledTriangle(ofVec2f p1, ofVec2f p2, ofVec2f p3) {
    
    addVertex(true, p1);
    addIndex(true, filledCounter.index);
    addColor(true, color);
    
    addVertex(true, p2);
    addIndex(true, filledCounter.index);
    addColor(true, color);
    
    addVertex(true, p3);
    addIndex(true, filledCounter.index);
    addColor(true, color);

}

void VboTriangleRenderer::fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    
    ofVec2f pos[] = {ofVec2f(x1, y1), ofVec2f(x2, y2), ofVec2f(x3, y3)};
    
    for(int i = 0; i < 3; i++){
        addVertex(true, pos[i] * ofVec2f(width, height));
        addIndex(true, filledCounter.index);
        addColor(true, color);
    }
}

void VboTriangleRenderer::noFilledTriangle(ofVec2f p1, ofVec2f p2, ofVec2f p3)  {
    addVertex(false, p1);
    addColor(false, color);
    
    addVertex(false, p2);
    addColor(false, color);
    
    addVertex(false, p3);
    addColor(false, color);
    
    
    int vertIDBegin = noFillCounter.vertex;
    
    addIndex(false, vertIDBegin);
    addIndex(false, vertIDBegin+1);
    addIndex(false, vertIDBegin+1);
    addIndex(false, vertIDBegin+2);
    addIndex(false, vertIDBegin+2);
    addIndex(false, vertIDBegin);
}

void VboTriangleRenderer::noFillTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    
    ofVec2f pos[] = {ofVec2f(x1, y1), ofVec2f(x2, y2), ofVec2f(x3, y3)};
    
    for(int i = 0; i < 3; i++){
        addVertex(false, pos[i] * ofVec2f(width, height));
        addColor(false, color);
    }
    
    int vertIDBegin = noFillCounter.vertex;
    
    addIndex(false, vertIDBegin);
    addIndex(false, vertIDBegin+1);
    addIndex(false, vertIDBegin+1);
    addIndex(false, vertIDBegin+2);
    addIndex(false, vertIDBegin+2);
    addIndex(false, vertIDBegin);
}

void VboTriangleRenderer::addVertex(bool isFilled, ofVec2f pos) {
    if(isFilled){
        filledTrianglePos[filledCounter.vertex] = pos;
        filledCounter.vertex++;
    }else{
        noFillTrianglePos[noFillCounter.vertex] = pos;
        noFillCounter.vertex++;
    }
}

void VboTriangleRenderer::addColor(bool isFilled, ofFloatColor color) {
    if(isFilled){
        filledTriangleColors[filledCounter.color] = color;
        filledCounter.color++;
    }else{
        noFillTriangleColors[noFillCounter.color] = color;
        noFillCounter.color++;
    }
}

void VboTriangleRenderer::addIndex(bool isFilled, ofIndexType index) {
    if(isFilled){
        filledTriangleIndices[filledCounter.index] = index;
        filledCounter.index++;
    }else{
        noFillTriangleIndices[noFillCounter.index] = index;
        noFillCounter.index++;
    }
}

void VboTriangleRenderer::resetCounter() {
    noFillCounter.vertex = 0;
    noFillCounter.index = 0;
    noFillCounter.color = 0;
    
    filledCounter.vertex = 0;
    filledCounter.index = 0;
    filledCounter.color = 0;
}
