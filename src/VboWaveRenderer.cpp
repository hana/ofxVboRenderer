//
//  VboWaveRenderer.cpp
//  example-simple
//
//  Created by Hana on 2018/05/22.
//
//

#include "VboWaveRenderer.hpp"

VboWave::VboWave() {
    initVbo();
}

void VboWave::set(float x1, float y1, float x2, float y2, float freq, float amplitude, float phase, float thick) {
    //Culcurate Line status
    ofVec2f start = ofVec2f(x1 * width, y1 * height);
    ofVec2f end = ofVec2f(x2 * width, y2 * height);
    ofVec2f line = end - start;

    int length = line.length();
    float angle = line.getNormalized().angle(ofVec2f(1,0));


    //update linewidth
    lineWidth = thick;

    //Draw
    ofVec2f currentPointOnLine = ofVec2f(0, 0);

    //First position
    ofVec2f currentPos = start + line.getNormalized().rotate(90) * sin((phase * 2.0 * PI)) * width * amplitude;
    addVertex(currentPos);
    addColor(color);

    //Other pos
    static float ap = 0;    //advanced phase
    for (float i = 1; i <= VBOWAVE_DIVISION; i += 1.0) {
        ap = i * VBOWAVE_DIVISION_RECIPRO;
        currentPointOnLine = line * ap + start;
        currentPos = currentPointOnLine + line.getNormalized().rotate(90) * sin((ap * PI * 2 * freq) + (phase * 2 * PI)) * width * amplitude;
        addVertex(currentPos);
        addColor(color);
        addIndex(i - 1);
        addIndex(i);
    }
}


void VboWave::draw() {
    vbo.updateVertexData(verts, counter.vertex);
    vbo.updateColorData(colors, counter.color);
    vbo.updateIndexData(indices, counter.index);

    glLineWidth(lineWidth);
    vbo.drawElements(GL_LINES, counter.index);

    resetCount();
}

void VboWave::initVbo() {
    vbo.setVertexData(verts, VBOWAVE_VERTS_MAX, GL_DYNAMIC_DRAW);
    vbo.setColorData(colors, VBOWAVE_VERTS_MAX, GL_DYNAMIC_DRAW);
    vbo.setIndexData(indices, VBOWAVE_INDICES_MAX, GL_DYNAMIC_DRAW);
}

void VboWave::addVertex(ofVec2f pos) {
    verts[counter.vertex] = pos;
    counter.vertex++;
}

void VboWave::addColor(ofFloatColor _color) {
    colors[counter.color] = _color;
    counter.color++;
}

void VboWave::addIndex(ofIndexType index) {
    indices[counter.index] = index;
    counter.index++;
}

void VboWave::resetCount() {
    counter.vertex = 0;
    counter.color = 0;
    counter.index = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Renderer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VboWaveRenderer::VboWaveRenderer() {

}

void VboWaveRenderer::setup() {
    width = ofGetWidth();
    height = ofGetHeight();
    for(auto &v : vboWave) {
        v.setup(width, height);
    }
}

void VboWaveRenderer::setup(float w, float h) {
    width = w;
    height = h;
    for(auto &v : vboWave) {
        v.setup(width, height);
    }
}

void VboWaveRenderer::setScreenSize() {
    width = ofGetWidth();
    height = ofGetHeight();
    for(auto &v : vboWave) {
        v.setScreenSize(width, height);
    }
}

void VboWaveRenderer::setScreenSize(float w, float h) {
    width = w;
    height = h;
    for(auto &v : vboWave) {
        v.setup(width, height);
    }
    
}

void VboWaveRenderer::wave(float x1, float y1, float x2, float y2, float freq, float amplitude, float phase, float thick) {
    vboWave[waveCount].set(x1, y1, x2, y2, freq, amplitude, phase, thick);
    waveCount++;
}

void VboWaveRenderer::draw() {
    for(int i = 0; i < waveCount; i++) {
        vboWave[i].draw();
    }

    waveCount = 0;
}
