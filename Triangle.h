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
public:
    Triangle() {
//        glBegin(GL_TRIANGLES);
//        
//        glColor3f(1.0, 1.0, 1.0);
//        glVertex3f()
    }
    
    bool contains(float x, float y);
    void draw();
    ~Triangle() {}
};
#endif /* Triangle_h */
