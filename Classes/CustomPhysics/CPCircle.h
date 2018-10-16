#ifndef __CP_CIRCLE_H__
#define __CP_CIRCLE_H__

#include "CPBody.h"

// Circle body
class CPCircle : public CPBody
{
public:
	CPCircle(class CPWorld* world, const float radius, const cocos2d::Vec2 pos = cocos2d::Vec2::ZERO) : CPBody(world, pos, 0) {
		assert(radius > 0); 
		radius_ = radius;
	}

	// Updates radius and informs world about it
	void setRadius(float radius);
	// Returns radius
	float getRadius() const { return radius_; }

	// We override setRotation so it doesn't do anything (and doesn't inform world)
	// But we still keep 'rotation' in CPBody rather than in CPRectangle for example since it's a generic component
	void setRotation(float rot) override { }

private:
	float radius_; // radius
};

#endif // __CP_CIRCLE_H__
