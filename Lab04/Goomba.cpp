#include "Game.h"
#include "SpriteComponent.h"
#include "Goomba.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "GoombaMove.h"
//#include "GoombaMove.h"
Goomba::Goomba(Game* game)
	:Actor(game)
{
    //sc = new SpriteComponent(this);
    //sc->SetTexture(game->GetTexture("Assets/Goomba/Walk0.png"));
    asc = new AnimatedSprite(this);
    std::vector<SDL_Texture*> walkAnim{
        GetGame()->GetTexture("Assets/Goomba/Walk0.png"),
        GetGame()->GetTexture("Assets/Goomba/Walk1.png")
    };
    std::vector<SDL_Texture*> deadAnim{
        GetGame()->GetTexture("Assets/Goomba/Dead.png")
    };
    // This assumes "asc" is the animated sprite component
    asc->AddAnimation("walk", walkAnim);
    asc->AddAnimation("dead", deadAnim);
    asc->SetAnimation("walk");
    cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);
    gm = new GoombaMove(this);
    //gm = new GoombaMove(this);
    mStomped = false;
    GetGame()->AddEnemy(this);
}

void Goomba::OnUpdate(float deltaTime){
    if(mStomped){
        mStompTime+=deltaTime;
        
        gm->SetForwardSpeed(0);
        if(mStompTime>=0.25f){
            this->SetState(ActorState::Destroy);
        }
    }
}

Goomba::~Goomba() {
    GetGame()->RemoveEnemy(this);
}

void Goomba::SetStomped(){
    mStomped = true;
    asc->SetAnimation("dead");
};
