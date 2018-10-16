#ifndef __BOX2D_PILLAR_H__
#define __BOX2D_PILLAR_H__

#include "Pillar.h"
#include "cocos2d.h"

// Pillar with box2d physics
class Box2DPillar : public Pillar
{
public:
	// Initialize instance
	virtual bool init() override;
	// Initialize physics
	void initPhysics(class b2World* world);

	// static create()
	CREATE_FUNC(Box2DPillar);

private:
	// Physics
	class b2Body* topBody_ = nullptr;
	class b2Body* botBody_ = nullptr;
};

#endif // __BOX2D_PILLAR_H__
