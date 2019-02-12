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
    superAsc = new AnimatedSprite(this,205);
    Initialize();
    InitializeSuper();
    asc->SetAnimation("idle");

    pm = new PlayerMove(this);
    cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);
}

void Player::Initialize(){
    std::vector<SDL_Texture*> idleAnim{
        GetGame()->GetTexture("Assets/Mario/Idle.png")
    };
    
    std::vector<SDL_Texture*> deadAnim{
        GetGame()->GetTexture("Assets/Mario/Dead.png")
    };
    
    std::vector<SDL_Texture*> jumpRightAnim{
        GetGame()->GetTexture("Assets/Mario/JumpRight.png")
    };
    
    std::vector<SDL_Texture*> jumpLeftAnim{
        GetGame()->GetTexture("Assets/Mario/JumpLeft.png")
    };
    
    std::vector<SDL_Texture*> runRightAnim{
        GetGame()->GetTexture("Assets/Mario/RunRight0.png"),
        GetGame()->GetTexture("Assets/Mario/RunRight1.png"),
        GetGame()->GetTexture("Assets/Mario/RunRight2.png")
    };
    
    std::vector<SDL_Texture*> runLeftAnim{
        GetGame()->GetTexture("Assets/Mario/RunLeft0.png"),
        GetGame()->GetTexture("Assets/Mario/RunLeft1.png"),
        GetGame()->GetTexture("Assets/Mario/RunLeft2.png")
    };
    
    asc->AddAnimation("idle", idleAnim);
    asc->AddAnimation("dead", deadAnim);
    asc->AddAnimation("jumpRight", jumpRightAnim);
    asc->AddAnimation("jumpLeft", jumpLeftAnim);
    asc->AddAnimation("runRight", runRightAnim);
    asc->AddAnimation("runLeft", runLeftAnim);
}

void Player::InitializeSuper(){
    std::vector<SDL_Texture*> idleAnim{
        GetGame()->GetTexture("Assets/SuperMario/Idle.png")
    };
    
    std::vector<SDL_Texture*> deadAnim{
        GetGame()->GetTexture("Assets/SuperMario/Dead.png")
    };
    
    std::vector<SDL_Texture*> jumpRightAnim{
        GetGame()->GetTexture("Assets/SuperMario/JumpRight.png")
    };
    
    std::vector<SDL_Texture*> jumpLeftAnim{
        GetGame()->GetTexture("Assets/SuperMario/JumpLeft.png")
    };
    
    std::vector<SDL_Texture*> runRightAnim{
        GetGame()->GetTexture("Assets/SuperMario/RunRight0.png"),
        GetGame()->GetTexture("Assets/SuperMario/RunRight1.png"),
        GetGame()->GetTexture("Assets/SuperMario/RunRight2.png")
    };
    
    std::vector<SDL_Texture*> runLeftAnim{
        GetGame()->GetTexture("Assets/SuperMario/RunLeft0.png"),
        GetGame()->GetTexture("Assets/SuperMario/RunLeft1.png"),
        GetGame()->GetTexture("Assets/SuperMario/RunLeft2.png")
    };
    
    superAsc->AddAnimation("idle", idleAnim);
    superAsc->AddAnimation("dead", deadAnim);
    superAsc->AddAnimation("jumpRight", jumpRightAnim);
    superAsc->AddAnimation("jumpLeft", jumpLeftAnim);
    superAsc->AddAnimation("runRight", runRightAnim);
    superAsc->AddAnimation("runLeft", runLeftAnim);
}

void Player::OnUpdate(float deltaTime) {
    if(this->GetPosition().x > 6368.0f){
        Mix_HaltChannel(GetGame()->GetChannel());
        Mix_Chunk *sample = GetGame()->GetSound("Assets/Sounds/StageClear.wav");
        if(Mix_PlayChannel(-1, sample, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        this->SetState(ActorState::Paused);
    }
}

void Player::ChangeState(){
    state = true;
    cc->SetSize(32.0f, 64.0f);
    asc->SetAnimation("idle");
    superAsc->SetAnimation("idle");

    Mix_Chunk *sample = GetGame()->GetSound("Assets/Sounds/PowerUp.wav");
    if(Mix_PlayChannel(-1, sample, 0)==-1) {
        printf("Mix_PlayChannel: %s\n",Mix_GetError());
    }
}

/*PlayerMove* Player::GetMoveComponent() {
    return pm;
}*/
