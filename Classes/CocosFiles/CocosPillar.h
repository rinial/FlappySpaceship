#ifndef __COCOS_PILLAR_H__
#define __COCOS_PILLAR_H__

#include "Pillar.h"
#include "cocos2d.h"

// Pillar with cocos physics
class CocosPillar : public Pillar
{
public:
	// Initialize instance (physics)
	virtual bool init() override;

	// static create()
	CREATE_FUNC(CocosPillar);
};

#endif // __COCOS_PILLAR_H__
