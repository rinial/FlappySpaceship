#ifndef __BOX2D_GAME_SCENE_H__
#define __BOX2D_GAME_SCENE_H__

#include "GameScene.h"
#include "Box2D/Box2D.h"
#include "cocos2d.h"

// Game scene with box2d physics
class Box2DGameScene : public GameScene, public b2ContactListener
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    // static create()
    CREATE_FUNC(Box2DGameScene);

	// Clean memory upon destruction
	~Box2DGameScene();

private:
	// Clean memory before leaving
	virtual void beforeLeavingScene() override;
	// Go to game over screen
	virtual void continueToGameOver(float dT) override;

	// Physics
	class b2World* sceneWorld_ = nullptr;
	class b2Body* edgeBody_ = nullptr;
	// Called from physics when contact starts
	void BeginContact(b2Contact* contact) override;

	// Update physics here
	virtual void updatePhysics(float dT);

	// Create spaceship
	virtual Spaceship* createSpaceship() override;
	// Create new pillar
	virtual Pillar* createNewPillar() override;
};

#endif // __BOX2D_GAME_SCENE_H__
