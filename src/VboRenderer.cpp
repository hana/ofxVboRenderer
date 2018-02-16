//
//  VboRenderer.cpp
//  vboCircle
//
//  Created by Hana on 2018/01/24.
//
//

#include "VboRenderer.hpp"

VboRenderer::VboRenderer() {

}

void VboRenderer::setup() {
    circleRenderer.setup();
    lineRenderer.setup();
}

void VboRenderer::setup(float w, float h) {
    circleRenderer.setup(w, h);
    lineRenderer.setup(w, h);
}


void VboRenderer::setColor(float c) {
    circleRenderer.setColor(c);
    lineRenderer.setColor(c);
}

void VboRenderer::setColor(ofFloatColor c) {
    circleRenderer.setColor(c);
    lineRenderer.setColor(c);
}


void VboRenderer::setCircleBaseRad(int baseRad) {
    circleRenderer.setBaseRad(baseRad);
}

void VboRenderer::draw() {
    circleRenderer.draw();
    lineRenderer.draw();
}

void VboRenderer::circle(float x, float y, float size, bool fill) {
    circleRenderer.circle(x, y, size, fill);
}

void VboRenderer::line(float x1, float y1, float x2, float y2, float _thick) {
    lineRenderer.line(x1, y1, x2, y2, _thick);
}


//void VboRenderer::setEvents()  {
//    GismoManager& gismo = GismoManager::getInstance();
//    
//    auto circleEvent = [&](void* args){ //<- keep this desctiption
//        param_u* params = (param_u *)args;
//        float x = params[0].fval;
//        float y = params[1].fval;
//        float size = params[2].fval;
//        float fill = params[3].ival;
//        
//        this->circle(x, y, size, fill);
//        
//    };
//    gismo.lambdaAdd("/circle", circleEvent);
//    
//    
//    auto lineEvent = [&](void* args){ //<- keep this desctiption
//        param_u* params = (param_u *)args;
//        float x1 = params[0].fval;
//        float y1 = params[1].fval;
//        float x2 = params[2].fval;
//        float y2 = params[3].fval;
//        float _thick = params[4].fval;
//        
//        
//        this->line(x1, y1, x2, y2, _thick);
//        
//    };
//    gismo.lambdaAdd("/line", lineEvent);
//    
//    
//    auto colorEvent = [&](void* args){ //<- keep this desctiption
//        param_u* params = (param_u *)args;
//        float c = params[0].fval;
//        
//        this->setColor(c);
//    };
//    
//    gismo.lambdaAdd("/performanceColor", colorEvent);
//}
