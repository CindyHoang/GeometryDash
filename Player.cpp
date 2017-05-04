//
//  Player.cpp
//  glutapp
//
//  Created by Cindy Hoang on 5/3/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#include "Player.h"

void Player::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
    
    glVertex2f(x, y);
    glVertex2f(x+s, y);
    glVertex2f(x+s, y-s);
    glVertex2f(x, y-s);
    
    glEnd();
}

void Player::jump() {
    shouldJump = true;
}
