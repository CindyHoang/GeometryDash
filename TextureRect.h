//
//  TextureRect.h
//  glutapp
//
//  Created by Cindy Hoang on 5/9/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef TextureRect_h
#define TextureRect_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class TextureRect {
    float x, y;
    float w, h;
    
public:
    TextureRect(float xx = 0, float yy = 0, float ww = 0.5, float hh = 0.5) :
    x(xx), y(yy), w(ww), h(hh) {
    }
    
    void draw();
};


#endif /* TextureRect_h */
