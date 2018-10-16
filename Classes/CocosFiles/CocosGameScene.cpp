#include "CocosGameScene.h"
#include "GameOverScene.h"
#include "CocosSpaceship.h"
#include "CocosPillar.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CocosGameScene::createScene()
{
	const auto scene = Scene::createWithPhysics();
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	const auto layer = CocosGameScene::create();
	layer->sceneWorld_ = scene->getPhysicsWorld();
	scene->addChild(layer);

	return scene;
}

// Initialize instance
bool CocosGameScene::init()
{
	// Super init first
	if (!GameScene::init())
		return false;

	// Set label for physics system 
	auto physicsLabel = Label::createWithTTF("Cocos physics", MAIN_FONT, PHYSICS_LABEL_FONT_SIZE);
	physicsLabel->setPosition(
		ORIGIN.x + V_SIZE.width - physicsLabel->getContentSize().width / 2 - PHYSICS_LABEL_X_OFFSET,
		ORIGIN.y + physicsLabel->getContentSize().height / 2 + PHYSICS_LABEL_Y_OFFSET);
	physicsLabel->setColor(GAME_SCORE_COLOR);
	physicsLabel->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * PHYSICS_LABEL_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(physicsLabel, 1);

	// Set physical boundaries
	const auto edgeBody = PhysicsBody::createEdgeBox(V_SIZE, PHYSICSBODY_MATERIAL_DEFAULT);
	edgeBody->setCollisionBitmask(COLLISION_BITMASK_OBSTACLE);
	edgeBody->setContactTestBitmask(COLLISION_BITMASK_SPACESHIP);
	auto edgeNode = Node::create();
	edgeNode->setPosition(CENTER);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	// Start listening to contacts (collisions)
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CocosGameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Tell parent that everything is initialized
	onInitFinished();

	return true;
}

// Go to game over screen
void CocosGameScene::continueToGameOver(float dT)
{
	beforeLeavingScene(); // Cleans some memory

	const auto scene = GameOverScene<CocosGameScene>::createScene(score_);
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}

// Called from physics when contact starts
bool CocosGameScene::onContactBegin(PhysicsContact& contact)
{
	const auto bitmaskA = contact.getShapeA()->getBody()->getCollisionBitmask();
	const auto bitmaskB = contact.getShapeB()->getBody()->getCollisionBitmask();

	if ((bitmaskA == COLLISION_BITMASK_SPACESHIP && bitmaskB == COLLISION_BITMASK_OBSTACLE) || 
		(bitmaskB == COLLISION_BITMASK_SPACESHIP && bitmaskA == COLLISION_BITMASK_OBSTACLE))
		onCollision();

	return true;
}

// Create spaceship
Spaceship* CocosGameScene::createSpaceship()
{
	const auto spaceship = CocosSpaceship::create();
	this->addChild(spaceship, 1);
	return spaceship;
}

// Create new pillar
Pillar* CocosGameScene::createNewPillar()
{
	const auto pillar = CocosPillar::create();
	this->addChild(pillar);
	return pillar;
}
