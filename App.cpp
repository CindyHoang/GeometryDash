#include "App.h"

// TODO: Make player rotate while jumping, insert moving autonomous map?
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    
    p = new Player(-0.5f, -0.5f);
    
    loop = true;
    hasLanded = true;
    
    loadObstacles();
}

void App::loadObstacles() {
    for (int i = 0; i < 5; i++) {
        obstacles.push_back(new Obstacle(0.5+(0.1*i), -0.5));
    }
    for (int i = 0; i < 5; i++) {
        obstacles.push_back(new Obstacle(1.2+(0.1*i), -0.3));
    }
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(1.5+(0.1*i), -0.3));
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
    
    p->draw();
    
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->draw();
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
        for (int i = 0; i < obstacles.size(); i++) {
            delete obstacles[i];
        }
        exit(0);
    }
    else if (key == ' ' && hasLanded) {
        // Jump :D
        playerY = p->getY();
        p->jump();
    }
    else if (key == 'r') {
        // Reset the game
        p->setY(-0.5f);
        hasLanded = true;
        p->shouldJump = false;
        p->shouldLand = false;
        obstacles.clear();
        loadObstacles();
        loop = true;
        gameover = false;
    }
    redraw();
}

void App::idle() {
    if (loop) {
        for (int i = 0; i < obstacles.size(); i++) {
            float x = obstacles[i]->getX();
            
            if (obstacles[i]->contains(p->getX(), p->getY())) {
                // Collision check
                gameover = true;
                break;
            }
            
            if (obstacles[i]->isLand() && (obstacles[i]->getX() - p->getX() <= 0.1f) && (p->getY() - obstacles[i]->getY() <= 0.1f)) {
                // If the terrain is landable, and the position is correct, we should land
                hasLanded = true;
                p->shouldLand = false;
            }
            
            if (x < -0.5) {
                p->shouldLand = true;
                
            }
            
            if (p->shouldJump && p->getY() - playerY >= 0.2f) {
                // Setting max height for the jump
                hasLanded = false;
                p->shouldJump = false;
                p->shouldLand = true;
            }
            else if (p->shouldLand) {
                // If player is currently attempting to land, and has reached the floor
                if (x < -0.5) {
                    hasLanded = false;
                }
                else if (obstacles.size() && p->getY() <= playerY+0.01) {
                    hasLanded = true;
                    p->shouldLand = false;
                }
            }
 
            obstacles[i]->setX(x - 0.01f);

            if (x < -1) {
                // Delete obstacle once it goes off the screen
                obstacles.erase(obstacles.begin());
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
}
