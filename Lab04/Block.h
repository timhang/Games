#pragma once
#include "Actor.h"
#include <string>
class Block : public Actor
{
public:
    Block(class Game* game);
    Block(class Game* game, char texture, int column, int row);
    ~Block();
    void ChangeTexture(char texture);
    class CollisionComponent* GetCollisionComponent() {
        return cc;
    }
    char GetType(){
        return mType;
    }
private:
	std::string mTexture;
    class CollisionComponent* cc;
    char mType;
};

