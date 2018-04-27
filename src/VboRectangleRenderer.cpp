//
//  VboRectangleRenderer.cpp
//  example-simple
//
//  Created by Hana on 2018/04/25.
//
//

#include "VboRectangleRenderer.hpp"

VboRectangleRenderer::VboRectangleRenderer() {
    initVbo();
    initCount();
    
    thick = 1.0;
}

void VboRectangleRenderer::setup() {
    setScreenSize();
    initVbo();
}

void VboRectangleRenderer::setup(float w, float h) {
    setScreenSize(w, h);
    initVbo();
}

void VboRectangleRenderer::draw() {
    filledVbo.updateVertexData(filledPos, filledCounter.vertex);
    filledVbo.updateColorData(filledColors, filledCounter.color);
    filledVbo.updateIndexData(filledIndices, filledCounter.index);
    
    filledVbo.drawElements(GL_TRIANGLES, filledCounter.index);
    
    noFillVbo.updateVertexData(noFillPos, noFillCounter.vertex);
    noFillVbo.updateColorData(noFillColors, noFillCounter.color);
    noFillVbo.updateIndexData(noFillIndices, noFillCounter.index);

    glLineWidth(thick);
    noFillVbo.drawElements(GL_LINES, noFillCounter.index);
    
    initCount();
}

void VboRectangleRenderer::square(float x, float y, float size, float angle, bool fill) {
    if (fill) {
        filledSquare(x, y, size, angle);
    } else {
        noFillSquare(x, y, size, angle);
    }
}

void VboRectangleRenderer::square(ofVec2f pos, float size, float angle, float fill) {
    square(pos.x, pos.y, size, angle, fill);
}

void VboRectangleRenderer::filledSquare(float x, float y, float size, float angle) {
    updateVerts(x, y, size, angle);
    addFilledRectangle();
}

void VboRectangleRenderer::noFillSquare(float x, float y, float size, float angle) {
    updateVerts(x, y, size, angle);
    addNoFillRectangle();
    
}

void VboRectangleRenderer::rectangle(float x1, float y1, float x2, float y2, float angle, bool fill)    {
    if(fill) {
        filledRectangle(x1, y1, x2, y2, angle);
    } else {
        noFillRectangle(x1, y1, x2, y2, angle);
    }
}

void VboRectangleRenderer::rectangle(ofVec2f p1, ofVec2f p2, float angle, bool fill) {
    rectangle(p1.x, p1.y, p2.x, p2.y, angle, fill);
}

void VboRectangleRenderer::rectangle(ofVec2f pos, float w, float h, float angle, bool fill) {
    if(fill) {
        filledRectangle(pos, w, h, angle);
    } else {
        noFillRectangle(pos, w, h, angle);
    }
}

void VboRectangleRenderer::filledRectangle(float x1, float y1, float x2, float y2, float angle) {
    updateVerts(x1, y1, x2, y2, angle);
    addFilledRectangle();
}

void VboRectangleRenderer::filledRectangle(ofVec2f pos, float w, float h, float angle) {
    updateVerts(pos, w, h, angle);
    addFilledRectangle();
}

void VboRectangleRenderer::noFillRectangle(float x1, float y1, float x2, float y2, float angle) {
    updateVerts(x1, y1, x2, y2, angle);
    addNoFillRectangle();
}

void VboRectangleRenderer::noFillRectangle(ofVec2f pos, float w, float h, float angle) {
    updateVerts(pos, w, h, angle);
    addNoFillRectangle();
}

void VboRectangleRenderer::initVbo() {
    filledVbo.setVertexData(filledPos, VBORECTANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    filledVbo.setColorData(filledColors, VBORECTANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    filledVbo.setIndexData(filledIndices, VBORECTANGLE_INDICES_MAX, GL_DYNAMIC_DRAW);
    
    noFillVbo.setVertexData(noFillPos, VBORECTANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    noFillVbo.setColorData(noFillColors, VBORECTANGLE_VERTS_MAX, GL_DYNAMIC_DRAW);
    noFillVbo.setIndexData(noFillIndices, VBORECTANGLE_INDICES_MAX, GL_DYNAMIC_DRAW);
}

void VboRectangleRenderer::initCount() {
    filledCounter.vertex = 0;
    filledCounter.color = 0;
    filledCounter.index = 0;
    filledCounter.num = 0;
    
    noFillCounter.vertex = 0;
    noFillCounter.color = 0;
    noFillCounter.index = 0;
    noFillCounter.num = 0;
}

void VboRectangleRenderer::updateVerts(float x, float y, float size, float angle) {
    //Calcurate half size
    tmpLength = width * size * 0.5;
    
    //Create square at center
    verts[0] = ofVec2f(-tmpLength, tmpLength);
    verts[1] = ofVec2f(tmpLength, tmpLength);
    verts[2] = ofVec2f(tmpLength, -tmpLength);
    verts[3] = ofVec2f(-tmpLength, -tmpLength);
    
    //Rotate and move
    tmpAngle = 360 * angle;
    center.set(x * width, y * height);
    for(int i = 0; i < RECTANGLE_VERTS_NUM; i++) {
        verts[i].rotate(tmpAngle);
        verts[i] += center;
    }
}

void VboRectangleRenderer::updateVerts(ofVec2f pos, float size, float angle) {
    updateVerts(pos.x, pos.y, size, angle);
}


void VboRectangleRenderer::updateVerts(float x1, float y1, float x2, float y2, float angle) {
    //Calcurate half width and height
    tmpWidth = width * abs(x2 - x1) * 0.5;
    tmpHeight = height * abs(y2 - y1) * 0.5;
    
    //Create rectangle at center
    verts[0] = ofVec2f(-tmpWidth, tmpHeight);
    verts[1] = ofVec2f(tmpWidth, tmpHeight);
    verts[2] = ofVec2f(tmpWidth, -tmpHeight);
    verts[3] = ofVec2f(-tmpWidth, -tmpHeight);
    
    //Rotate and move
    tmpAngle = 360.0 * angle;
    center.set( (x2 + x1) * width * 0.5, (y2 + y1) * height * 0.5);
    for(int i = 0; i < RECTANGLE_VERTS_NUM; i++) {
        verts[i].rotate(tmpAngle);
        verts[i] += center;
    }
}

void VboRectangleRenderer::updateVerts(ofVec2f p1, ofVec2f p2, float angle) {
    updateVerts(p1.x, p1.y, p2.x, p2.y, angle);
}

void VboRectangleRenderer::updateVerts(ofVec2f pos, float w, float h, float angle) {
    tmpWidth = w * 0.5 * width;
    tmpHeight = h * 0.5 * height;
    
    //Create square at center
    verts[0] = ofVec2f(-tmpWidth, tmpHeight);
    verts[1] = ofVec2f(tmpWidth, tmpHeight);
    verts[2] = ofVec2f(tmpWidth, -tmpHeight);
    verts[3] = ofVec2f(-tmpWidth, -tmpHeight);
    
    //rotate and move
    tmpAngle = 360.0 * angle;
    for(int i = 0; i < RECTANGLE_VERTS_NUM; i++) {
        verts[i].rotate(tmpAngle);
        verts[i].x += pos.x * width;
        verts[i].y += pos.y * height;
    }
}

void VboRectangleRenderer::addVertex(ofVec2f pos, bool filled)  {
    if (filled) {
        addFilledVertex(pos);
    } else {
        addNoFillVertex(pos);
    }
}

void VboRectangleRenderer::addFilledVertex(ofVec2f pos) {
    filledPos[filledCounter.vertex] = pos;
    filledCounter.vertex++;
}

void VboRectangleRenderer::addNoFillVertex(ofVec2f pos) {
    noFillPos[noFillCounter.vertex] = pos;
    noFillCounter.vertex++;
}

void VboRectangleRenderer::addIndex(ofIndexType index, bool filled) {
    if (filled) {
        addFilledIndex(index);
    } else {
        addNoFillIndex(index);
    }
}

void VboRectangleRenderer::addFilledIndex(ofIndexType index) {
    filledIndices[filledCounter.index] = index;
    filledCounter.index++;
}

void VboRectangleRenderer::addNoFillIndex(ofIndexType index) {
    noFillIndices[noFillCounter.index] = index;
    noFillCounter.index++;
}

void VboRectangleRenderer::addColor(ofFloatColor _color, bool filled) {
    if (filled) {
        addFilledColor(_color);
    } else {
        addNoFillColor(_color);
    }
}

void VboRectangleRenderer::addFilledColor(ofFloatColor _color) {
    filledColors[filledCounter.color] = color;
    filledCounter.color++;
}

void VboRectangleRenderer::addNoFillColor(ofFloatColor _color) {
    noFillColors[noFillCounter.color] = color;
    noFillCounter.color++;
}

void VboRectangleRenderer::addFilledRectangle() {
    //Add vertices and color
    for(int i = 0; i < RECTANGLE_VERTS_NUM; i++) {
        addFilledVertex(verts[i]);
        addFilledColor(color);
    }
    
    //Set index;
    addFilledIndex(filledCounter.vertex - 4);
    addFilledIndex(filledCounter.vertex - 3);
    addFilledIndex(filledCounter.vertex - 2);
    addFilledIndex(filledCounter.vertex - 4);
    addFilledIndex(filledCounter.vertex - 2);
    addFilledIndex(filledCounter.vertex - 1);
}

void VboRectangleRenderer::addNoFillRectangle() {
    //Add vertices and color
    for(int i = 0; i < RECTANGLE_VERTS_NUM; i++) {
        addNoFillVertex(verts[i]);
        addNoFillColor(color);
    }
    
    //Set INDEX
    addNoFillIndex(noFillCounter.vertex - 4);
    addNoFillIndex(noFillCounter.vertex - 3);
    addNoFillIndex(noFillCounter.vertex - 3);
    addNoFillIndex(noFillCounter.vertex - 2);
    addNoFillIndex(noFillCounter.vertex - 2);
    addNoFillIndex(noFillCounter.vertex - 1);
    addNoFillIndex(noFillCounter.vertex - 1);
    addNoFillIndex(noFillCounter.vertex - 4);
    
    //    noFillCounter.num++;
}
