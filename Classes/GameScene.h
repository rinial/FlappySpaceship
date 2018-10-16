#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Pillar.h"
#include "cocos2d.h"

// Basic class for game scenes where game happens
class GameScene : public cocos2d::Scene
{
public:
    virtual bool init() override;

protected:
	// Clean memory before leaving
	virtual void beforeLeavingScene() {} // Implemented in some children cleaning memory

	// Create spaceship
	virtual class Spaceship* createSpaceship() = 0; // Implemented in children creating specific spaceships
	// Create new pillar
	virtual Pillar* createNewPillar() = 0; // Implemented in children creating specific pillars

	// Called from children when initialization is complete
	void onInitFinished();

	// Called from children when collision is detected
	void onCollision();

	// Player's score
	unsigned int score_ = 0;

private:
	// Go to game over screen
	virtual void continueToGameOver(float dT) = 0; // Implemented in children to allow specific retry

	// Make the spaceship fly upon touch
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	// Spawn pillar
	void spawnPillar(float dT);

	// Increaments score when pillars pass the player
	void incrementScore(float dT);
	// This is where score is shown
	cocos2d::Label* scoreLabel_ = nullptr;

	// True if player is still alive
	bool isAlive_ = true;

	// Pool of all pillars
	cocos2d::Vector<Pillar*> pillarsPool_;
	// Index of the next pillar that can be pooled (basically, respawned)
	// Used to imitate queue in cocos2d::Vector
	int poolableIndex_ = 0;

	// Spaceship
	class Spaceship* spaceship_ = nullptr;
};

#endif // __GAME_SCENE_H__
