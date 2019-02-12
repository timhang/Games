#include "Game.h"
#include "SpriteComponent.h"
#include "Ball.h"
#include "MoveComponent.h"
#include "Math.h"
#include "BallMove.h"
#include "CollisionComponent.h"
Ball::Ball(Game* game)
	:Actor(game)
{
    sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Ball.png"));
    bm = new BallMove(this);
    cc = new CollisionComponent(this);
    cc->SetSize(20.0f, 20.0f);
    //bm->SetForwardSpeed(250.0f);
    //this->SetRotation(float(M_PI/4));
}

CollisionComponent* Ball::GetCollisionComponent() {
    return cc;
}
