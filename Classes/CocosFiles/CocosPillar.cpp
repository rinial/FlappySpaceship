#include "CocosPillar.h"
#include "Definitions.h"

USING_NS_CC;

// Initialize instance (physics)
bool CocosPillar::init()
{
	// Super init first
	if (!Pillar::init())
		return false;

	auto topPillarBody = PhysicsBody::createBox(topPillar_->getContentSize());
	auto botPillarBody = PhysicsBody::createBox(botPillar_->getContentSize());

	topPillarBody->setDynamic(false);
	botPillarBody->setDynamic(false);

	topPillarBody->setCollisionBitmask(COLLISION_BITMASK_OBSTACLE);
	botPillarBody->setCollisionBitmask(COLLISION_BITMASK_OBSTACLE);
	topPillarBody->setContactTestBitmask(COLLISION_BITMASK_SPACESHIP);
	botPillarBody->setContactTestBitmask(COLLISION_BITMASK_SPACESHIP);

	topPillar_->setPhysicsBody(topPillarBody);
	botPillar_->setPhysicsBody(botPillarBody);

	return true;
}
