#include "App.h"

// TODO: Fix where player goes from higher to lower platform
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    
    p = new Player(-0.5f, -0.5f);
    
    welcome = 0;
    
    loop = true;
    hasLanded = true;
    
    loadObstacles();
    
    score = 0.0;
    delay = 5.0;
}

void drawString (void * font, char * s, float x, float y, float z) {
    unsigned int i;
    glRasterPos3f(x, y, z);
    
    for (i = 0; i < strlen(s); i++) {
        glutBitmapCharacter(font, s[i]);
    }
}

void App::loadObstacles() {
    obstacles.push_back(new Obstacle(0.5, -0.5));
//    for (int i = 0; i < 20; i++) {
//        obstacles.push_back(new Obstacle(0.7+(0.2*i), -0.5+(0.1*i)));
//    }
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(0.5+(0.1*i), -0.5));
//    }
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(1.2+(0.1*i), -0.3));
//    }
//    powerups.push_back(new Powerup(0.7, -0.4));
//    powerups.push_back(new Powerup(1.5, -0.2, 1));
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(1.9+(0.1*i), -0.5));
//    }
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(2+(0.1*i), -0.2));
//    }
}
void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set Color
    glColor3d(1.0, 1.0, 1.0);
    
    if (welcome != 0) {
        if (gameover) {
            drawString(GLUT_BITMAP_HELVETICA_18, "Gameover :(", -0.175, 0, 0);
            drawString(GLUT_BITMAP_HELVETICA_12, "Press 'r' to restart the game", -0.25, -0.1, 0);
        }
        
        else {
            // Display score
            drawString(GLUT_BITMAP_HELVETICA_18, "Score: ", -0.75, 0.75, 0);
            drawString(GLUT_BITMAP_HELVETICA_18, pts, -0.5, 0.75, 0);
            sprintf(pts, "%.1f", score);
    
            p->draw();
    
            for (int i = 0; i < obstacles.size(); i++) {
                obstacles[i]->draw();
            }
    
            for (int i = 0; i < powerups.size(); i++) {
                powerups[i]->draw();
            }
        }
    }
    else {
        drawString(GLUT_BITMAP_HELVETICA_18, "Geometry Dash", -0.2, 0, 0);
        drawString(GLUT_BITMAP_HELVETICA_12, "Press any key to begin", -0.2, -0.1, 0);
    }
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

    if (welcome == 0) {
        welcome = 1;
        p->setY(-0.5f);
        hasLanded = true;
        p->shouldJump = false;
        p->shouldLand = false;
        obstacles.clear();
        powerups.clear();
        loadObstacles();
        loop = true;
        gameover = false;
        score = 0;
    }
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27) {
        // Exit the app when Esc key is pressed
        exit(0);
    }
    else if (key == ' ' && hasLanded) {
        // Jump :D
//        if (delay >= 5.0) {
            delay = 0;
            playerY = p->getY();
            p->jump();
//        }
    }
    else if (key == 'r') {
        // Reset the game
        p->setY(-0.5f);
        hasLanded = true;
        p->shouldJump = false;
        p->shouldLand = false;
        p->resetColor();
        obstacles.clear();
        powerups.clear();
        loadObstacles();
        loop = true;
        gameover = false;
        score = 0;
    }
    
    if (welcome == 0) {
        welcome = 1;
        p->setY(-0.5f);
        hasLanded = true;
        p->shouldJump = false;
        p->shouldLand = false;
        p->resetColor();
        obstacles.clear();
        powerups.clear();
        loadObstacles();
        loop = true;
        gameover = false;
        score = 0;
    }
    redraw();
}

void App::idle() {
    if (loop) {
        delay += 0.1f;
        float jumpHeight;
        
        if (p->getR() == 1) {
            jumpHeight = 0.3f;
        }
        else {
            jumpHeight = 0.2f;
        }
        for (int i = 0; i < obstacles.size(); i++) {
            float x = obstacles[i]->getX();
            
            if (obstacles[i]->contains(p->getX(), p->getY())) {
                // Collision check
                gameover = true;
                break;
            }
            
            if (obstacles[i]->isLand() && (obstacles[i]->getX() - p->getX() <= p->getS()) && (p->getY() - obstacles[i]->getY() <= p->getS())) {
                // If the terrain is landable, and the position is correct, we should land
                hasLanded = true;
                p->shouldLand = false;
            }
            
            if (x < p->getX()) {
                // If the obstacle has passed the player, we should be able to fall
                p->shouldLand = true;
            }
            
            if (p->shouldJump && p->getY() - playerY >= jumpHeight) {
                // Setting max height for the jump
                hasLanded = false;
                p->shouldJump = false;
                p->shouldLand = true;
            }
            else if (p->shouldLand) {
                // If player is currently attempting to land, and has reached the floor
                if (x < p->getX()) {
                    hasLanded = false;
                    p->shouldLand = true;
                }
                else if (obstacles.size() && p->getY() <= playerY+0.01) {
                    hasLanded = true;
                    p->shouldLand = false;
                }
            }
 
            obstacles[i]->setX(x - 0.01f);
            score += 0.01;
            
            if (x < -1) {
                // Delete obstacle once it goes off the screen
                obstacles.erase(obstacles.begin());
            }
        }
        
        for (int i = 0; i < powerups.size(); i++) {
            float x = powerups[i]->getX();
            
            powerups[i]->setX(x - 0.01f);
            
            if (powerups[i]->contains(p->getX(), p->getY())) {
                p->setColor(powerups[i]->getR(), powerups[i]->getG(), powerups[i]->getB());
                powerups.erase(powerups.begin());
            }
            
            if (x < -1) {
                powerups.erase(powerups.begin());
            }
            
        }
        
        if (p->shouldJump) {
            hasLanded = false;
            p->setY(p->getY() + 0.01f);
        }
        else if (p->shouldLand) {
            if (p->getY() > -0.5) {
                hasLanded = false;
                p->setY(p->getY() - 0.01f);
            }
        }
    
        if (gameover) {
            loop = false;
        }
        redraw();
    }
}

App::~App() {
    delete p;
    for (int i = 0; i < obstacles.size(); i++) {
        delete obstacles[i];
    }
    obstacles.clear();
}
