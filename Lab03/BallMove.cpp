#include "Game.h"
#include "SpriteComponent.h"
#include "BallMove.h"
#include "Paddle.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Ball.h"
#include "Math.h"
#include "Block.h"
//#include <iostream>
BallMove::BallMove(Actor* owner)
	:MoveComponent(owner)
{
    velocity = Vector2(250.0f,-250.0f);
    //this->SetPosition(Random::GetVector(Vector2(0.0f, 0.0f), Vector2(1024.0f,768.0f)));
    //GetGame()->AddAsteroid(this);
}

void BallMove::Update(float deltaTime) {
    
    mOwner->SetRotation(atan2f((-velocity.y), velocity.x));
    float tempSq = (velocity.x)*(velocity.x) + (velocity.y)*(velocity.y);
    float tempMag = sqrt(tempSq);
    
    if (!Math::NearZero(tempMag))
    {
        Vector2 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * tempMag * deltaTime;
        mOwner->SetPosition(pos);
    }
    
    if (mOwner->GetPosition().x < 42.0f || mOwner->GetPosition().x > 982.0f){
        velocity.x = -velocity.x;
    }
    
    if (mOwner->GetPosition().y < 42.0f){
        
        velocity.y = -velocity.y;
    }
    if (mOwner->GetPosition().y > 768.0f){
        mOwner->SetPosition(Vector2(512.0f, 628.0f));
        velocity = Vector2(250.0f,-250.0f);
    }
    Paddle* paddle = mOwner->GetGame()->GetPaddle();
    if(paddle->GetCollisionComponent()->Intersect(static_cast<Ball* >(mOwner)->GetCollisionComponent()) && velocity.y>0){
        if(mOwner->GetPosition().x - paddle->GetPosition().x >= 17.33f){ // right half
            //std::cout<<velocity.x<<" 1.1 "<<velocity.y<<std::endl;
            velocity = Vector2::Reflect(velocity, Vector2(0.2588190f,-0.9659258f));
            //std::cout<<velocity.x<<" 1.2 "<<velocity.y<<std::endl;
        } else if(mOwner->GetPosition().x - paddle->GetPosition().x <= -17.33f){// left half
            //std::cout<<velocity.x<<" 2.1 "<<velocity.y<<std::endl;
            velocity = Vector2::Reflect(velocity, Vector2(-0.2588190f,-0.9659258f));
            //std::cout<<velocity.x<<" 2.2 "<<velocity.y<<std::endl;
        } else {// middle
            velocity.y = -velocity.y;
        }

    }
    Vector2 offset = Vector2(0,0);
    std::vector<Block*> blocks = mOwner->GetGame()->GetBlocks();
    for(auto block:blocks) {
        CollSide temp = static_cast<Ball* >(mOwner)->GetCollisionComponent()->GetMinOverlap(block->GetCollisionComponent(),offset);
        if(temp==CollSide::Left || temp==CollSide::Right){
            velocity.x = -velocity.x;
            block->SetState(ActorState::Destroy);
            break;
        } else if(temp == CollSide::Top || temp==CollSide::Bottom){
            velocity.y = -velocity.y;
            block->SetState(ActorState::Destroy);
            break;
        }
    }
}

Vector2 BallMove::GetVelocity() {
    return this->velocity;
}

void BallMove::SetVelocity(Vector2 velocity) {
    this->velocity = velocity;
}
