#include "Game.h"
#include "SpriteComponent.h"
#include "GoombaMove.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Math.h"
#include "Block.h"
#include "Player.h"
#include "Goomba.h"
#include <vector>
//#include <iostream>
GoombaMove::GoombaMove(Actor* owner)
	:MoveComponent(owner)
{

    mYSpeed = 0.0f;
    this->SetForwardSpeed(-100.0f);
    mSpacePressed = false;
    
}

void GoombaMove::ProcessInput(const Uint8 *keyState){
    
}

void GoombaMove::Update(float deltaTime) {
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
    
    Vector2 position = mOwner->GetPosition();
    if (position.y > 448.0f){
        //position.y = 448.0f;
        mOwner->SetState(ActorState::Destroy);
    }
    
    //mOwner->SetPosition(position);
    
    std::vector<Block*> blocks;
    blocks = mOwner->GetGame()->GetBlocks();
    Vector2 offset = Vector2(0,0);
    for(auto block:blocks){
        CollSide temp = static_cast<Goomba* >(mOwner)->GetCollisionComponent()->GetMinOverlap(block->GetCollisionComponent(),offset);
        
        if(temp == CollSide::None){
            
        } else {
            if(temp == CollSide::Top && mYSpeed>0.0f){
                mYSpeed = 0;
            }
             
            /*if(temp == CollSide::Bottom){
                mYSpeed = 0;
            }*/
            if(temp == CollSide::Right || temp == CollSide::Left){
                
                this->SetForwardSpeed(-GetForwardSpeed());
            }
            
            mOwner->SetPosition(mOwner->GetPosition()+offset);
        }
        
    }
    
    std::vector<Goomba*> enemies = mOwner->GetGame()->GetEnemies();
    for(auto enemy:enemies){
        if(enemy!=mOwner){
            CollSide temp = static_cast<Goomba* >(mOwner)->GetCollisionComponent()->GetMinOverlap(enemy->GetCollisionComponent(),offset);
            
            if(temp == CollSide::None){
                
            } else {
                if(temp == CollSide::Right || temp == CollSide::Left){
                    
                    this->SetForwardSpeed(-GetForwardSpeed());
                }
                mOwner->SetPosition(mOwner->GetPosition()+offset);
            }
        }
    }
    
    mYSpeed+=deltaTime*2000.0f;
    
    //Part 2 Scrolling Camera 1
    /*Vector2 temp = mOwner->GetGame()->GetCameraPos();
    Vector2 tempPos = mOwner->GetPosition();
    if(tempPos.x < (temp.x+16.0f)){
        tempPos.x = (temp.x+16.0f);
    }
    mOwner->SetPosition(tempPos);*/
    
}



