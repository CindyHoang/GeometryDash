//
//  Player.h
//  glutapp
//
//  Created by Cindy Hoang on 4/30/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef Player_h
#define Player_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <vector>

using namespace std;
class Player {
    float x, y; // Coordinates
    float s; // Length of sides
    float r, g, b; // Color
    
public:
    bool shouldJump, shouldLand;
    vector<int> upgrades;
    
    Player(float xx = 0, float yy = 0, float ss = 0.1, float rr = 0, float gg = 1, float bb = 0) :
        x(xx), y(yy), s(ss), r(rr), g(gg), b(bb) {
            shouldJump = false;
            shouldLand = false;
    }
    
    void draw();
    
    void jump();
    
    float getX() const { return x; }
    float getY() const { return y; }
    void setX(float xx) { x = xx; }
    void setY(float yy) { y = yy; }
    
    float getS() const { return s; }
    void setS(float ss) { s = ss; }
    
    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }
    void setColor(float rr, float gg, float bb) { r = rr; g = gg; b = bb; }
    void resetColor() { r = 0; g = 1; b = 0; }
    
    virtual ~Player() {}
};

#endif /* Player_h */
