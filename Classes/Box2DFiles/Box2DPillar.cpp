#include "Box2DPillar.h"
#include "Box2D/Box2D.h"
#include "Definitions.h"

USING_NS_CC;

// Initialize instance
bool Box2DPillar::init()
{
	// Super init first
	return Pillar::init();
}
// Initialize physics
void Box2DPillar::initPhysics(b2World* world)
{
	// Basic body creation
	b2BodyDef topBodyDef;
	topBodyDef.type = b2_kinematicBody;
	topBodyDef.position.Set(TO_M(this->getPositionX() + topPillar_->getPositionX()), TO_M(this->getPositionY() + topPillar_->getPositionY()));
	topBodyDef.fixedRotation = true;
	topBodyDef.userData = topPillar_;
	topBody_ = world->CreateBody(&topBodyDef);

	topBodyDef.userData = botPillar_;
	botBody_ = world->CreateBody(&topBodyDef); // We use (almost) the same difinition since at init step pillars are identical

	// Polygonal shape
	b2PolygonShape shape;
	shape.SetAsBox(TO_M(topPillar_->getContentSize().width / 2), TO_M(topPillar_->getContentSize().height / 2));

	// Polygonal fixture
	b2FixtureDef topFixtureDef;
	topFixtureDef.shape = &shape;
	topFixtureDef.density = 1;
	topFixtureDef.filter.categoryBits = COLLISION_BITMASK_OBSTACLE;
	topFixtureDef.filter.maskBits = COLLISION_BITMASK_SPACESHIP; // collide with spaceships
	topBody_->CreateFixture(&topFixtureDef);

	botBody_->CreateFixture(&topFixtureDef); // We use the same difinition since at init step pillars are identical
}
