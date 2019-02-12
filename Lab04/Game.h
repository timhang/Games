#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "Math.h"


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
    Mix_Chunk* GetSound(const std::string& filename);
    
    void AddBlock(class Block* block);
    void RemoveBlock(class Block* block);
    std::vector<class Block*>& GetBlocks(){
        return blocks;
    }
    
    void AddEnemy(class Goomba* enemy);
    void RemoveEnemy(class Goomba* enemy);
    std::vector<class Goomba*>& GetEnemies(){
        return enemies;
    }
    
    void AddCoin(class Coin* coin);
    void RemoveCoin(class Coin* coin);
    std::vector<class Coin*>& GetCoins(){
        return coins;
    }
    
    Vector2 GetCameraPos(){
        return mCameraPos;
    }
    void SetCameraPos(Vector2 pos){
        mCameraPos = pos;
    }
    class Player* GetPlayer();
    
    int GetChannel(){
        return mChannel;
    }
    void IncrementScore(){
        mScore++;
    }

    private:
    
    SDL_Window *window;
    SDL_Renderer *renderer = NULL;
    bool isRunning = true;
    
    int mScore = 0;
    class Player* player;
    class Actor* scoreActor0;
    class Actor* scoreActor1;
    Vector2 mCameraPos;
    std::unordered_map<std::string, SDL_Texture*> textures;
    std::unordered_map<std::string, Mix_Chunk*> sounds;
    std::vector<class Actor*> actors;
    std::vector<class SpriteComponent*> sprites;
    std::vector<class Block*> blocks;
    std::vector<class Goomba*> enemies;
    std::vector<class Coin*> coins;
    void LoadData();
    void UnloadData();
    
    int mChannel;
    int r=0;
    int g=0;
    int b=255;
    bool flagR = true;
    bool flagG = true;
    bool flagB = false;
    long time = 0;
    int direction;
};
