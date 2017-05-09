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
    int type;
    
public:
    Powerup(float xx = 0, float yy = 0, int tt = 0, float ww = 0.05, float hh = 0.05) : x(xx), y(yy), type(tt), w(ww), h(hh) {
        if (type == 1) {
            r = 1;
            g = 1;
            b = 1;
        }
        else {
            r = 0;
            g = 1;
            b = 1;
        }
    }
    
    float getX() const { return x; }
    float getY() const { return y; }
    void setX(float xx) { x = xx; }
    void setY(float yy) { y = yy; }
    
    int getType() const { return type; }
    
    float getW() const { return w; }
    float getH() const { return h; }
    void setW(float ww) { w = ww; }
    void setH(float hh) { h = hh; }
    
    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }
    void setColor(float rr, float gg, float bb) { r = rr; g = gg; b = bb; }
    
    virtual void draw();
    virtual ~Powerup() {}
};

#endif /* Powerup_h */
