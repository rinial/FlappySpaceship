#ifndef __CP_BODY_H__
#define __CP_BODY_H__

#include "cocos2d.h" // Just for basic things like Vec2

// Forward declarations
class CPWorld;

// Basic custom physics body with all required information
class CPBody
{
public:
	// Updates position/rotation and informs world about it
	void setPosition(cocos2d::Vec2 pos);
	virtual void setRotation(float rot);
	// Useful to avoid informing world twice
	void setTransform(cocos2d::Vec2 pos, float rot);

	// Returns position/rotation
	cocos2d::Vec2 getPosition() const { return position_; }
	float getRotation() const { return rotation_; }

	void* userData = nullptr;
	uint16_t selfMask = 0; // what it is
	uint16_t hitMask = 0; // what it can contact with

	// Important for cleaning memory using base class pointer
	virtual ~CPBody() = default; 

protected:
	// Constructor is not public so that noone creates CPBody
	explicit CPBody(CPWorld* world, cocos2d::Vec2 pos = cocos2d::Vec2::ZERO, float rot = 0);

	// Used to inform world when this body has moved (and thus should be evaluated for contacts)
	CPWorld* world_ = nullptr; 

private:
	cocos2d::Vec2 position_;
	float rotation_ = 0;
};

#endif // __CP_BODY_H__
