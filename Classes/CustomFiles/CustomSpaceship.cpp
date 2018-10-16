#include "CustomSpaceship.h"
#include "CustomPhysics/CustomPhysics.h"
#include "Definitions.h"

USING_NS_CC;

// Initialize instance
bool CustomSpaceship::init()
{
	// Super init first
	return Spaceship::init();
}
// Initialize physics
void CustomSpaceship::initPhysics(CPWorld* world)
{
	// Basic body creation
	physicsBody_ = new CPCircle(world, this->getContentSize().width / 2, this->getPosition());
	physicsBody_->selfMask = COLLISION_BITMASK_SPACESHIP;
	physicsBody_->hitMask = COLLISION_BITMASK_ALL; // collide with all bodies
	physicsBody_->userData = this;
}
