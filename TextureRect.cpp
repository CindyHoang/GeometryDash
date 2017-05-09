//
//  TextureRect.cpp
//  glutapp
//
//  Created by Cindy Hoang on 5/9/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#include "TextureRect.h"

void TextureRect::draw() {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x, y - h);
    
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x, y);
    
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x+w, y);
    
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x+w, y - h);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}
