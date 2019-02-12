#include "TiledBGComponent.h"
#include "Actor.h"
#include "Game.h"
#include "CSVHelper.h"
#include <iostream>
#include <fstream>

TiledBGComponent::TiledBGComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{
}

void TiledBGComponent::Update(float deltaTime)
{
	// TODO: Implement
    
}



void TiledBGComponent::Draw(SDL_Renderer* renderer){
    if (mTexture)
    {
        SDL_Rect r;
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
        // Center the rectangle around the position of the owner
        r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
        r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);
        r.x -= mOwner->GetGame()->GetCameraPos().x;
        r.y -= mOwner->GetGame()->GetCameraPos().y;
        // Draw (have to convert angle from radians to degrees, and clockwise to counter)
        SDL_RenderCopyEx(renderer,
                         mTexture,
                         nullptr,
                         &r,
                         -Math::ToDegrees(mOwner->GetRotation()),
                         nullptr,
                         SDL_FLIP_NONE);
    }
}

void TiledBGComponent::LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight){
    std::ifstream inFile;
    inFile.open(fileName);
    std::string line;
    int i = 0;
    while(!inFile.eof())
    {
        getline(inFile,line); // Saves the line in STRING.
        //printf("%s\n",line.c_str());
        std::cout<<line<<std::endl;
        if(line.length()>0){
            std::vector<std::string> temp = CSVHelper::Split(line);
            std::vector<int> buffer;
            for(auto iter:temp){
                buffer.push_back(std::stoi(iter));
            }
            mCSV.push_back(buffer);
            i++;
        }
    }
    std::cout<<mCSV[0].size()<<" "<<mCSV.size()<<std::endl;
}
