//
//  Obstacle.cpp
//  glutapp
//
//  Created by Cindy Hoang on 5/3/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#include "Obstacle.h"

void Obstacle::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
    
    glVertex2f(x, y);
    glVertex2f(x+w, y);
    glVertex2f(x+w, y-h);
    glVertex2f(x, y-h);
    
    glEnd();
}

bool Obstacle::contains(float xx, float yy) {
    if ((x >= xx && x <= xx+0.1 && y >= yy))
        return true;
    return false;
}
