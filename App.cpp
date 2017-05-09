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
    highscore = 0.0;
    delay = 5.0;
    
    missileX = 0.74;
    missileY = -0.55;
    
#if defined WIN32
    wall = loadTexture("..\\bg.bmp");
#else
    wall = loadTexture("bg.bmp");
#endif
    
    bg = new TextureRect(-1, 1, 2, 2);
}

void drawString (void * font, char * s, float x, float y, float z) {
    unsigned int i;
    glRasterPos3f(x, y, z);
    
    for (i = 0; i < strlen(s); i++) {
        glutBitmapCharacter(font, s[i]);
    }
}

void App::loadObstacles() {
//    obstacles.push_back(new Obstacle(0.5, -0.5));
//    obstacles.push_back(new Triangle(0.7, -0.5));
//    for (int i = 0; i < 20; i++) {
//        obstacles.push_back(new Obstacle(0.7+(0.2*i), -0.5+(0.1*i)));
//    }
    
    obstacles.push_back(new Triangle(0.5, -0.5));
    obstacles.push_back(new Enemy(1.5, -0.5));
//    obstacles.push_back(new Triangle(1.5, -0.5));
//    obstacles.push_back(new Triangle(1.6, -0.5));
    for (int i = 0; i < 5; i++) {
        obstacles.push_back(new Obstacle(2.5+(0.1*i), -0.5));
    }
    for (int i = 0; i < 3; i++) {
        obstacles.push_back(new Triangle(3.025+(0.1*i), -0.5));
    }
    for (int i = 0; i < 5; i++) {
        obstacles.push_back(new Obstacle(3.35+(0.1*i), -0.5));
    }
    for (int i = 0; i < 2; i++) {
        obstacles.push_back(new Obstacle(5+(0.1*i), -0.5));
    }
    for (int i = 0; i < 2; i++) {
        obstacles.push_back(new Obstacle(5.5+(0.1*i), -0.35));
    }
    for (int i = 0; i < 5; i++) {
        obstacles.push_back(new Obstacle(6+(0.1*i), -0.2));
    }
    for (int i = 0; i < 2; i++) {
        obstacles.push_back(new Obstacle(6.6+(0.1*i), -0.35));
    }
    for (int i = 0; i < 2; i++) {
        obstacles.push_back(new Obstacle(6.9+(0.1*i), -0.5));
    }
//    for (int i = 0; i < 3; i++) {
//        obstacles.push_back(new Obstacle(4.2+(0.1*i), -0.5+(0.2*i)));
//        obstacles.push_back(new Obstacle(4.2+(0.2*i), -0.5+(0.2*i)));
//    }
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(0.5+(0.1*i), -0.5));
//    }
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(1.2+(0.1*i), -0.4));
//    }
//    powerups.push_back(new Powerup(0.7, -0.4));
//    powerups.push_back(new Powerup(1.5, -0.2, 1));
//    for (int i = 0; i < 5; i++) {
//        obstacles.push_back(new Obstacle(2+(0.1*i), -0.2));
//    }
}

GLuint App::loadTexture(const char *filename) {
    GLuint texture_id;
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    RgbImage theTexMap( filename );
    
    glGenTextures( 1, &texture_id );
    glBindTexture( GL_TEXTURE_2D, texture_id );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    
    return texture_id;
    
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
            
            glBindTexture(GL_TEXTURE_2D, wall);
            bg->draw();
            glDisable(GL_TEXTURE_2D);
        }
        
        else {
            // Display score
            drawString(GLUT_BITMAP_HELVETICA_18, "Score: ", -0.75, 0.75, 0);
            drawString(GLUT_BITMAP_HELVETICA_18, pts, -0.5, 0.75, 0);
            sprintf(pts, "%.1f", score);
            
            drawString(GLUT_BITMAP_HELVETICA_18, "Highscore: ", 0.25, 0.75, 0);
            drawString(GLUT_BITMAP_HELVETICA_18, recordPts, 0.6, 0.75, 0);
            sprintf(recordPts, "%.1f", highscore);
    
            p->draw();
    
            for (int i = 0; i < obstacles.size(); i++) {
                obstacles[i]->draw();
                
                if (obstacles[i]->canFire() && obstacles[i]->missile && !gameover) {
                    Obstacle* pew = new Obstacle(missileX, missileY, false, 0.02f, 0.02f, 1, 1, 1);
                    pew->draw();
                }
            }
    
            for (int i = 0; i < powerups.size(); i++) {
                powerups[i]->draw();
            }

        }
    }
    else {
        drawString(GLUT_BITMAP_HELVETICA_18, "Geometry Dash", -0.2, 0, 0);
        drawString(GLUT_BITMAP_HELVETICA_12, "Press any key to begin", -0.2, -0.1, 0);
        
        glBindTexture(GL_TEXTURE_2D, wall);
        bg->draw();
        glDisable(GL_TEXTURE_2D);
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
        if (score > highscore) {
            highscore = score;
        }
        p->setY(-0.5f);
        missileX = 0.74;
        missileY = -0.55;
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
        missileX = 0.74;
        missileY = -0.55;
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
        highscore = 0;
    }
    redraw();
}

void App::idle() {
    if (loop) {
//        delay += 0.1f;
        float jumpHeight = 0.25f;
        
//        if (p->getR() == 1) {
//            jumpHeight = 0.3f;
//        }
//        else {
//            jumpHeight = 0.2f;
//        }
        
        for (int i = 0; i < obstacles.size(); i++) {
            float x = obstacles[i]->getX();
            
            if (p->contains(obstacles[i]->getX(), obstacles[i]->getY(), obstacles[i]->getW(), obstacles[i]->getH())) {
                // Collision check
                gameover = true;
                break;
            }
            
            if (obstacles[i]->canFire() && obstacles[i]->getX() <= 0.75) {
                obstacles[i]->missile = true;
                missileX -= 0.02f;
            }
            
            if (p->contains(missileX, missileY, 0.02f, 0.02f)) {
                gameover = true;
                break;
            }
            
            if (missileX < -1) {
                obstacles[i]->missile = false;
            }
            
            if ((!obstacles[i]->passedUser) && (obstacles[i]->getX() <= p->getX() + p->getS()) && (obstacles[i]->getX() > p->getX()) && (p->getY() > obstacles[i]->getY()+0.09f) && (p->getY() <= obstacles[i]->getY()+0.1f)) {
                if (obstacles[i]->isLand()) {
                    // If the terrain is landable, and the position is correct, we should land
                    hasLanded = true;
                    p->shouldLand = false;
                }
                else {
                    gameover = true;
                    break;
                }
            }
            
            if (obstacles[i]->getX()+0.1f < p->getX()) {
                // If the obstacle has passed the player, we should be able to fall
                p->shouldLand = true;
                obstacles[i]->passedUser = true;
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
                else if (obstacles.size() && p->getY() <= -0.5f) {
                    hasLanded = true;
                    p->shouldLand = false;
                }
            }
 
            obstacles[i]->setX(x - 0.0125f);
            score += 0.01;
            
            if (x < -1) {
                // Delete obstacle once it goes off the screen
                obstacles.erase(obstacles.begin());
            }
        }
        
        for (int i = 0; i < powerups.size(); i++) {
            float x = powerups[i]->getX();
            
            powerups[i]->setX(x - 0.01f);
            
            if (p->contains(powerups[i]->getX(), powerups[i]->getY(), powerups[i]->getW(), powerups[i]->getH())) {
                p->setColor(powerups[i]->getR(), powerups[i]->getG(), powerups[i]->getB());
                powerups.erase(powerups.begin());
            }
            
            if (x < -1) {
                powerups.erase(powerups.begin());
            }
            
        }
    
        if (p->shouldJump) {
            hasLanded = false;
            p->setY(p->getY() + 0.0125f);
        }
        else if (p->shouldLand) {
            if (p->getY() > -0.5) {
                hasLanded = false;
                p->setY(p->getY() - 0.0125f);
            }
        }
        
        if (gameover) {
            loop = false;
            if (score > highscore) {
                highscore = score;
            }
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
