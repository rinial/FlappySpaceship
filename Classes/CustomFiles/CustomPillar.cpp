#include "CustomPillar.h"
#include "CustomPhysics/CustomPhysics.h"
#include "Definitions.h"

USING_NS_CC;

// Initialize instance
bool CustomPillar::init()
{
	// Super init first
	return Pillar::init();
}
// Initialize physics
void CustomPillar::initPhysics(CPWorld* world)
{
	// Top body creation
	topBody_ = new CPRectangle(world, 
		topPillar_->getContentSize(),
		this->getPosition() + topPillar_->getPosition());
	topBody_->selfMask = COLLISION_BITMASK_OBSTACLE;
	topBody_->hitMask = COLLISION_BITMASK_SPACESHIP; // collide with spaceship
	topBody_->userData = topPillar_;

	// Bottom body creation
	botBody_ = new CPRectangle(world, 
		botPillar_->getContentSize(),
		this->getPosition() + botPillar_->getPosition());
	botBody_->selfMask = COLLISION_BITMASK_OBSTACLE;
	botBody_->hitMask = COLLISION_BITMASK_SPACESHIP; // collide with spaceship
	botBody_->userData = botPillar_;
}
