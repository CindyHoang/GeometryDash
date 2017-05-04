#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "Player.h"
#include "Obstacle.h"
#include <vector>
#include <iostream>

using namespace std;
class App: public GlutApp {
    // Maintain app state here
    
    Player* p;
    
    float mx;
    float my;
    
    float playerY;
    
    int jCounter;
    
    bool loop;
    bool gameover;
    
    vector<Obstacle*> obstacles;
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    void loadObstacles();
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    
    void idle();
    
    ~App();
};

#endif
