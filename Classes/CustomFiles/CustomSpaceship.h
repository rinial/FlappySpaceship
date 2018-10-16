#ifndef __CUSTOM_SPACESHIP_H__
#define __CUSTOM_SPACESHIP_H__

#include "Spaceship.h"
#include "cocos2d.h"

// Forward declarations
class CPWorld;
class CPBody;

// Spaceship with box2d physics
class CustomSpaceship : public Spaceship
{
public:
	// Initialize instance
	virtual bool init() override;
	// Initialize physics
	void initPhysics(CPWorld* world);

	// static create()
	CREATE_FUNC(CustomSpaceship);

private:
	// Physics
	CPBody* physicsBody_ = nullptr;
};

#endif // __CUSTOM_SPACESHIP_H__
