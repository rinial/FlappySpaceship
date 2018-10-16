#ifndef __BOX2D_SPACESHIP_H__
#define __BOX2D_SPACESHIP_H__

#include "Spaceship.h"
#include "cocos2d.h"

// Spaceship with box2d physics
class Box2DSpaceship : public Spaceship
{
public:
	// Initialize instance
	virtual bool init() override;
	// Initialize physics
	void initPhysics(class b2World* world);

	// static create()
	CREATE_FUNC(Box2DSpaceship);

private:
	// Physics
	class b2Body* physicsBody_ = nullptr;
};

#endif // __BOX2D_SPACESHIP_H__
