#include "Game.h"
#include "SpriteComponent.h"
#include "Paddle.h"
#include "Random.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
Paddle::Paddle(Game* game)
	:Actor(game)
{
    sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Paddle.png"));
    mc = new MoveComponent(this);
    cc = new CollisionComponent(this);
    cc->SetSize(104.0f, 24.0f);
}


void Paddle::OnProcessInput(const Uint8 *keyState){
    
    mc->SetForwardSpeed(0.0f);
    //mc->SetAngularSpeed(0.0f);

    
    if (keyState[SDL_SCANCODE_LEFT]){
        mc->SetForwardSpeed(-600.0f);
    } else if (keyState[SDL_SCANCODE_RIGHT]){
        mc->SetForwardSpeed(600.0f);
    }
    
    //mc->SetAngularSpeed(0.0f);
    //mc->SetForwardSpeed(0.0f);
}

void Paddle::OnUpdate(float deltaTime) {
    //interval -= deltaTime;
    Vector2 position = this->GetPosition();
    if (position.x < 84.0f){
        position.x = 84.0f;
    } else if (position.x > 940.0f){
        position.x = 940.0f;
    }
    

    this->SetPosition(position);
}

CollisionComponent* Paddle::GetCollisionComponent() {
    return cc;
}
