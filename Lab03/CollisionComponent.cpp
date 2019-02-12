#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	// TODO: Implement
    bool case1 = this->GetMax().x < other->GetMin().x;
    bool case2 = other->GetMax().x < this->GetMin().x;
    bool case3 = this->GetMax().y < other->GetMin().y;
    bool case4 = other->GetMax().y < this->GetMin().y;
    bool intersecting = !(case1 || case2 || case3 || case4);
	return intersecting;
}

Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
    Vector2 min;
    min.x = mOwner->GetPosition().x - (mWidth *mOwner->GetScale()) / 2.0f;
    min.y = mOwner->GetPosition().y - (mHeight*mOwner->GetScale()) / 2.0f;
	return min;
}

Vector2 CollisionComponent::GetMax() const
{
	// TODO: Implement
    Vector2 max;
    max.x = mOwner->GetPosition().x + (mWidth *mOwner->GetScale()) / 2.0f;
    max.y = mOwner->GetPosition().y + (mHeight*mOwner->GetScale()) / 2.0f;
    return max;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector2& offset)
{
	offset = Vector2::Zero;
	// TODO: Implement
    if(!Intersect(other)){
        return CollSide::None;
    }
    
    float dx1, dx2, dy1, dy2;
    
    dx1 = this->GetMax().x - other->GetMin().x;
    dx2 = this->GetMin().x - other->GetMax().x;
    dy1 = this->GetMax().y - other->GetMin().y;
    dy2 = this->GetMin().y - other->GetMax().y;
    
    if(Math::Abs(dx1)<Math::Abs(dx2) && Math::Abs(dx1)<Math::Abs(dy1) && Math::Abs(dx1)<Math::Abs(dy2)){
        offset.x+=dx1;
        return CollSide::Left;
    } else if(Math::Abs(dx2)<Math::Abs(dx1) && Math::Abs(dx2)<Math::Abs(dy1) && Math::Abs(dx2)<Math::Abs(dy2)){
        offset.x+=dx2;
        return CollSide::Right;
    } else if(Math::Abs(dy1)<Math::Abs(dx1) && Math::Abs(dy1)<Math::Abs(dx2) && Math::Abs(dy1)<Math::Abs(dy2)){
        offset.y+=dy1;
        return CollSide::Top;
    } else {
        offset.y+=dy2;
        return CollSide::Bottom;
    }

}
