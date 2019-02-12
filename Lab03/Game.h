#pragma once

#include "SDL/SDL.h"
#include <vector>
#include <unordered_map>
#include <string>

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
    void AddActor(class Actor* ActorToAdd);
    void RemoveActor(class Actor* ActorToRemove);
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    void GenerateBlocksFromFile(std::string name);
    void GenerateBlocks(std::string line, int row);
    SDL_Texture* GetTexture(std::string FileName);
    class Paddle* GetPaddle();
    
    void AddBlock(class Block* block);
    void RemoveBlock(class Block* block);
    std::vector<class Block*>& GetBlocks(){
        return blocks;
    }
    
    private:
    
    SDL_Window *window;
    SDL_Renderer *renderer = NULL;
    bool isRunning = true;
    
    std::unordered_map<std::string, SDL_Texture*> textures;
    std::vector<class Actor*> actors;
    std::vector<class SpriteComponent*> sprites;
    std::vector<class Block*> blocks;
    void LoadData();
    void UnloadData();
    class Paddle * paddle;
    int r=0;
    int g=0;
    int b=255;
    bool flagR = true;
    bool flagG = true;
    bool flagB = false;
    long time = 0;
    int direction;
};
