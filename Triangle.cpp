//
//  Triangle.cpp
//  glutapp
//
//  Created by Cindy Hoang on 5/7/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#include "Triangle.h"

void Triangle::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_TRIANGLES);
    
    glVertex3f(x, y-0.1, 0);
    glVertex3f(x+0.1, y-0.1, 0);
    glVertex3f(x+0.05, y, 0);
    
    glEnd();
}

bool Triangle::isLand() {
    return false;
}

bool Triangle::contains(float xx, float yy) {
    if ((x >= xx && x < xx+0.1f && y >= yy && y-0.1f < yy))
        return true;
    return false;
}
