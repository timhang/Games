#include "Game.h"
#include "SpriteComponent.h"
#include "Spawner.h"
#include "CollisionComponent.h"
#include "Math.h"
#include "Goomba.h"
#include "Player.h"
Spawner::Spawner(Game* game)
	:Actor(game)
{
    
}

void Spawner::OnUpdate(float deltaTime) {
    Vector2 temp = this->GetPosition();
    if(Math::Abs(temp.x-(this->GetGame()->GetPlayer()->GetPosition().x))<600){
        Goomba* goomba = new Goomba(this->GetGame());
        goomba->SetPosition(this->GetPosition());
        this->SetState(ActorState::Destroy);
    }
}


