#include "Game.h"
#include "SpriteComponent.h"
#include "PlayerMove.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "Math.h"
#include "Player.h"
#include <vector>
//#include <iostream>
PlayerMove::PlayerMove(Actor* owner)
	:MoveComponent(owner)
{

    mYSpeed = 0.0f;
    mXSpeed = 0.0f;
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    //SetForwardSpeed(0.0f);
    //mc->SetAngularSpeed(0.0f);
    static_cast<Player* >(mOwner)->GetASC()->SetIsPaused(true);
    
    
    if (keyState[SDL_SCANCODE_LEFT]){
        mXSpeed = -130.0f;
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("walkLeft");
        static_cast<Player* >(mOwner)->SetDirection(PlayerDirection::Left);
        static_cast<Player* >(mOwner)->GetASC()->SetIsPaused(false);
        
    } else if (keyState[SDL_SCANCODE_RIGHT]){
        mXSpeed = 130.0f;
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("walkRight");
        static_cast<Player* >(mOwner)->SetDirection(PlayerDirection::Right);
        static_cast<Player* >(mOwner)->GetASC()->SetIsPaused(false);
    } else if (keyState[SDL_SCANCODE_UP]) {
        mYSpeed = -130.0f;
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("walkUp");
        static_cast<Player* >(mOwner)->SetDirection(PlayerDirection::Up);
        static_cast<Player* >(mOwner)->GetASC()->SetIsPaused(false);
    } else if (keyState[SDL_SCANCODE_DOWN]){
        mYSpeed = 130.0f;
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("walkDown");
        static_cast<Player* >(mOwner)->SetDirection(PlayerDirection::Down);
        static_cast<Player* >(mOwner)->GetASC()->SetIsPaused(false);
    }
    
    
}
void PlayerMove::Update(float deltaTime) {
    if (!Math::NearZero(GetForwardSpeed()))
    {
        Vector2 pos = mOwner->GetPosition();
        pos.x += GetForwardSpeed() * deltaTime;
        
        mOwner->SetPosition(pos);
    }
    
    if (!Math::NearZero(mYSpeed))
    {
        Vector2 pos = mOwner->GetPosition();
        pos.y += mYSpeed * deltaTime;
        
        mOwner->SetPosition(pos);
    }
    
    Vector2 tempPos = mOwner->GetPosition();
    mOwner->GetGame()->SetCameraPos(Vector2(tempPos.x-300,tempPos.y-224));
}



