#pragma once
#include "Actor.h"

class Coin : public Actor
{
public:
    Coin(class Game* game, bool state);
    void OnUpdate(float deltaTime) override;
    ~Coin();
    class CollisionComponent* GetCollisionComponent() {
        return cc;
    };
    void SetSpriteComponent(SDL_Texture* temp){
        sc->SetTexture(temp);
    };
    void SetStomped(){
        mStomped = true;
    };
    bool GetStomped(){
        return mStomped;
    }
    bool GetState(){
        return mState;
    }

private:
    bool mState;
    class CollisionComponent* cc;
    class SpriteComponent* sc;
    class MoveComponent* mc;
    bool mStomped;
    float mStompTime = 0;
    float mYSpeed = 0;
};

