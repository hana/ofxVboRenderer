//
//  VboTriangleRenderer.hpp
//  vboRendererDev
//
//  Created by Momoha Matsuhashi on 2018/04/16.
//
//

#ifndef VboTriangleRenderer_hpp
#define VboTriangleRenderer_hpp

#include "ofMain.h"

struct vbo_triangle_count_t {
    int num;
    int vertex = 0;
    int color = 0;
    int index = 0;
};

constexpr int VBOTRIANGLE_NUM_MAX = 1024;
constexpr int VBOTRIGANGLE_VERTS_MAX = VBOTRIANGLE_NUM_MAX * 3;
constexpr int VBOTRIANGLE_INDICES_MAX = VBOTRIANGLE_NUM_MAX * 6;

class VboTriangleRenderer {
public:
    VboTriangleRenderer();
    void setup();
    void setup(float w, float h);
    void setScreenSize();
    void setScreenSize(float w, float h);
    void setColor(float brightness, float alpha = 1.0);
    void setColor(ofFloatColor c);
    void setLineWidth(float w);
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool fill);
    void fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
    void noFillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
    
    
    void draw();
    
private:
    void initVbo();
    
    void addVertex(bool isFilled, ofVec2f pos);
    void addIndex(bool isFilled, ofIndexType index);
    void addColor(bool isFilled, ofFloatColor color);
    void resetCounter();
    
    float width, height, lineWidth;
    ofFloatColor color;
    
    
    
    //VBO
    vbo_triangle_count_t filledCounter;
    ofVbo filledTriangleVbo;
    ofVec2f filledTrianglePos[VBOTRIGANGLE_VERTS_MAX];
    ofFloatColor filledTriangleColors[VBOTRIGANGLE_VERTS_MAX];
    ofIndexType filledTriangleIndices[VBOTRIGANGLE_VERTS_MAX];
    
    vbo_triangle_count_t noFillCounter;
    ofVbo noFillTriangleVbo;
    ofVec2f noFillTrianglePos[VBOTRIGANGLE_VERTS_MAX];
    ofFloatColor noFillTriangleColors[VBOTRIGANGLE_VERTS_MAX];
    ofIndexType noFillTriangleIndices[VBOTRIANGLE_INDICES_MAX];
    
};

#endif /* VboTriangleRenderer_hpp */
