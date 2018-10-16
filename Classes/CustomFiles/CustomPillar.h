#ifndef __CUSTOM_PILLAR_H__
#define __CUSTOM_PILLAR_H__

#include "Pillar.h"
#include "cocos2d.h"

// Forward declarations
class CPWorld;
class CPBody;

// Pillar with box2d physics
class CustomPillar : public Pillar
{
public:
	// Initialize instance
	virtual bool init() override;
	// Initialize physics
	void initPhysics(CPWorld* world);

	// static create()
	CREATE_FUNC(CustomPillar);

private:
	// Physics
	CPBody* topBody_ = nullptr;
	CPBody* botBody_ = nullptr;
};

#endif // __CUSTOM_PILLAR_H__
