#include "Game.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Random.h"
#include "PlayerMove.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
Player::Player(Game* game)
	:Actor(game)
{
    asc = new AnimatedSprite(this, 200);
    Initialize();
    asc->SetAnimation("walkUp");
    asc->SetIsPaused(true);
    pm = new PlayerMove(this);
    cc = new CollisionComponent(this);
    cc->SetSize(20.0f, 20.0f);
    mDirection = PlayerDirection::Up;
}

void Player::Initialize(){
    std::vector<SDL_Texture*> walkUpAnim{
        GetGame()->GetTexture("Assets/Link/WalkUp0.png"),
        GetGame()->GetTexture("Assets/Link/WalkUp1.png")
    };
    
    std::vector<SDL_Texture*> walkDownAnim{
        GetGame()->GetTexture("Assets/Link/WalkDown0.png"),
        GetGame()->GetTexture("Assets/Link/WalkDown1.png")
    };
    
    std::vector<SDL_Texture*> walkLeftAnim{
        GetGame()->GetTexture("Assets/Link/WalkLeft0.png"),
        GetGame()->GetTexture("Assets/Link/WalkLeft1.png")
    };
    
    std::vector<SDL_Texture*> walkRightAnim{
        GetGame()->GetTexture("Assets/Link/WalkRight0.png"),
        GetGame()->GetTexture("Assets/Link/WalkRight1.png")
    };
    
    asc->AddAnimation("walkUp", walkUpAnim);
    asc->AddAnimation("walkDown", walkDownAnim);
    asc->AddAnimation("walkLeft", walkLeftAnim);
    asc->AddAnimation("walkRight", walkRightAnim);
 
}

void Player::OnUpdate(float deltaTime) {
    
}


/*PlayerMove* Player::GetMoveComponent() {
    return pm;
}*/
