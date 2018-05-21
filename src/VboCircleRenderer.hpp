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
#include "config.h"


constexpr int RESOLUTION_MAX = 120;
constexpr int VBOCIRCLE_VERTICES_MAX = VBOCIRCLE_NUM_MAX * RESOLUTION_MAX;

class VboCircleRenderer {
public:
    VboCircleRenderer();
    void setup();
    void setup(float w, float h);
    void setScreenSize();
    void setScreenSize(float w, float h);
    void setColor(ofFloatColor _color);
    void setColor(float brightness, float alpha = 1.0);
    void setLineWidth(float w);
    inline void setBaseDiameter(int _baseDiameter) {
        baseDiameter = _baseDiameter;
    }
    void draw();
    void circle(float x, float y, float diameter, bool fill);
    void filled(float x, float y, float diameter);
    void noFill(float x, float y, float diameter);
    
    
    ofVec2f getVertPos(float centerX, float centerY, float rad, float diameter);
    
private:
    void initVbo();
    
    int getResolution(float size);
    
    [[deprecated]]void addVertex(bool isFilled, ofVec2f pos);
    void addVertex(ofVec2f pos, bool isFilled);
    [[deprecated]]void addIndex(bool isFilled, ofIndexType index);
    void addIndex(ofIndexType index, bool isFilled);
    [[deprecated]]void addColor(bool isFilled, ofFloatColor _color);
    void addColor(ofFloatColor _color, bool isFilled);
    void resetCounter();
    
    int baseDiameter;
    float width, height, lineWidth;
    ofFloatColor color;
    
    
    
    //VBO
    vbo_count_t filledCounter;
    ofVbo filledVbo;
    ofVec2f filledPos[VBOCIRCLE_VERTICES_MAX];
    ofFloatColor filledColors[VBOCIRCLE_VERTICES_MAX];
    ofIndexType filledIndices[VBOCIRCLE_VERTICES_MAX];
    
    vbo_count_t noFillCounter;
    ofVbo noFillVbo;
    ofVec2f noFillPos[VBOCIRCLE_VERTICES_MAX];
    ofFloatColor noFillColors[VBOCIRCLE_VERTICES_MAX];
    ofIndexType noFillIndices[VBOCIRCLE_VERTICES_MAX];
    
};

#endif /* VboCircle_hpp */
