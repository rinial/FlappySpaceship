#ifndef __COCOS_GAME_SCENE_H__
#define __COCOS_GAME_SCENE_H__

#include "GameScene.h"
#include "cocos2d.h"

// Game scene with cocos physics
class CocosGameScene : public GameScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    // static create()
    CREATE_FUNC(CocosGameScene);

private:
	// Go to game over screen
	virtual void continueToGameOver(float dT) override;

	// Physics
	cocos2d::PhysicsWorld* sceneWorld_ = nullptr;;
	// Called from physics when contact starts
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	// Create spaceship
	virtual Spaceship* createSpaceship() override;
	// Create new pillar
	virtual Pillar* createNewPillar() override;
};

#endif // __COCOS_GAME_SCENE_H__
