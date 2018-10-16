#include "Box2DGameScene.h"
#include "GameOverScene.h"
#include "Box2DSpaceship.h"
#include "Box2DPillar.h"
#include "Box2D/Box2D.h"
#include "Definitions.h"

USING_NS_CC;

Scene* Box2DGameScene::createScene()
{
	return Box2DGameScene::create();
}

// Initialize instance
bool Box2DGameScene::init()
{
	// Super init first
	if (!GameScene::init())
		return false;

	// Set label for physics system 
	auto physicsLabel = Label::createWithTTF("Box 2D physics", MAIN_FONT, PHYSICS_LABEL_FONT_SIZE);
	physicsLabel->setPosition(
		ORIGIN.x + V_SIZE.width - physicsLabel->getContentSize().width / 2 - PHYSICS_LABEL_X_OFFSET,
		ORIGIN.y + physicsLabel->getContentSize().height / 2 + PHYSICS_LABEL_Y_OFFSET);
	physicsLabel->setColor(GAME_SCORE_COLOR);
	physicsLabel->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * PHYSICS_LABEL_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(physicsLabel, 1);

	// Set physical world
	sceneWorld_ = new b2World(b2Vec2_zero);
	sceneWorld_->SetAllowSleeping(true);
	sceneWorld_->SetContactListener(this); // start listening to contacts

	// Set physical boundaries
	// Body
	b2BodyDef edgeBodyDef;
	edgeBodyDef.type = b2_staticBody;
	edgeBodyDef.position.Set(0, 0);
	edgeBody_ = sceneWorld_->CreateBody(&edgeBodyDef);
	// Shape
	b2EdgeShape edgeShape;
	// Fixture
	b2FixtureDef edgeFixtureDef;
	edgeFixtureDef.shape = &edgeShape;
	edgeFixtureDef.density = 1;
	edgeFixtureDef.filter.categoryBits = COLLISION_BITMASK_OBSTACLE;
	edgeFixtureDef.filter.maskBits = COLLISION_BITMASK_SPACESHIP; // collide with spaceship
	// Two lines on top and on botoom of thescreen
	edgeShape.Set( // Bottom
		V_TO_MV(ORIGIN), 
		TO_MV(ORIGIN.x + V_SIZE.width, ORIGIN.y));
	edgeBody_->CreateFixture(&edgeFixtureDef);
	edgeShape.Set( // Top
		TO_MV(ORIGIN.x, ORIGIN.y + V_SIZE.height), 
		TO_MV(ORIGIN.x + V_SIZE.width, ORIGIN.y + V_SIZE.height));
	edgeBody_->CreateFixture(&edgeFixtureDef);

	// Tell parent that everything is initialized
	onInitFinished();

	// Start updating physics
	this->schedule(schedule_selector(Box2DGameScene::updatePhysics), PHYSICS_UPDATE_INTERVAL);

	return true;
}

// Clean memory upon destruction
Box2DGameScene::~Box2DGameScene()
{
	unscheduleAllCallbacks();
	delete sceneWorld_;
	sceneWorld_ = nullptr;
}

// Clean memory before leaving
void Box2DGameScene::beforeLeavingScene()
{
	this->unscheduleAllCallbacks(); // important to avoid bugs before scenes actually change
	delete sceneWorld_;
	sceneWorld_ = nullptr;
}

// Go to game over screen
void Box2DGameScene::continueToGameOver(float dT)
{
	beforeLeavingScene(); // Cleans some memory

	const auto scene = GameOverScene<Box2DGameScene>::createScene(score_);
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}

// Called from physics when contact starts
void Box2DGameScene::BeginContact(b2Contact* contact)
{
	const auto bitmaskA = contact->GetFixtureA()->GetFilterData().categoryBits;
	const auto bitmaskB = contact->GetFixtureB()->GetFilterData().categoryBits;

	if ((bitmaskA == COLLISION_BITMASK_SPACESHIP && bitmaskB == COLLISION_BITMASK_OBSTACLE) || 
		(bitmaskB == COLLISION_BITMASK_SPACESHIP && bitmaskA == COLLISION_BITMASK_OBSTACLE))
		onCollision();
}

// Update physics here
void Box2DGameScene::updatePhysics(float dT)
{
	// Update physic body positions
	for (auto body = sceneWorld_->GetBodyList(); body; body = body->GetNext())
	{
		if (!body->GetUserData())
			continue;

		const auto node = static_cast<Sprite*>(body->GetUserData());
		if (!node)
			continue;
		
		const auto parent = node->getParent();
		const auto pillar = dynamic_cast<Pillar*>(parent); // When physics object is child of pillar
		if (pillar) // We make sure that pillar's position is added
			body->SetTransform(V_TO_MV((node->getPosition() + parent->getPosition())), CC_DEGREES_TO_RADIANS(node->getRotation() + parent->getRotation()));
		else
			body->SetTransform(V_TO_MV(node->getPosition()), CC_DEGREES_TO_RADIANS(node->getRotation()));
	}
	
	// Evaluate physics
	sceneWorld_->Step(dT, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

// Create spaceship
Spaceship* Box2DGameScene::createSpaceship()
{
	auto spaceship = Box2DSpaceship::create();
	spaceship->initPhysics(sceneWorld_);
	this->addChild(spaceship, 1);
	return spaceship;
}

// Create new pillar
Pillar* Box2DGameScene::createNewPillar()
{
	const auto pillar = Box2DPillar::create();
	pillar->initPhysics(sceneWorld_);
	this->addChild(pillar);
	return pillar;
}
