#include "AnimatedSprite.h"
#include "Actor.h"
#include "Game.h"

AnimatedSprite::AnimatedSprite(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{
}

void AnimatedSprite::Update(float deltaTime)
{
	// TODO: Implement
    if(!mAnimName.empty()){
        if(!mIsPaused){
            mAnimTimer += mAnimFPS * deltaTime;
            while(mAnimTimer >= mAnims.at(mAnimName).size()){
                mAnimTimer -= mAnims.at(mAnimName).size();
            }
            
        }
        SetTexture(mAnims.at(mAnimName)[mAnimTimer]);
    }
}

void AnimatedSprite::SetAnimation(const std::string& name, bool resetTimer)
{
	if (mAnimName != name)
	{
		mAnimName = name;
	}
	
	if (resetTimer)
	{
		mAnimTimer = 0.0f;
	}
}

void AnimatedSprite::AddAnimation(const std::string& name,
								  const std::vector<SDL_Texture*>& images)
{
	mAnims.emplace(name, images);
}
