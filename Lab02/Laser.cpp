#include "Laser.h"

#include "Game.h"
#include "Asteroid.h"
#include "Math.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Laser::Laser(Game* game)
	:Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Laser.png"));
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(400.0f);

}

void Laser::OnUpdate(float deltaTime){
    // (Screen wrapping code only for asteroids)
    lifetime-=deltaTime;
    if(lifetime<=0.0f) {
        this->SetState(ActorState::Destroy);
    }
    std::vector<Asteroid *> tempAst = GetGame()->GetAsteroids();
    for(auto asteroid:tempAst) {
        if ((asteroid->GetPosition() - this->GetPosition()).Length()<=70.0f){
            this->SetState(ActorState::Destroy);
            asteroid->SetState(ActorState::Destroy);
        }
    }
}
