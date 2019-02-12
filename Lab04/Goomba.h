#pragma once
#include "Actor.h"

class Goomba : public Actor
{
public:
    Goomba(class Game* game);
    void OnUpdate(float deltaTime) override;
    ~Goomba();
    class CollisionComponent* GetCollisionComponent() {
        return cc;
    };
    /*void SetSpriteComponent(SDL_Texture* temp){
        sc->SetTexture(temp);
    };*/
    void SetStomped();
    bool GetStomped(){
        return mStomped;
    }

private:
	//class GoombaMove* gm;
    class CollisionComponent* cc;
    class GoombaMove* gm;
    //class SpriteComponent* sc;
    class AnimatedSprite* asc;
    bool mStomped;
    float mStompTime = 0;
};

