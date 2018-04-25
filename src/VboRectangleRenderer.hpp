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

constexpr int RECTANGLE_NUM_MAX = 1024;
constexpr int VBORECTANGLE_VERTS_MAX = RECTANGLE_NUM_MAX * 4;
constexpr int VBORECTANGLE_INDICES_MAX = RECTANGLE_NUM_MAX * 6;

class VboRectangleRenderer {
public:
    VboRectangleRenderer();
    void setup();
    void setup(float w, float h);
    void setScreenSize();
    void setScreenSize(float w, float h);
    void setColor(ofFloatColor _color);
    void setColor(float brightness, float alpha= 1.0);
    void setLineWidth(float w);
    
    void draw();
    
    void square(float x, float y, float size, float angle, bool fill);
    void square(ofVec2f pos, float size, float angle, float fill);
    
    void rectangle(ofVec2f p1, ofVec2f p2, float angle, bool fill);
    void rectangle(float x1, float y1, float x2, float y2, float angle, bool fill);
    
    void filledRectangle(ofVec2f p1, ofVec2f p2, float angle);
    void filledRectangle(float x1, float y1, float x2, float y2, float angle);

    void noFillRectangle(ofVec2f p1, ofVec2f p2, float angle);
    void noFillRectangle(float x1, float y1, float x2, float y2, float angle);
    
private:
    void initVbo();
    void initCount();
    void addVertex(ofVec2f pos);
    void addIndex(int index);
    void addLineIndices();
    ofVec2f getPosition(float x, float y);
    
    
    ofVec2f start, s1, s2, end, e1,e2;
    float width, height, thick;
    ofFloatColor color;
    int lineCount, vertsCount, indicesCount;
    
    //VBO
    ofVbo filledVbo;
    ofVec2f filledRectanglePos[VBORECTANGLE_VERTS_MAX];
    ofFloatColor filledRectangleColors[VBORECTANGLE_VERTS_MAX];
    ofIndexType filledRectangleIndices[VBORECTANGLE_INDICES_MAX];

    ofVbo noFillVbo;
    ofVec2f noFillRectanglePos[VBORECTANGLE_VERTS_MAX];
    ofFloatColor noFillRectangleColors[VBORECTANGLE_VERTS_MAX];
    ofIndexType noFillRectangleIndices[VBORECTANGLE_INDICES_MAX];

};

#endif /* VboRectangleRenderer_hpp */
