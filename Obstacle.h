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
    bool missile;
    bool passedUser;
    Obstacle(float xx = 0, float yy = 0, bool canLand = true, float ww = 0.1, float hh = 0.1, float rr = 1, float gg = 0, float bb = 0) :
        x(xx), y(yy), isLandable(canLand), w(ww), h(hh), r(rr), g(gg), b(bb) {
            missile = false;
            passedUser = false;
    }
    
    virtual float getX() const { return x; }
    virtual float getY() const { return y; }
    virtual void setX(float xx) { x = xx; }
    virtual void setY(float yy) { y = yy; }
    
    virtual float getW() const { return w; }
    virtual float getH() const { return h; }
    virtual void setW(float ww) { w = ww; }
    virtual void setH(float hh) { h = hh; }
    
    virtual float getR() const { return r; }
    virtual float getG() const { return g; }
    virtual float getB() const { return b; }
    virtual void setColor(float rr, float gg, float bb) { r = rr; g = gg; b = bb; }
    
    virtual bool isLand() { return isLandable; }
    virtual bool canFire();
    virtual void draw();
    virtual ~Obstacle() {}
};

#endif /* Obstacle_h */
