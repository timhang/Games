//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"

// TODO
Game::Game(){
    window = nullptr;
}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 0;
    }
    
    
    
    window = SDL_CreateWindow(
                              "Pong",
                              100,
                              100,
                              1024,
                              768,
                              0
                              );


    if (window == NULL) {

        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return 0;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return 0;
    }
    
    return true;
}

void Game::RunLoop() {
    while(isRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
        
    }
    
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        switch (event.type)
        {
            
            case SDL_QUIT:
            isRunning = false;
            break;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // When user pressed escape
    if (state[SDL_SCANCODE_ESCAPE]){
        isRunning = false;
    }
    
    //Up and down W/S
    direction = 0;
    if (state[SDL_SCANCODE_W])
    {
        direction = -1;
    }
    if (state[SDL_SCANCODE_S])
    {
        direction = 1;
    }
    
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), time + 16)) {
        
    }
    
    float dt = (SDL_GetTicks() - time) / 1000.0f;
    if (dt > 0.033f) {
        dt = 0.033f;
    }
    
    time = SDL_GetTicks();
    //SDL_log(dt);
    //std::cout<<dt<<std::endl;
    if(direction == 1) {
        paddlePosition.y += 384 * dt;
        if (paddlePosition.y > (768.0 - 50 - thickness))
        {
            paddlePosition.y = 768.0 - 50 - thickness;
        }
    } else if (direction == -1) {
        paddlePosition.y -= 384 * dt;
        if (paddlePosition.y < (50 + thickness))
        {
            paddlePosition.y = 50 + thickness;
        }
    }
    
    ballPosition.x += ballVelocity.x * dt;
    ballPosition.y += ballVelocity.y * dt;
    
    float yDist = ballPosition.y - paddlePosition.y;
    if (yDist<0.0f) {
        yDist = -yDist;
    }
    
    if (yDist <= 50 && ballPosition.x <= 20.0f && ballPosition.x >= 15.0f && ballVelocity.x < 0.0f) {
        ballVelocity.x *= -1.0f;
    }
    // End game if goes over the board
    else if (ballPosition.x <= 0.0f) {
        isRunning = false;
    }
    // Top wall Collision
    else if (ballPosition.y <= thickness && ballVelocity.y < 0.0f) {
        ballVelocity.y *= -1;
    }
    
    // Right Wall Collision
    else if (ballPosition.x >= (1024.0f - thickness) && ballVelocity.x > 0.0f) {
        ballVelocity.x *= -1.0f;
    }
    
    // Bottom Wall Collision
    else if (ballPosition.y >= (768 - thickness) && ballVelocity.y > 0.0f) {
        ballVelocity.y *= -1;
    }
}

void Game::GenerateOutput()
{
    //Insane RGB lighting effects!!
    if(flagR){
        r++;
        if(r>=255) flagR = false;
    } else {
        r--;
        if(r<=0) flagR = true;
    }
    
    if(flagG){
        g++;
        if(g>=255) flagG = false;
    } else {
        g--;
        if(g<=0) flagG = true;
    }
    
    if(flagB){
        b++;
        if(b>=255) flagB = false;
    } else {
        b--;
        if(b<=0) flagB = true;
    }
    
    SDL_SetRenderDrawColor(
        renderer,
        r,
        g,
        b,
        255
    );
    
    //color background
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    
    //top border
    SDL_Rect wall{
        0,
        0,
        1024,
        thickness
    };
    SDL_RenderFillRect(renderer, &wall);
    
    //bottom border
    wall.y = 768 - thickness;
    SDL_RenderFillRect(renderer, &wall);
    
    //right border
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(renderer, &wall);
    
    //draw paddle
    SDL_Rect paddle{
        paddlePosition.x,
        paddlePosition.y - 50,
        thickness,
        100
    };
    SDL_RenderFillRect(renderer, &paddle);
    
    SDL_Rect ball{
        ballPosition.x - thickness/2,
        ballPosition.y - thickness/2,
        thickness,
        thickness
    };
    SDL_RenderFillRect(renderer, &ball);
    
    SDL_RenderPresent(renderer);
}

void Game::Shutdown1()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
