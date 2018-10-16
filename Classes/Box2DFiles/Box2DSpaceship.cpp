#include "Box2DSpaceship.h"
#include "Box2D/Box2D.h"
#include "Definitions.h"

USING_NS_CC;

// Initialize instance
bool Box2DSpaceship::init()
{
	// Super init first
	return Spaceship::init();
}
// Initialize physics
void Box2DSpaceship::initPhysics(b2World* world)
{
	// Basic body creation
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(TO_M(this->getPositionX()), TO_M(this->getPositionY()));
	bodyDef.fixedRotation = true;
	//bodyDef.bullet = true;
	bodyDef.userData = this;
	physicsBody_ = world->CreateBody(&bodyDef);

	// Circle shape
	b2CircleShape shape;
	shape.m_radius = TO_M(this->getContentSize().width / 2);

	// Circle fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1;
	fixtureDef.filter.categoryBits = COLLISION_BITMASK_SPACESHIP;
	fixtureDef.filter.maskBits = COLLISION_BITMASK_ALL; // collide with all bodies
	physicsBody_->CreateFixture(&fixtureDef);
}
