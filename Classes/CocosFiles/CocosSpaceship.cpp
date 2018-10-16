#include "CocosSpaceship.h"
#include "Definitions.h"

USING_NS_CC;

// Initialize instance (physics)
bool CocosSpaceship::init()
{
	// Super init first
	if (!Spaceship::init())
		return false;
	
	const auto spaceshipBody = PhysicsBody::createCircle(this->getContentSize().width / 2);
	spaceshipBody->setDynamic(false);
	spaceshipBody->setCollisionBitmask(COLLISION_BITMASK_SPACESHIP);
	spaceshipBody->setContactTestBitmask(COLLISION_BITMASK_ALL); // collides with all bodies
	this->setPhysicsBody(spaceshipBody);

	return true;
}
