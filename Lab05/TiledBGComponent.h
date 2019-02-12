#pragma once
#include "SpriteComponent.h"
#include "SDL/SDL.h"
#include <vector>
#include <unordered_map>
#include <string>

class TiledBGComponent : public SpriteComponent
{
public:
	// (Lower draw order corresponds with further back)
	TiledBGComponent(class Actor* owner, int drawOrder = 50);

	// Update the AnimatedSprite
	void Update(float deltaTime) override;
    
    void Draw(SDL_Renderer* renderer) override;
    
    void LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight);
protected:
    
    int mTileWidth;
    int mTileHeight;
    std::vector<std::vector<int> > mCSV;
};
