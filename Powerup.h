//
//  Powerup.h
//  glutapp
//
//  Created by Cindy Hoang on 5/7/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef Powerup_h
#define Powerup_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Powerup {
    float x, y;
    float w, h;
    float r, g, b;
public:
    Powerup(float xx = 0, float yy = 0, float ww = 0.05, float hh = 0.05, float rr = 0, float gg = 0, float bb = 1) : x(xx), y(yy), w(ww), h(hh), r(rr), g(gg), b(bb) {
        
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
    
    virtual void draw();
    virtual bool contains(float x, float y);
    virtual ~Powerup() {}
};

#endif /* Powerup_h */
