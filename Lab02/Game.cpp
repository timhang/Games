//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include <algorithm>
#include <SDL/SDL_image.h>
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"
// TODO
Game::Game(){
    window = nullptr;
}

bool Game::Initialize(){
    Random::Init();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 0;
    }
    
    
    
    window = SDL_CreateWindow(
                              "Asteroid",
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
    IMG_Init(IMG_INIT_PNG);
    LoadData();
    return true;
}

void Game::RunLoop() {
    while(isRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
        
    }
    
}



//Process Input
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
    std::vector<Actor* > actorsCopy = actors;
    for(auto actor : actorsCopy) {
        actor->ProcessInput(state);
    }
    
}


//Update Game



void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), time + 16)) {
        
    }
    
    float dt = (SDL_GetTicks() - time) / 1000.0f;
    if (dt > 0.033f) {
        dt = 0.033f;
    }
    
    time = SDL_GetTicks();
    std::vector<Actor* > actorsCopy = actors;
    
    for (auto actor : actorsCopy) {
        actor->Update(dt);
    }
    std::vector<Actor*> tempActors;
    for (auto actor : actorsCopy) {
        if(actor->GetState() == ActorState::Destroy) {
            tempActors.push_back(actor);
        }
    }
    
    for(auto temp: tempActors){
        delete temp;
    }
    tempActors.clear();
    /*while (!tempActors.empty())
    {
        delete tempActors.back();
    }*/
    
    
    
}


//Generate Output
void Game::GenerateOutput()
{
    //Insane RGB lighting effects!!
    /*if(flagR){
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
    );*/
    
    //color background
    SDL_RenderClear(renderer);
    //Draw sprites
    for (auto sprite : sprites){
        sprite->Draw(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

void Game::Shutdown1()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Game::AddActor(Actor* ActorToAdd){
    actors.push_back(ActorToAdd);
    
}

void Game::RemoveActor(Actor* ActorToRemove) {
    actors.erase(std::find(actors.begin(),actors.end(),ActorToRemove));
}

void Game::AddAsteroid(Asteroid* asteroid){
    asteroids.push_back(asteroid);
}

void Game::RemoveAsteroid(Asteroid* asteroid){
    asteroids.erase(std::find(asteroids.begin(),asteroids.end(),asteroid));
}

void Game::LoadData() {
    /*Actor* test = new Actor(this);
    SpriteComponent* sc = new SpriteComponent(test);
    sc->SetTexture(GetTexture("Assets/Ship.png"));
    
    //Laser
    Actor* test1 = new Actor(this);
    test1->SetPosition(Vector2(200.0f, 100.0f));
    sc = new SpriteComponent(test1);
    sc->SetTexture(GetTexture("Assets/Laser.png"));
    
    //ShipThrust
    Actor* test2 = new Actor(this);
    test2->SetPosition(Vector2(200.0f,200.0f));
    test2->SetScale(0.75);
    test2->SetRotation(M_PI/2);
    sc = new SpriteComponent(test2);
    sc->SetTexture(GetTexture("Assets/ShipThrust.png"));*/
    
    //Stars
    Actor* test3 = new Actor(this);
    test3->SetPosition(Vector2(512.0f, 384.0f));
    SpriteComponent* sc1 = new SpriteComponent(test3, 50);
    sc1->SetTexture(GetTexture("Assets/Stars.png"));
    
    Ship* ship = new Ship(this);
    ship->SetPosition(Vector2(512.0f, 384.0f));
    
    for(int i = 0; i < 20; i++) {
        new Asteroid(this);
    }
    
}

void Game::UnloadData() {
    while (!actors.empty())
    {
        delete actors.back();
    }
    for (auto iterator:textures)
    {
        SDL_DestroyTexture(iterator.second);
    }
    textures.clear();
}

SDL_Texture* Game::GetTexture(std::string FileName){
    auto value = textures.find(FileName);
    if(value!=textures.end()) {
        return value->second;
    } else {
        SDL_Surface* surface = IMG_Load(FileName.c_str());
        
        if (!surface) {
            SDL_Log("Unable to load image file %s", FileName.c_str());
            return nullptr;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if(!texture) {
            SDL_Log("Unable to create texture from surface from %s",FileName.c_str());
            return nullptr;
        }
        
        textures.emplace(FileName.c_str(), texture);
        return texture;
    }
}

void Game::AddSprite(SpriteComponent* sprite){
    sprites.push_back(sprite);
    std::sort(sprites.begin(), sprites.end(),
              [](SpriteComponent* a, SpriteComponent* b) {
                  return a->GetDrawOrder() < b->GetDrawOrder();
              });
}

void Game::RemoveSprite(SpriteComponent* sprite){
    sprites.erase(std::find(sprites.begin(),sprites.end(),sprite));
}
