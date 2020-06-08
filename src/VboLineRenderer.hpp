//
//  VboLineRenderer.hpp
//  vboCircle
//
//  Created by Hana on 2018/01/23.
//
//

#ifndef VboLineRenderer_hpp
#define VboLineRenderer_hpp

#include "ofMain.h"
#include "VboRendererConfig.h"

constexpr int VBOLINE_VERTS_MAX = VBOLINE_NUM_MAX * 4;
constexpr int VBOLINE_INDICES_MAX = VBOLINE_NUM_MAX * 6;
const float THICK_MOD = 0.3125;

class VboLineRenderer {
public:
    VboLineRenderer();
    void setup();
    void setup(float w, float h);
    void setScreenSize();
    void setScreenSize(float w, float h);
    void setColor(float brightness, float alpha = 1.0);
    void setColor(ofFloatColor c);
    
    void line(float x1, float y1, float x2, float y2, float _thick);    //1.0 equals to display width
    
    void draw();
    
private:
    void initVbo();
    void initCount();
    void addVertex(ofVec2f pos);
    void addIndex(ofIndexType index);
    void addIndex(int index);
    void addLineIndices();
    ofVec2f getPosition(float x, float y);
    
    
    ofVec2f start, s1, s2, end, e1,e2;
    float width, height, thick;
    ofFloatColor color;
    int lineCount, vertsCount, indicesCount;
    
    //VBO
    ofVbo vbo;
    std::array<glm::vec2, VBOLINE_VERTS_MAX> vertices;
    std::array<ofFloatColor, VBOLINE_VERTS_MAX> colors;
    std::array<ofIndexType, VBOLINE_INDICES_MAX> indices;    
};

#endif /* VboLineRenderer_hpp */
