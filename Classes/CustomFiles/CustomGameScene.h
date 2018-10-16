#ifndef __CUSTOM_GAME_SCENE_H__
#define __CUSTOM_GAME_SCENE_H__

#include "GameScene.h"
#include "CustomPhysics/CPContactListener.h"
#include "cocos2d.h"

// Forward declarations
class CPWorld;
class CPBody;

// Game scene with box2d physics
class CustomGameScene : public GameScene, public CPContactListener
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	// static create()
	CREATE_FUNC(CustomGameScene);

	// Clean memory upon destruction
	~CustomGameScene();

private:
	// Clean memory before leaving
	virtual void beforeLeavingScene() override;
	// Go to game over screen
	virtual void continueToGameOver(float dT) override;

	// Physics
	CPWorld* sceneWorld_ = nullptr;
	CPBody* topEdgeBody_ = nullptr;
	CPBody* botEdgeBody_ = nullptr;
	// Called from physics when contact starts
	void onBeginContact(CPContact& contact) override;

	// Update physics here
	virtual void updatePhysics(float dT);

	// Create spaceship
	virtual Spaceship* createSpaceship() override;
	// Create new pillar
	virtual Pillar* createNewPillar() override;
};

#endif // __CUSTOM_GAME_SCENE_H__
