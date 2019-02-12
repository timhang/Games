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
#include "Random.h"
#include "Block.h"
#include "Spawner.h"
#include "Player.h"
#include <iostream>
#include <fstream>
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
                              "Mario",
                              100,
                              100,
                              600,
                              448,
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
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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
    
    int first = mScore % 10;
    int second = mScore/10;
    std::string filename0 = "Assets/Numbers/" + std::to_string(first) + ".png";
    
    std::string filename1 = "Assets/Numbers/" + std::to_string(second) + ".png";
    
    scoreActor0->SetPosition(Vector2((GetCameraPos().x+584.0f),16.0f));
    scoreActor1->SetPosition(Vector2((GetCameraPos().x+552.0f),16.0f));
    
    SpriteComponent* gameScore0 = new SpriteComponent(scoreActor0, 300);
    gameScore0->SetTexture(GetTexture(filename0));
    
    SpriteComponent* gameScore1 = new SpriteComponent(scoreActor1, 300);
    gameScore1->SetTexture(GetTexture(filename1));
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
    */
    
    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        255,
        255
    );
    
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
    Mix_CloseAudio();
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



void Game::GenerateBlocksFromFile(std::string name){
    std::ifstream inFile;
    inFile.open(name);
    std::string line;
    int i = 0;
    while(!inFile.eof())
    {
        getline(inFile,line); // Saves the line in STRING.
        //printf("%s\n",line.c_str());
        GenerateBlocks(line, i);
        i++;
    }
    
}
void Game::GenerateBlocks(std::string line, int row){
    for(int column = 0; column < line.length(); column++){
        if(line[column]!='.'&&line[column]!='P'&&line[column]!='Y' ){
            /*std::string s;
            s.push_back(line[column]);*/
            new Block(this,line[column],column,row);
            /*block->SetPosition(Vector2((64.0f + column * 64), (48.0f + row * 32)));
            blocks.push_back(block);*/
        }
        if(line[column]=='P'){
            player = new Player(this);
            player->SetPosition(Vector2((16.0f+column*32),(16.0f+row*32)));
            //player->ChangeState();
        }
        if(line[column]=='Y'){
            Spawner* spawner = new Spawner(this);
            spawner->SetPosition(Vector2((16.0f+column*32),(16.0f+row*32)));
        }
    }
}



void Game::LoadData() {
    Actor* background = new Actor(this);
    background->SetPosition(Vector2(3392.0f, 224.0f));
    SpriteComponent* sc = new SpriteComponent(background, 25);
    sc->SetTexture(GetTexture("Assets/Background.png"));
    
    scoreActor0 = new Actor(this);
    scoreActor0->SetPosition(Vector2((GetCameraPos().x+584.0f),16.0f));
    SpriteComponent* gameScore0 = new SpriteComponent(scoreActor0, 300);
    gameScore0->SetTexture(GetTexture("Assets/Numbers/0.png"));
    
    scoreActor1 = new Actor(this);
    scoreActor1->SetPosition(Vector2((GetCameraPos().x+552.0f),16.0f));
    SpriteComponent* gameScore1 = new SpriteComponent(scoreActor1, 300);
    gameScore1->SetTexture(GetTexture("Assets/Numbers/0.png"));
    
    Mix_Chunk *sample = GetSound("Assets/Sounds/Music.ogg");
    mChannel = Mix_PlayChannel(-1, sample, -1);
    
    GenerateBlocksFromFile("Assets/Level1.txt");
}
void Game::UnloadData() {
    while (!actors.empty())
    {
        delete actors.back();
    }
    /*for(auto actor: actors){
        delete actor;
    }
    actors.clear();*/
    for (auto iterator:textures)
    {
        SDL_DestroyTexture(iterator.second);
    }
    textures.clear();
    for (auto iterator:sounds)
    {
        Mix_FreeChunk(iterator.second);
    }
    sounds.clear();
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

Mix_Chunk* Game::GetSound(const std::string &filename){
    auto value = sounds.find(filename);
    if(value!=sounds.end()) {
        return value->second;
    } else {
        Mix_Chunk *sound;
        sound=Mix_LoadWAV(filename.c_str());
        if(!sound) {
            SDL_Log("Unable to load sound file %s", filename.c_str());
            return nullptr;
            // handle error
        }
        
        sounds.emplace(filename.c_str(), sound);
        return sound;
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



void Game::AddBlock(Block* block){
    blocks.push_back(block);
}
void Game::RemoveBlock(Block* block){
    blocks.erase(std::find(blocks.begin(),blocks.end(),block));
}

void Game::AddEnemy(class Goomba* enemy){
    enemies.push_back(enemy);
}
void Game::RemoveEnemy(class Goomba* enemy){
    enemies.erase(std::find(enemies.begin(),enemies.end(),enemy));
}

void Game::AddCoin(class Coin* coin){
    coins.push_back(coin);
}
void Game::RemoveCoin(class Coin* coin){
    coins.erase(std::find(coins.begin(),coins.end(),coin));
}

Player* Game::GetPlayer(){
    return player;
}

