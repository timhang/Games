#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	// TODO
    mGame->AddActor(this);
}

Actor::~Actor()
{
	// TODO
    mGame->RemoveActor(this);
    /*while (!mComponents.empty())
    {
        delete mComponents.back();
    }*/
    std::vector<Component*> tempComponents = mComponents;
    for(auto temp: tempComponents){
        delete temp;
    }
    tempComponents.clear();
     
}

void Actor::Update(float deltaTime)
{
	// TODO
    if (mState == ActorState::Active) {
        for (auto comp : mComponents) {
            comp->Update(deltaTime);
        }
        OnUpdate(deltaTime);
    }
}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// TODO

    if (this->mState == ActorState::Active) {
        for (auto comp : mComponents) {
            comp->ProcessInput(keyState);
        }
        if (keyState!=nullptr)
            OnProcessInput(keyState);
    }
}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}

Vector2 Actor::GetForward(){
     return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation));
}
