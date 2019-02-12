#include "Asteroid.h"
#include "Game.h"
#include "Random.h"
#include "Math.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);
    this->SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    this->SetPosition(Random::GetVector(Vector2(0.0f, 0.0f), Vector2(1024.0f,768.0f)));
    GetGame()->AddAsteroid(this);
}

Asteroid::~Asteroid(){
    GetGame()->RemoveAsteroid(this);
}

void Asteroid::OnUpdate(float deltaTime){
    // (Screen wrapping code only for asteroids)
    Vector2 position = this->GetPosition();
    if (position.x < 0.0f){
        position.x = 1022.0f;
    } else if (position.x > 1024.0f){
        position.x = 2.0f;
    }
    
    if (position.y < 0.0f){
        position.y = 766.0f;
    } else if (position.y > 768.0f){
        position.y = 2.0f;
    }
    this->SetPosition(position);
}
