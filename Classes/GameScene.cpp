#include "GameScene.h"
#include "GameOverScene.h"
#include "Spaceship.h"
#include "Pillar.h"
#include "Definitions.h"
#include <ctime>

#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

constexpr int maxNumPillars = 1.0 / (PILLAR_SPEED * PILLAR_SPAWN_INTERVAL) + 1;

// Initialize instance
bool GameScene::init()
{
	// Super init first
	if (!Scene::init())
		return false;

	// Background music
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC);

	// Background image
	auto backSprite = Sprite::create("Background.png");
	backSprite->setPosition(CENTER);
	this->addChild(backSprite);

	// Set label for score 
	scoreLabel_ = Label::createWithTTF("Score: 0", MAIN_FONT, GAME_SCORE_FONT_SIZE);
	scoreLabel_->setPosition(
		CENTER_X,
		ORIGIN.y + V_SIZE.height - scoreLabel_->getContentSize().height / 2 - GAME_SCORE_Y_OFFSET);
	scoreLabel_->setWidth(V_SIZE.width - 2 * GAME_SCORE_X_OFFSET);
	scoreLabel_->setAlignment(TextHAlignment::RIGHT);
	scoreLabel_->setColor(GAME_SCORE_COLOR);
	scoreLabel_->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * GAME_SCORE_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(scoreLabel_, 1);

	// Start listening to touches
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	// Seed randomness
	std::srand(std::time(0));

	return true;
}

// Called from children when initialization is complete
void GameScene::onInitFinished()
{
	// We don't do this earlier to be sure that physics systems are ready

	// Add all possible pillars to pillars pool to avoid FPS drops on creating new pillars
	pillarsPool_.reserve(maxNumPillars);
	for (int i = 0; i < maxNumPillars; ++i) {
		pillarsPool_.pushBack(createNewPillar());
	}

	// Schedule pillar spawns
	this->schedule(schedule_selector(GameScene::spawnPillar), PILLAR_SPAWN_INTERVAL);
	// Schedule score increments
	this->schedule(schedule_selector(GameScene::incrementScore), PILLAR_SPAWN_INTERVAL, CC_REPEAT_FOREVER, PILLAR_SPAWN_INTERVAL + (1.0 - SPACESHIP_X_POS) / PILLAR_SPEED);

	// Finally create a spaceship
	spaceship_ = createSpaceship();
}

// Called from children when collision was detected
void GameScene::onCollision()
{
	if (!isAlive_) return;
	isAlive_ = false;

	spaceship_->onCrash(); // Plays basic crash animation

	this->scheduleOnce(schedule_selector(GameScene::continueToGameOver), CRASH_SCENE_TRANSITION_DELAY);
}

// Make the spaceship fly upon touch
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	if (isAlive_)
		spaceship_->boost();
	return true;
}

// Spawn pillar
void GameScene::spawnPillar(float dT)
{
	pillarsPool_.at(poolableIndex_)->spawn();

	++poolableIndex_;
	if (poolableIndex_ >= maxNumPillars) 
		poolableIndex_ = 0;
}

// Increaments score when pillars pass the player
void GameScene::incrementScore(float dT)
{
	if(!isAlive_)
		return;

	SimpleAudioEngine::getInstance()->playEffect(POINT_SOUND_EFFECT);
	++score_;
	scoreLabel_->setString(__String::createWithFormat("Score: %d", score_)->getCString());
}
