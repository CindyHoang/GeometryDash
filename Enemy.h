//
//  Enemy.h
//  glutapp
//
//  Created by Cindy Hoang on 5/8/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

#include "Obstacle.h"

class Enemy : public Obstacle {
    float x, y;
    float w, h;
    float r, g, b;
    
public:
    bool missile;
    
    Enemy(float xx = 0, float yy = 0, float ww = 0.1, float hh = 0.1, float rr = 1, float gg = 1, float bb = 1) :
        x(xx), y(yy), w(ww), h(hh), r(rr), g(gg), b(bb) {
            missile = false;
    }
    
    void draw();
    bool canFire();
    bool fire();
    
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
};

#endif /* Enemy_h */
