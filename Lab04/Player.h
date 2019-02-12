#pragma once
#include "Actor.h"
#include <string>
class Player : public Actor
{
    
public:
    Player(class Game* game);

    void OnUpdate(float deltaTime) override;
    //class PlayerMove* GetMoveComponent();
    class CollisionComponent* GetCollisionComponent(){
        return cc;
    };
    class AnimatedSprite* GetASC(){
        if(state == false)
            return asc;
        else
            return superAsc;
    };
    void Initialize();
    void InitializeSuper();
    void ChangeState();
    bool GetSuperState(){
        return state;
    }
private:
	class PlayerMove* pm;
    class AnimatedSprite* asc;
    class AnimatedSprite* superAsc;
    bool state = false;
    class CollisionComponent* cc;
    
};

