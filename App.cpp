#include "App.h"

// TODO: Make player rotate while jumping, insert moving autonomous map?
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    
    p = new Player(-0.5f, -0.5f);
    
    loop = true;
    
    jCounter = 0; // Counter so user can only jump once at a time
    
    loadObstacles();
}

void App::loadObstacles() {
    for (int i = 0; i < 5; i++) {
        obstacles.push_back(new Obstacle(0.5+(0.1*i), -0.5));
    }
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
    else if (key == ' ' && jCounter == 0) {
        // Jump :D
        playerY = p->getY();
        p->jump();
        jCounter++;
    }
    else if (key == 'r') {
        // Reset the game
        p->setY(-0.5f);
        p->shouldJump = false;
        p->shouldLand = false;
        jCounter = 0;
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
            if (obstacles[i]->contains(p->getX(), p->getY())) {
                gameover = true;
                break;
            }
            
            float x = obstacles[i]->getX();
            obstacles[i]->setX(x - 0.01f);
            
            if (obstacles[i]->isLand() && obstacles[i]->getX() <= p->getX() && p->getY()-obstacles[i]->getY() <= 0.1) {
                p->shouldLand = false;
            }
            
            if (x < -1) {
                // Delete obstacle once it goes off the screen
                obstacles.erase(obstacles.begin());
            }
        }
        
        if (p->shouldJump && p->getY() - playerY >= 0.2f) {
            p->shouldJump = false;
            p->shouldLand = true;
        }
        else if (p->shouldLand && p->getY() == playerY) {
            p->shouldLand = false;
            jCounter = 0;
        }
        
        if (p->shouldJump) {
            p->setY(p->getY() + 0.01f);
        }
        else if (p->shouldLand) {
            p->setY(p->getY() - 0.0075f);
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
