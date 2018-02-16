//
//  VboCircle.hpp
//  vboCircle
//
//  Created by Hana on 2018/01/22.
//
//

#ifndef VboCircleRenderer_hpp
#define VboCircleRenderer_hpp

#include "ofMain.h"

struct vbo_count_t {
    int num;
    int vertex = 0;
    int color = 0;
    int index = 0;
};

enum circle_type_e {
    filled, noFill,
};

static constexpr int CIRCLE_NUM_PER_AG = 64;
static constexpr int CIRCLE_NUM_MAX = 1024;
static constexpr int RESOLUTION_MAX = 120;
static constexpr int VERTICES_MAX = CIRCLE_NUM_MAX * RESOLUTION_MAX;

class VboCircleRenderer {
public:
    VboCircleRenderer();
    void setup();
    void setup(float w, float h);
    void setColor(ofFloatColor _color);
    void setColor(float c);
    void setLineWidth(float w);
    void setBaseRad(int _baseRad);
    void draw();
    void circle(float x, float y, float size, bool fill);
    void filledCircle(float x, float y, float size);
    void noFillCircle(float x, float y, float size);
    

    ofVec2f getVertPos(float centerX, float centerY, float rad, float size);
    
private:
    void initVbo();
    
    int getResolution(float size);
    
    void addVertex(circle_type_e type, ofVec2f pos);
    void addIndex(circle_type_e type, ofIndexType index);
    void addColor(circle_type_e type, ofFloatColor color);
    void resetCounter();
    
    int baseRad;
    float width, height, lineWidth;
    ofFloatColor color;
    

    
    //VBO
    vbo_count_t filledCounter;
    ofVbo filledCircleVbo;
    ofVec2f filledCirclePos[VERTICES_MAX];
    ofFloatColor filledCircleColors[VERTICES_MAX];
    ofIndexType filledCircleIndices[VERTICES_MAX];
    
    vbo_count_t noFillCounter;
    ofVbo noFillCircleVbo;
    ofVec2f noFillCirclePos[VERTICES_MAX];
    ofFloatColor noFillCircleColors[VERTICES_MAX];
    ofIndexType noFillCircleIndices[VERTICES_MAX];
    
};

#endif /* VboCircle_hpp */
