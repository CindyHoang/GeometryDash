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
public:
    Powerup(float xx = 0, float yy = 0, float ww = 0.05, float hh = 0.05) : x(xx), y(yy), w(ww), h(hh) {
        
    }
};

#endif /* Powerup_h */
