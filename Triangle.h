//
//  Triangle.h
//  glutapp
//
//  Created by Cindy Hoang on 5/7/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

#include "Obstacle.h"

class Triangle : public Obstacle {
    float x, y, z;
    float r, g, b;
public:
    Triangle(float xx = 0, float yy = 0, float zz = 0, float rr = 0, float gg = 0, float bb = 1) :
        x(xx), y(yy), z(zz), r(rr), g(gg), b(bb) {
    }
    
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    void setX(float xx) { x = xx; }
    void setY(float yy) { y = yy; }
    void setZ(float zz) { z = zz; }
    
    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }
    void setColor(float rr, float gg, float bb) { r = rr; g = gg; b = bb; }
    
    bool isLand();
    void draw();
    bool contains(float x, float y);
    ~Triangle() {}
};
#endif /* Triangle_h */
