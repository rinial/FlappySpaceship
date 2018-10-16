#ifndef __COCOS_SPACESHIP_H__
#define __COCOS_SPACESHIP_H__

#include "Spaceship.h"
#include "cocos2d.h"

// Spaceship with cocos physics
class CocosSpaceship : public Spaceship
{
public:
	// Initialize instance (physics)
	virtual bool init() override;

	// static create()
	CREATE_FUNC(CocosSpaceship);
};

#endif // __COCOS_SPACESHIP_H__
