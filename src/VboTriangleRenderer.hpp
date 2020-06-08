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
#include "VboRendererConfig.h"


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
    
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool fill);
    void triangle(float x, float y, float size, float angle, bool fill);
    void filledTriangle(ofVec2f p1,ofVec2f p2, ofVec2f p3);
    void fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
    void noFilledTriangle(ofVec2f p1,ofVec2f p2, ofVec2f p3);
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
    
    //Variables for calculation 
    ofVec2f top, left, right, center, normalizedTop, normalizedLeft, normalizedRight;
    
    //VBO
    vbo_count_t filledCounter;
    ofVbo filledTriangleVbo;
    std::array<glm::vec2, VBOTRIGANGLE_VERTS_MAX> filledTrianglePos;
    std::array<ofFloatColor, VBOTRIGANGLE_VERTS_MAX> filledTriangleColors;
    std::array<ofIndexType, VBOTRIGANGLE_VERTS_MAX> filledTriangleIndices;
    
    vbo_count_t noFillCounter;
    ofVbo noFillTriangleVbo;
    std::array<glm::vec2, VBOTRIGANGLE_VERTS_MAX> noFillTrianglePos;
    std::array<ofFloatColor, VBOTRIGANGLE_VERTS_MAX> noFillTriangleColors;
    std::array<ofIndexType, VBOTRIGANGLE_VERTS_MAX> noFillTriangleIndices;
};

#endif /* VboTriangleRenderer_hpp */
