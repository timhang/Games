#include "Game.h"
#include "SpriteComponent.h"
#include "Block.h"
#include "Random.h"
#include "CollisionComponent.h"
Block::Block(Game* game)
	:Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    mTexture = "Assets/BlockA.png";
    sc->SetTexture(game->GetTexture(mTexture));
    cc = new CollisionComponent(this);
    cc->SetSize(64.0f, 32.0f);
    //this->SetPosition(Random::GetVector(Vector2(0.0f, 0.0f), Vector2(1024.0f,768.0f)));
    //GetGame()->AddAsteroid(this);
    GetGame()->AddBlock(this);
}
Block::~Block() {
    //this->SetState(ActorState::Destroy);
    GetGame()->RemoveBlock(this);
}

Block::Block(Game* game, std::string texture, int column, int row)
:Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    mTexture = "Assets/Block" + texture + ".png";
    sc->SetTexture(game->GetTexture(mTexture));
    
    this->SetPosition(Random::GetVector(Vector2(0.0f, 0.0f), Vector2(1024.0f,768.0f)));
    cc = new CollisionComponent(this);
    cc->SetSize(64.0f, 32.0f);
    this->SetPosition(Vector2((64.0f + column * 64), (48.0f + row * 32)));
    GetGame()->AddBlock(this);
}


void Block::ChangeTexture(std::string texture) {
    mTexture = texture;
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(GetGame()->GetTexture(mTexture));
}
