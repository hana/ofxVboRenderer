//
//  VboArcRenderer.cpp
//  example-simple
//
//  Created by Hana on 2018/05/18.
//
//

#include "VboArcRenderer.hpp"

VboArc::VboArc() {
    initVbo();
    resetCount();
}


void VboArc::setup() {
    setScreenSize();
}

void VboArc::setup(float w, float h) {
    setScreenSize(w, h);
}

void VboArc::setColor(ofFloatColor _color)  {
    color = _color;
}

void VboArc::setColor(float brightness, float alpha) {
    color = ofFloatColor(brightness, alpha);
}

void VboArc::setLineWidth(float w) {
    lineWidth = w;
}

void VboArc::set(float x1, float y1, float x2, float y2, float arcHeight, float expose, float thick)    {
    //Prepare for culculate
    float line_x, line_y;
    ofVec2f center;
    
    center = ofVec2f((x1 + x2) * 0.5, (y1 + y2) * 0.5);
    line_x = x2 - x1;
    line_y = y2 - y1;
    
    //Get control position
    float control_x, control_y, normalizedLine, ux, uy;
    normalizedLine = 1.0 / sqrt(line_x * line_x + line_y * line_y);
    ux = normalizedLine * line_x;
    uy = normalizedLine * line_y;
    
    control_x = center.x - arcHeight * uy;
    
    if (arcHeight < 0) {
        control_y = center.y + abs(arcHeight * ux);
    } else {
        control_y = center.y - abs(arcHeight * ux);
    }
    
    //Ready to start drawing
    prevPoint = ofVec2f(x1 * width, y1 * height);
    control = ofVec2f(control_x * width, control_y * height);
    start = ofVec2f(x1 * width, y1 * height);
    end = ofVec2f(x2 * width, y2 * height);
    
    //Draw Arc
    this->setLineWidth(thick);
    addVertex(start);
    
    float exposed, t;
    exposed = float(VBOARC_DIVISION) * expose;
    ofVec2f tmpPoint = ofVec2f(0, 0);
    for (int i = 1; i <= exposed; i++) {
        t = float(i) / VBOARC_DIVISION;
        tmpPoint = (1-t)*(1-t)*start + 2*(1-t)*t*control + t*t*end;
        addVertex(tmpPoint);
        addColor(color);
        addIndex(i-1);
        addIndex(i);
    }
    
}

void VboArc::draw() {
    vbo.updateVertexData(verts, counter.vertex);
    vbo.updateColorData(colors, counter.color);
    vbo.updateIndexData(indices, counter.index);
    
    glLineWidth(lineWidth);
    vbo.drawElements(GL_LINES, counter.index);
    
    resetCount();
}


void VboArc::initVbo() {
    vbo.setVertexData(verts, VBOARC_VERTS_MAX, GL_DYNAMIC_DRAW);
    vbo.setColorData(colors, VBOARC_VERTS_MAX, GL_DYNAMIC_DRAW);
    vbo.setIndexData(indices, VBOARC_INDICES_MAX, GL_DYNAMIC_DRAW);
}

void VboArc::resetCount() {
    counter.vertex = 0;
    counter.color = 0;
    counter.index = 0;
    counter.num = 0;
}

void VboArc::addVertex(ofVec2f vertex) {
    verts[counter.vertex] = vertex;
    counter.vertex++;
}

void VboArc::addIndex(ofIndexType index) {
    indices[counter.index] = index;
    counter.index++;
}

void VboArc::addColor(ofFloatColor _color) {
    colors[counter.color] = _color;
    counter.color++;
}

VboArcRenderer::VboArcRenderer() {
    width = ofGetWidth();
    height = ofGetHeight();
    for (auto &v : vboArc) {
        v.setup(width, height);
    }
}

void VboArcRenderer::setup() {
    width = ofGetWidth();
    height = ofGetHeight();
    for (auto &v : vboArc) {
        v.setup(width, height);
    }
}

void VboArcRenderer::setup(float w, float h) {
    for (auto &v : vboArc) {
        v.setup(w, h);
    }
}

void VboArcRenderer::setScreenSize() {
    width = ofGetWidth();
    height = ofGetHeight();
    for (auto &v : vboArc) {
        v.setScreenSize(width, height);
    }
}

void VboArcRenderer::setScreenSize(float w, float h) {
    for (auto &v : vboArc) {
        v.setScreenSize(w, h);
    }
}


void VboArcRenderer::setColor(ofFloatColor _color) {
    color = _color;
}

void VboArcRenderer::setColor(float brightness, float alpha) {
    color = ofFloatColor(brightness, alpha);
}

void VboArcRenderer::arc(float x1, float y1, float x2, float y2, float arcHeight, float expose, float thick) {
    vboArc[arcCount].setColor(color);
    vboArc[arcCount].set(x1, y1, x2, y2, arcHeight, expose, thick);
    arcCount++;
}

void VboArcRenderer::draw() {
    for(int i = 0; i < arcCount; i++) {
        vboArc[i].draw();
    }
    
    arcCount = 0;
}
