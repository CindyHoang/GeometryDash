//
//  Obstacle.h
//  glutapp
//
//  Created by Cindy Hoang on 5/3/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef Obstacle_h
#define Obstacle_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Obstacle {
    float x, y;
    float w, h;
    float r, g, b;
    bool isLandable;
public:
    Obstacle(float xx = 0, float yy = 0, bool canLand = true, float ww = 0.1, float hh = 0.1, float rr = 1, float gg = 0, float bb = 0) :
        x(xx), y(yy), isLandable(canLand), w(ww), h(hh), r(rr), g(gg), b(bb) {
    }
    
    float getX() const { return x; }
    float getY() const { return y; }
    void setX(float xx) { x = xx; }
    void setY(float yy) { y = yy; }
    
    float getW() const { return w; }
    float getH() const { return h; }
    void setW(float ww) { w = ww; }
    void setH(float hh) { h = hh; }
    
    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }
    void setColor(float rr, float gg, float bb) { r = rr; g = gg; b = bb; }
    
    bool isLand() const { return isLandable; }
    
    virtual bool contains(float x, float y);
    virtual void draw();
    virtual ~Obstacle() {}
};

#endif /* Obstacle_h */
