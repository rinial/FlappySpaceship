#include "Pillar.h"
#include "Definitions.h"

USING_NS_CC;

// Initialize instance (sprites)
bool Pillar::init()
{
	// Super init first
	if (!Node::init())
		return false;
	
	// Create 'subpillars' (sprites for top and bottom pillars)
	constexpr auto pillarPath = "Pillar.png";
	topPillar_ = Sprite::create(pillarPath);
	botPillar_ = Sprite::create(pillarPath);

	// Just move out of screen. We could change visibility instead, but it doesn't affect physics
	this->setPosition(-topPillar_->getContentSize().width / 2, 0); 
	this->setScaleX(PILLAR_X_SCALE);

	this->addChild(topPillar_);
	this->addChild(botPillar_);

	return true;
}

// Spawns pillar randomly
void Pillar::spawn()
{
	// Set random 'subpillars'
	const auto gapHeightK = MIN_PILLAR_GAP + rand_0_1() * (MAX_PILLAR_GAP - MIN_PILLAR_GAP);
	const auto gapHeight = V_SIZE.height * gapHeightK;
	const auto gapPosition = V_SIZE.height * (MIN_PILLAR_POS + gapHeightK / 2 + rand_0_1() * (MAX_PILLAR_POS - MIN_PILLAR_POS - gapHeightK));
	topPillar_->setPosition(0, gapPosition + topPillar_->getContentSize().height / 2 + gapHeight / 2);
	botPillar_->setPosition(0, gapPosition - botPillar_->getContentSize().height / 2 - gapHeight / 2);

	// Set pillar to the right
	this->setPosition(ORIGIN.x + V_SIZE.width + topPillar_->getContentSize().width / 2, 0);

	// Start moving the pillar
	const auto travelDistance = V_SIZE.width + topPillar_->getContentSize().width;
	const auto travelTime = 1.0 / PILLAR_SPEED;
	this->runAction(MoveBy::create(travelTime, Vec2(-travelDistance, 0)));
}
