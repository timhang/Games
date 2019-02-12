#include "Game.h"
#include "SpriteComponent.h"
#include "Coin.h"
#include "CollisionComponent.h"
#include "Block.h"
#include "MoveComponent.h"
Coin::Coin(Game* game, bool state)
	:Actor(game)
{
    mState = state;
    sc = new SpriteComponent(this);
    
    if(mState){
        sc->SetTexture(game->GetTexture("Assets/Coin.png"));
    } else {
        sc->SetTexture(game->GetTexture("Assets/Mushroom.png"));
        mc = new MoveComponent(this);
        mc->SetForwardSpeed(-100);
    }
    
    cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);

    mStomped = false;
    GetGame()->AddCoin(this);
}

void Coin::OnUpdate(float deltaTime){
    if(mStomped){
        mStompTime+=deltaTime;
        if(mStompTime>=0.15f){
            this->SetState(ActorState::Destroy);
        }
    }
    if(!mState){
        if (!Math::NearZero(mYSpeed))
        {
            Vector2 pos = GetPosition();
            pos.y += mYSpeed * deltaTime;
            
            SetPosition(pos);
        }
        
        Vector2 position = GetPosition();
        if (position.y > 448.0f){
            //position.y = 448.0f;
            SetState(ActorState::Destroy);
        }
        
        //mOwner->SetPosition(position);
        
        std::vector<Block*> blocks;
        blocks = GetGame()->GetBlocks();
        Vector2 offset = Vector2(0,0);
        for(auto block:blocks){
            CollSide temp = cc->GetMinOverlap(block->GetCollisionComponent(),offset);
            
            if(temp == CollSide::None){
                
            } else {
                if(temp == CollSide::Top && mYSpeed>0.0f){
                    mYSpeed = 0;
                }
                
                /*if(temp == CollSide::Bottom){
                 mYSpeed = 0;
                 }*/
                /*if(temp == CollSide::Right || temp == CollSide::Left){
                    
                    mc->SetForwardSpeed(-(mc->GetForwardSpeed()));
                }*/
                
                SetPosition(GetPosition()+offset);
            }
            
        }
        
        mYSpeed+=deltaTime*2000.0f;
        
    }
}

Coin::~Coin() {
    GetGame()->RemoveCoin(this);
}


