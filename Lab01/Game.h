#pragma once

#include "SDL/SDL.h"
#include "iostream"
// TODO
class Game {
    public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void Shutdown1();
    private:
    SDL_Window *window;
    SDL_Renderer *renderer = NULL;
    bool isRunning = true;
    const int thickness = 10;
    SDL_Point paddlePosition{thickness,768/2};
    SDL_Point ballPosition{1024/2,768/2};
    SDL_Point ballVelocity{1024/5,768/3};
    int r=0;
    int g=0;
    int b=255;
    bool flagR = true;
    bool flagG = true;
    bool flagB = false;
    long time = 0;
    int direction;
};
