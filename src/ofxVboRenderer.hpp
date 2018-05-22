//
//  ofxVboRenderer.hpp
//  ofxVboRenderer
//
//  Created by Hana on 2018/01/24.
//
//

#ifndef ofxVboRenderer_hpp
#define ofxVboRenderer_hpp

#include "ofMain.h"
#include "VboCircleRenderer.hpp"
#include "VboLineRenderer.hpp"
#include "VboTriangleRenderer.hpp"
#include "VboRectangleRenderer.hpp"
#include "VboArcRenderer.hpp"
#include "VboWaveRenderer.hpp"

class ofxVboRenderer {
public:
    void setup();
    void setup(float w, float h);
    void setScreenSize();
    void setScreenSize(float w, float h);
    void setColor(float brightness, float alpha = 1.0);
    void setColor(float red, float green, float blue, float alpha = 1.0);
    void setColor(ofFloatColor c);
    void setCircleBaseDiameter(int baseDiameter);
    void draw();
    void circle(float x, float y, float diameter, bool fill);
    void line(float x1, float y1, float x2, float y2, float _thick);
    void triangle(float x, float y, float size, float angle, bool fill);
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool fill);
    void square(float x, float y, float size, float angle, bool fill);
    void square(ofVec2f pos, float size, float angle, bool fill);
    void rect(float x1, float y1, float x2, float y2, float  angle, bool fill);
    void rect(ofVec2f pos, float w, float h, float angle, bool fill);
    void arc(float x1, float y1, float x2, float y2, float arcHeight, float expose, float thick);
    void wave(float x1, float y1, float x2, float y2, float freq, float amplitude, float phase, float thick);
    
private:
    VboCircleRenderer circleRenderer;
    VboLineRenderer lineRenderer;
    VboTriangleRenderer triangleRenderer;
    VboRectangleRenderer rectangleRenderer;
    VboArcRenderer arcRenderer;
    VboWaveRenderer waveRenderer;
    
    float width, height;
    ofFloatColor colorBuffer;
    
};

#endif /* ofxVboRenderer_hpp */
