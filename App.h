 #ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "Player.h"
#include "Powerup.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Triangle.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
class App: public GlutApp {
    // Maintain app state here
    
    Player* p;
    
    float mx;
    float my;
    
    float missileX;
    float missileY;
    
    int welcome;
    
    float playerY;
    
    bool loop;
    bool gameover;
    bool hasLanded;
    
    float score;
    float delay;
	float speed;
    
    vector<Obstacle*> obstacles;
    vector<Powerup*> powerups;
    
    char pts[25];
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    void loadObstacles();
    // These are the events we want to handle
    virtual void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    
    void idle();
    
    ~App();
};

#endif
