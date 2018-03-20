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

class ofxVboRenderer {
public:
    ofxVboRenderer();
    void setup();
    void setup(float w, float h);
    void setColor(float c);
    void setColor(ofFloatColor c);
    void setCircleBaseRad(int baseRad);
    void draw();
    void circle(float x, float y, float size, bool fill);
    void line(float x1, float y1, float x2, float y2, float _thick);
    
private:
    VboCircleRenderer circleRenderer;
    VboLineRenderer lineRenderer;
    float width ,height;
    
};

#endif /* ofxVboRenderer_hpp */
