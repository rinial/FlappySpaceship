#include "CPBody.h"
#include "CPWorld.h"

USING_NS_CC;

// Updates position/rotation and informs world about it
void CPBody::setPosition(const Vec2 pos)
{
	position_ = pos;
	world_->onManipulatedBody(this);
}
void CPBody::setRotation(const float rot)
{
	rotation_ = rot;
	world_->onManipulatedBody(this);
}
// Useful to avoid informing world twice
void CPBody::setTransform(const Vec2 pos, const float rot)
{
	position_ = pos;
	rotation_ = rot; // This will change rotation for cirle, but the overload or setRotation in CPCircle is only added to prevent informing world, so it's fine
	world_->onManipulatedBody(this);
}

// Constructor
CPBody::CPBody(CPWorld* world, const Vec2 pos, const float rot) : position_(pos), rotation_(rot)
{
	assert(world);
	world_ = world;
	world_->onCreatedBody(this); // adds body to world
}
