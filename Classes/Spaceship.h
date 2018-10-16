#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include "cocos2d.h"

// Base class for spaceships
class Spaceship : public cocos2d::Sprite
{
public:
	// Initialize instance (sprite)
	virtual bool init() override;

	// Spaceship's "jump"
	void boost();

	// Plays basic animation
	void onCrash();

private:
	// Movement affected by gravity
	void fall(float dT);

	// Speed of the spaceship
	float currentSpeed_ = 0;
	// Spaceship isn't controllable after a crash
	bool isControllable_ = true;
};

#endif // __SPACESHIP_H__
