//
//  VboArcRenderer.hpp
//  example-simple
//
//  Created by Hana on 2018/05/18.
//
//

#ifndef VboArcRenderer_hpp
#define VboArcRenderer_hpp

#include "ofMain.h"
#include "config.h"

static constexpr int VBOARC_DIVISION = 128;
constexpr int VBOARC_VERTS_MAX = VBOARC_DIVISION * 2;
constexpr int VBOARC_INDICES_MAX = VBOARC_VERTS_MAX * 2;

class VboArc {
public:
    VboArc();
    void setup();
    void setup(float w, float h);
    inline void setScreenSize(float w, float h) {
        width = w;
        height = h;
    }
    
    inline void setScreenSize() {
        width = ofGetWidth();
        height = ofGetHeight();
    }
    void setColor(ofFloatColor _color);
    void setColor(float brightness, float alpha = 1.0);
    void setLineWidth(float w);
    
    void set(float x1, float y1, float x2, float y2, float arcHeight, float expose, float thick);
    void draw();
private:
    void initVbo();
    void resetCount();
    
    void addVertex(ofVec2f pos);
    void addIndex(ofIndexType index);
    void addColor(ofFloatColor _color);
    
    ofVbo vbo;
    ofVec2f verts[VBOARC_VERTS_MAX];
    ofFloatColor colors[VBOARC_VERTS_MAX];
    ofIndexType indices[VBOARC_INDICES_MAX];

    vbo_count_t counter;
    float width, height, lineWidth;
    ofFloatColor color;
    
    //Variables for culculation
    ofVec2f prevPoint, control, start, end, center;
};


class VboArcRenderer {
public:
    VboArcRenderer();
    void setup();
    void setup(float w, float h);
    void setScreenSize();
    void setScreenSize(float w, float h);
    void setColor(ofFloatColor _color);
    void setColor(float brightness, float alpha = 1.0);
    
    void draw();
    void arc(float x1, float y1, float x2, float y2, float arcHeight, float expose, float thick);
    
private:
    void initVbo();
    void resetConter();
    
    int arcCount;
    float width, height;
    ofFloatColor color;
    
    VboArc vboArc[VBOARC_NUM_MAX];

};


#endif /* VboArcRenderer_hpp */
