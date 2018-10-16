#include "Spaceship.h"
#include "Definitions.h"

#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

// Initialize instance (sprite)
bool Spaceship::init()
{
	// Super init first
	if (!Sprite::initWithFile("Spaceship.png"))
		return false;

	this->setPosition(ORIGIN.x + V_SIZE.width * SPACESHIP_X_POS, CENTER_Y);

	// Start applying gravity
	// We delay it by the scene transition time to avoid teleports at the start of the game
	this->schedule(schedule_selector(Spaceship::fall), PHYSICS_UPDATE_INTERVAL, CC_REPEAT_FOREVER, SCENE_TRANSITION_TIME);
	
	return true;
}

// Spaceship's "jump"
void Spaceship::boost()
{
	if (!isControllable_)
		return;

	SimpleAudioEngine::getInstance()->playEffect(BOOST_SOUND_EFFECT);
	currentSpeed_ = BOOSTER_SPEED;
}

// Plays basic animation
void Spaceship::onCrash()
{
	if (!isControllable_) return;
	isControllable_ = false;

	SimpleAudioEngine::getInstance()->playEffect(CRASH_SOUND_EFFECT);
	// Moves left and rotates
	this->runAction(RepeatForever::create(MoveBy::create(1, Vec2(-(PILLAR_SPEED * V_SIZE.width) * CRASH_SPEED_K, 0))));
	this->runAction(RepeatForever::create(RotateBy::create(1, -CRASH_ROTATION_SPEED)));
}

// Movement affected by gravity
void Spaceship::fall(float dT)
{
	this->setPositionY(this->getPositionY() + currentSpeed_ * dT);
	currentSpeed_ -= GRAVITY_FORCE * dT;

	if (isControllable_)
		this->setRotation(currentSpeed_ * SPEED_TO_ANGLE);
}
