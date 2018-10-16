#ifndef __PILLAR_H__
#define __PILLAR_H__

#include "cocos2d.h"

// Base class for all pillars
class Pillar : public cocos2d::Node
{
public:
	// Initialize instance (sprites)
	virtual bool init() override;

	// Spawns pillar randomly
	void spawn();

protected:
	cocos2d::Sprite* topPillar_ = nullptr;
	cocos2d::Sprite* botPillar_ = nullptr;
};

#endif // __PILLAR_H__
