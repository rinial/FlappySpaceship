#include "CustomGameScene.h"
#include "GameOverScene.h"
#include "CustomSpaceship.h"
#include "CustomPillar.h"
#include "CustomPhysics/CustomPhysics.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CustomGameScene::createScene()
{
	return CustomGameScene::create();
}

// Initialize instance
bool CustomGameScene::init()
{
	// Super init first
	if (!GameScene::init())
		return false;

	// Set label for physics system 
	auto physicsLabel = Label::createWithTTF("Custom physics", MAIN_FONT, PHYSICS_LABEL_FONT_SIZE);
	physicsLabel->setPosition(
		ORIGIN.x + V_SIZE.width - physicsLabel->getContentSize().width / 2 - PHYSICS_LABEL_X_OFFSET,
		ORIGIN.y + physicsLabel->getContentSize().height / 2 + PHYSICS_LABEL_Y_OFFSET);
	physicsLabel->setColor(GAME_SCORE_COLOR);
	physicsLabel->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * PHYSICS_LABEL_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(physicsLabel, 1);

	// Set physical world
	sceneWorld_ = new CPWorld();
	sceneWorld_->addContactListener(this); // start listening to contacts

	// Set physical boundaries
	// Top boundary creation
	topEdgeBody_ = new CPRectangle(sceneWorld_, 
		Size(V_SIZE.width, BOUNDARY_WIDTH),
		Vec2(CENTER_X, ORIGIN.y + V_SIZE.height + BOUNDARY_WIDTH / 2.0));
	topEdgeBody_->selfMask = COLLISION_BITMASK_OBSTACLE;
	topEdgeBody_->hitMask = COLLISION_BITMASK_SPACESHIP; // collide with spaceship
	// Bottom boundary creation
	botEdgeBody_ = new CPRectangle(sceneWorld_,
		Size(V_SIZE.width, BOUNDARY_WIDTH),
		Vec2(CENTER_X, ORIGIN.y - BOUNDARY_WIDTH / 2.0));
	botEdgeBody_->selfMask = COLLISION_BITMASK_OBSTACLE;
	botEdgeBody_->hitMask = COLLISION_BITMASK_SPACESHIP; // collide with spaceship

	// Tell parent that everything is initialized
	onInitFinished();

	// Start updating physics
	this->schedule(schedule_selector(CustomGameScene::updatePhysics), PHYSICS_UPDATE_INTERVAL);

	return true;
}

// Clean memory upon destruction
CustomGameScene::~CustomGameScene()
{
	unscheduleAllCallbacks();
	delete sceneWorld_;
	sceneWorld_ = nullptr;
}

// Clean memory before leaving
void CustomGameScene::beforeLeavingScene()
{
	this->unscheduleAllCallbacks(); // important to avoid bugs before scenes actually change
	delete sceneWorld_;
	sceneWorld_ = nullptr;
}

// Go to game over screen
void CustomGameScene::continueToGameOver(float dT)
{
	beforeLeavingScene(); // Cleans some memory

	const auto scene = GameOverScene<CustomGameScene>::createScene(score_);
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}

// Called from physics when contact starts
void CustomGameScene::onBeginContact(CPContact& contact)
{
	const auto bitmaskA = contact.getBodyA()->selfMask;
	const auto bitmaskB = contact.getBodyB()->selfMask;

	if ((bitmaskA == COLLISION_BITMASK_SPACESHIP && bitmaskB == COLLISION_BITMASK_OBSTACLE) || 
		(bitmaskB == COLLISION_BITMASK_SPACESHIP && bitmaskA == COLLISION_BITMASK_OBSTACLE))
		onCollision();
}

// Update physics here
void CustomGameScene::updatePhysics(float dT)
{
	// Update physic body positions
	for (auto body : sceneWorld_->bodies)
	{
		if (!body->userData)
			continue;

		const auto node = static_cast<Sprite*>(body->userData);
		if (!node)
			continue;

		const auto parent = node->getParent();
		const auto pillar = dynamic_cast<Pillar*>(parent); // When physics object is child of pillar
		if (pillar) // We make sure that pillar's position is added
			body->setTransform(node->getPosition() + parent->getPosition(), node->getRotation() + parent->getRotation());
		else
			body->setTransform(node->getPosition(), node->getRotation());
	}

	// Evaluate physics
	sceneWorld_->step(dT);
}

// Create spaceship
Spaceship* CustomGameScene::createSpaceship()
{
	auto spaceship = CustomSpaceship::create();
	spaceship->initPhysics(sceneWorld_);
	this->addChild(spaceship, 1);
	return spaceship;
}

// Create new pillar
Pillar* CustomGameScene::createNewPillar()
{
	const auto pillar = CustomPillar::create();
	pillar->initPhysics(sceneWorld_);
	this->addChild(pillar);
	return pillar;
}
