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
    mType = 'A';
    cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);
    //this->SetPosition(Random::GetVector(Vector2(0.0f, 0.0f), Vector2(1024.0f,768.0f)));
    GetGame()->AddBlock(this);
}
Block::~Block() {
    GetGame()->RemoveBlock(this);
}

Block::Block(Game* game, char texture, int column, int row)
:Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    mType = texture;
    std::string s;
    s.push_back(texture);
    mTexture = "Assets/Block" + s + ".png";
    sc->SetTexture(game->GetTexture(mTexture));
    
    cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);
    this->SetPosition(Vector2((16.0f + column * 32), (16.0f + row * 32)));
    GetGame()->AddBlock(this);
}


void Block::ChangeTexture(char texture) {
    std::string s;
    s.push_back(texture);
    mTexture = "Assets/Block" + s + ".png";
    mType = texture;
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(GetGame()->GetTexture(mTexture));
}
