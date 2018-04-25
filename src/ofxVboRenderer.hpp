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

class ofxVboRenderer {
public:
    ofxVboRenderer();
    void setup();
    void setup(float w, float h);
    void setScreenSize();
    void setScreenSize(float w, float h);
    void setColor(float brightness, float alpha = 1.0);
    void setColor(float red, float green, float blue, float alpha = 1.0);
    void setColor(ofFloatColor c);
    void setCircleBaseRad(int baseRad);
    void draw();
    void circle(float x, float y, float size, bool fill);
    void line(float x1, float y1, float x2, float y2, float _thick);
    void triangle(float x, float y, float size, float angle, bool fill);
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool fill);
    
private:
    VboCircleRenderer circleRenderer;
    VboLineRenderer lineRenderer;
    VboTriangleRenderer triangleRenderer;
    float width, height;
    ofFloatColor colorBuffer;
    
};

#endif /* ofxVboRenderer_hpp */
