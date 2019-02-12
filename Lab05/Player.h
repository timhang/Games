#pragma once
#include "Actor.h"
#include <string>
enum class PlayerDirection
{
    Up,
    Down,
    Left,
    Right
};

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
        return asc;
    };
    void Initialize();
    void InitializeSuper();
    void ChangeState();
    PlayerDirection GetDirection(){
        return mDirection;
    }
    void SetDirection(PlayerDirection direction){
        mDirection = direction;
    }
private:
	class PlayerMove* pm;
    class AnimatedSprite* asc;
    class CollisionComponent* cc;
    PlayerDirection mDirection;
};

