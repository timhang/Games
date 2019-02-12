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
    
    SDL_Texture* GetTexture(std::string FileName);
    void AddAsteroid(class Asteroid* ast);
    void RemoveAsteroid(class Asteroid* ast);
    std::vector<class Asteroid*>& GetAsteroids(){
        return asteroids;
    }
    
    private:
    
    SDL_Window *window;
    SDL_Renderer *renderer = NULL;
    bool isRunning = true;
    
    std::unordered_map<std::string, SDL_Texture*> textures;
    std::vector<class Actor*> actors;
    std::vector<class SpriteComponent*> sprites;
    std::vector<class Asteroid*> asteroids;
    void LoadData();
    void UnloadData();
    
    int r=0;
    int g=0;
    int b=255;
    bool flagR = true;
    bool flagG = true;
    bool flagB = false;
    long time = 0;
    int direction;
};
