//
//  VboRectangleRenderer.hpp
//  example-simple
//
//  Created by Hana on 2018/04/25.
//
//

#ifndef VboRectangleRenderer_hpp
#define VboRectangleRenderer_hpp

#include "ofMain.h"
#include "config.h"

constexpr int RECTANGLE_VERTS_NUM = 4;
constexpr int VBORECTANGLE_VERTS_MAX = VBORECTANGLE_NUM_MAX * 4;
constexpr int VBORECTANGLE_INDICES_MAX = VBORECTANGLE_NUM_MAX * 8;

class VboRectangleRenderer {
public:
    VboRectangleRenderer();
    void setup();
    void setup(float w, float h);
    
    inline void setScreenSize() {
        width = ofGetWidth();
        height = ofGetHeight();
    }
    
    inline void setScreenSize(float w, float h) {
        width = w;
        height = h;
    }
    
    inline void setColor(ofFloatColor _color) {
        color = _color;
    }
    
    inline void setColor(float brightness, float alpha = 1.0) {
        color = ofFloatColor(brightness, alpha);
    }
    
    inline void setLineThick(float _thick) {
        thick = _thick;
    }
    
    void draw();
    
    /* Square */
    void square(float x, float y, float size, float angle, bool fill);
    void square(ofVec2f _pos, float size, float angle, float fill);
    
    void filledSquare(float x, float y, float size, float angle);
    void noFillSquare(float x, float y, float size, float angle);
    
    
    
    /* Rectangle */
    void rectangle(ofVec2f p1, ofVec2f p2, float angle, bool fill);
    void rectangle(float x1, float y1, float x2, float y2, float angle, bool fill);
    void rectangle(ofVec2f pos, float w, float h, float angle, bool fill);
    
    void filledRectangle(float x1, float y1, float x2, float y2, float angle);
    void filledRectangle(ofVec2f pos, float w, float h, float angle);
    void noFillRectangle(float x1, float y1, float x2, float y2, float angle);
    void noFillRectangle(ofVec2f pos, float w, float h, float angle);
    
private:
    void initVbo();
    void initCount();
    
    //Methods to update pos[] with the width and height of rect or square
    void updateVerts(float x, float y, float size, float angle);    //For square
    void updateVerts(ofVec2f pos, float size, float angle); //For square
    
    void updateVerts(float x1, float y1, float x2, float y2, float angle);   //For rectangle
    void updateVerts(ofVec2f p1, ofVec2f p2, float angle);   //For rectangle
    void updateVerts(ofVec2f pos, float w, float h, float angle);
    
    void addVertex(ofVec2f pos, bool filled);
    void addFilledVertex(ofVec2f pos);
    void addNoFillVertex(ofVec2f pos);
    
    void addIndex(ofIndexType index, bool filled);
    void addFilledIndex(ofIndexType index);
    void addNoFillIndex(ofIndexType index);
    
    void addColor(ofFloatColor _color, bool filled);
    void addFilledColor(ofFloatColor _color);
    void addNoFillColor(ofFloatColor _color);
    
    void addFilledRectangle();
    void addNoFillRectangle();
    
    float width, height, thick;
    ofFloatColor color;
    
    //To calcurate square
    ofVec2f verts[RECTANGLE_VERTS_NUM],center; //From left-top, clockwise
    float tmpLength, tmpWidth, tmpHeight, tmpAngle;
    
    //VBO
    vbo_count_t filledCounter;
    ofVbo filledVbo;
    ofVec2f filledPos[VBORECTANGLE_VERTS_MAX];
    ofFloatColor filledColors[VBORECTANGLE_VERTS_MAX];
    ofIndexType filledIndices[VBORECTANGLE_INDICES_MAX];

    vbo_count_t noFillCounter;
    ofVbo noFillVbo;
    ofVec2f noFillPos[VBORECTANGLE_VERTS_MAX];
    ofFloatColor noFillColors[VBORECTANGLE_VERTS_MAX];
    ofIndexType noFillIndices[VBORECTANGLE_INDICES_MAX];

};

#endif /* VboRectangleRenderer_hpp */
