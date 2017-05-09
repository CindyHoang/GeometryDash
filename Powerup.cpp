//
//  Powerup.cpp
//  glutapp
//
//  Created by Cindy Hoang on 5/7/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#include "Powerup.h"

void Powerup::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
    
    glVertex2f(x, y);
    glVertex2f(x+w, y);
    glVertex2f(x+w, y-h);
    glVertex2f(x, y-h);
    
    glEnd();
}
