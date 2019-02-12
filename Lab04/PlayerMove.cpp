#include "Game.h"
#include "SpriteComponent.h"
#include "PlayerMove.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "Math.h"
#include "Block.h"
#include "Player.h"
#include "Goomba.h"
#include "Coin.h"
#include <vector>
//#include <iostream>
PlayerMove::PlayerMove(Actor* owner)
	:MoveComponent(owner)
{

    mYSpeed = 0.0f;
    mSpacePressed = false;
    mInAir = false;
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    SetForwardSpeed(0.0f);
    //mc->SetAngularSpeed(0.0f);
    if(!mInAir)
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("idle");
    
    
    if (keyState[SDL_SCANCODE_LEFT]){
        SetForwardSpeed(-300.0f);
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("runLeft");
    } else if (keyState[SDL_SCANCODE_RIGHT]){
        SetForwardSpeed(300.0f);
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("runRight");
    }
    
    if(keyState[SDL_SCANCODE_SPACE]&&!mSpacePressed&&!mInAir){
        if(static_cast<Player* >(mOwner)->GetSuperState()==false){
            Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav");
            if(Mix_PlayChannel(-1, sample, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        } else {
            Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/JumpSuper.wav");
            if(Mix_PlayChannel(-1, sample, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
        
        mYSpeed = -700.0f;
        mInAir = true;
        mSpacePressed = true;
        
    }
    if(mInAir){
        if(GetForwardSpeed()<0){
            static_cast<Player* >(mOwner)->GetASC()->SetAnimation("jumpLeft");
        } else if (GetForwardSpeed()>0){
            static_cast<Player* >(mOwner)->GetASC()->SetAnimation("jumpRight");
        } else {
            if(static_cast<Player* >(mOwner)->GetASC()->GetAnimName() == "runRight" ||
               static_cast<Player* >(mOwner)->GetASC()->GetAnimName() == "jumpRight" ||
               static_cast<Player* >(mOwner)->GetASC()->GetAnimName() == "idle"){
                static_cast<Player* >(mOwner)->GetASC()->SetAnimation("jumpRight");
            } else {
                static_cast<Player* >(mOwner)->GetASC()->SetAnimation("jumpLeft");
            }
        }
    }
    if(!keyState[SDL_SCANCODE_SPACE]){
        mSpacePressed = false;
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
    
    Vector2 position = mOwner->GetPosition();
    if (position.y > 448.0f){
        mInAir = false;
        //position.y = 448.0f;
        static_cast<Player* >(mOwner)->GetASC()->SetAnimation("dead");
        static_cast<Player* >(mOwner)->SetState(ActorState::Paused);
        Mix_HaltChannel(mOwner->GetGame()->GetChannel());
        Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav");
        if(Mix_PlayChannel(-1, sample, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    }
    
    //mOwner->SetPosition(position);
    
    std::vector<Block*> blocks;
    blocks = mOwner->GetGame()->GetBlocks();
    Vector2 offset = Vector2(0,0);
    bool collide = false;
    for(auto block:blocks){
        CollSide temp = static_cast<Player* >(mOwner)->GetCollisionComponent()->GetMinOverlap(block->GetCollisionComponent(),offset);
        
        if(temp == CollSide::None){
            
        } else {
            collide = true;
            if(temp == CollSide::Top && mYSpeed>0.0f){
                mInAir = false;
                mYSpeed = 0;
            }
            if(temp == CollSide::Bottom){
                mYSpeed = 0;
                
                if(block->GetType() == 'C'){
                    block->ChangeTexture('E');
                    if(state == true){ //if first question mark then mushroom
                        state = false;
                        Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/Mushroom.wav");
                        if(Mix_PlayChannel(-1, sample, 0)==-1) {
                            printf("Mix_PlayChannel: %s\n",Mix_GetError());
                        }
                        
                        Coin* coin = new Coin(mOwner->GetGame(),0);
                        
                        coin->SetPosition(Vector2(block->GetPosition().x, block->GetPosition().y - 32));
                        
                    } else { //after first question mark, coins
                        
                        
                        Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/Coin.wav");
                        if(Mix_PlayChannel(-1, sample, 0)==-1) {
                            printf("Mix_PlayChannel: %s\n",Mix_GetError());
                        }
                        
                        Coin* coin = new Coin(mOwner->GetGame(),1);

                        coin->SetPosition(Vector2(block->GetPosition().x, block->GetPosition().y - 32));

                    }
                } else {
                    Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/Bump.wav");
                    if(Mix_PlayChannel(-1, sample, 0)==-1) {
                        printf("Mix_PlayChannel: %s\n",Mix_GetError());
                    }
                }
            }
            mOwner->SetPosition(mOwner->GetPosition()+offset);
        }
        
    }
    if(!collide){
        mInAir = true;
    }
    std::vector<Coin*> coins = mOwner->GetGame()->GetCoins();
    for(auto coin:coins){
        if(!(coin->GetStomped())){
            CollSide temp = static_cast<Player* >(mOwner)->GetCollisionComponent()->GetMinOverlap(coin->GetCollisionComponent(),offset);
            if(temp != CollSide::None){
                mOwner->GetGame()->IncrementScore();
                coin->SetStomped();
                if(coin->GetState()==false){
                    static_cast<Player* >(mOwner)->ChangeState();
                }
            }
        }
    }
    
    std::vector<Goomba*> enemies = mOwner->GetGame()->GetEnemies();
    for(auto enemy:enemies){
        if(!(enemy->GetStomped())){
            CollSide temp = static_cast<Player* >(mOwner)->GetCollisionComponent()->GetMinOverlap(enemy->GetCollisionComponent(),offset);
            
            if(temp == CollSide::None){
                
            } else {
                if(temp == CollSide::Top || ((temp == CollSide::Right || temp == CollSide::Left) && mInAir)){
                    enemy->SetStomped();
                    mOwner->GetGame()->IncrementScore();
                    mOwner->GetGame()->IncrementScore();
                    mYSpeed = -350.0f;
                    Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/Stomp.wav");
                    if(Mix_PlayChannel(-1, sample, 0)==-1) {
                        printf("Mix_PlayChannel: %s\n",Mix_GetError());
                    }
                    mInAir = true;
                } else {
                    static_cast<Player* >(mOwner)->GetASC()->SetAnimation("dead");
                    static_cast<Player* >(mOwner)->SetState(ActorState::Paused);
                    Mix_HaltChannel(mOwner->GetGame()->GetChannel());
                    Mix_Chunk *sample = mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav");
                    if(Mix_PlayChannel(-1, sample, 0)==-1) {
                        printf("Mix_PlayChannel: %s\n",Mix_GetError());
                    }
                }
                mOwner->SetPosition(mOwner->GetPosition()+offset);
            }
        }
    }
    
    mYSpeed+=deltaTime*2000.0f;
    
    //Part 2 Scrolling Camera 1
    Vector2 temp = mOwner->GetGame()->GetCameraPos();
    Vector2 tempPos = mOwner->GetPosition();
    if(tempPos.x < (temp.x+16.0f)){
        tempPos.x = (temp.x+16.0f);
    }
    mOwner->SetPosition(tempPos);
    if(mOwner->GetPosition().x-300.0f>temp.x){
        temp.x = mOwner->GetPosition().x-300.0f;
        mOwner->GetGame()->SetCameraPos(temp);
    }
    
}



