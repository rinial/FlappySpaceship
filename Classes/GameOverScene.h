#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

// Player's score
static unsigned int gainedScore = 0;
// Player's highest score
static unsigned int highestScore = 0;

// Game over screen
// T is the type of previous scene, a.g. CocosGameScene, Box2DGameScene, CustomGameScene
// This is needed for 'retry' functionality
template<typename T> 
class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(float score);

    virtual bool init() override;
    
    // static create()
    CREATE_FUNC(GameOverScene<T>);

private:
	// Retry the game
	void menuRetryCallback(cocos2d::Ref* sender);

	// Returns to menu
	void menuMenuCallback(cocos2d::Ref* sender);

	// Exits the game
	void menuExitCallback(cocos2d::Ref* sender);

	// Score that is currently shown on the screen
	unsigned int shownScore_ = 0;
	// This is where score is shown
	cocos2d::Label* scoreLabel_ = nullptr;

	// Highest score that is currently shown on the screen
	unsigned int shownHScore_ = 0;
	// This is where highest score is shown
	cocos2d::Label* hScoreLabel_ = nullptr;

	// Updates shown score by one and schedules itself
	void incrementShownScore(float dT);
};

///////////////////////////////
// Declarations

#include "MenuScene.h"
#include "Definitions.h"

#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

template<typename T>
Scene* GameOverScene<T>::createScene(const float score)
{
	gainedScore = score;
	return GameOverScene<T>::create();
}

// Initialize instance
template<typename T>
bool GameOverScene<T>::init()
{
	// Super init first
	if (!Scene::init())
		return false;

	// Background music
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MENU_BACKGROUND_MUSIC);

	// Background image
	auto backSprite = Sprite::create("Background.png");
	backSprite->setPosition(CENTER);
	this->addChild(backSprite);

	const auto titleTopOffset = V_SIZE.height / 5;

	// Title image on the top
	auto titleSprite = Sprite::create("TitleWithSpaceship.png");
	titleSprite->setPosition(CENTER_X, 
		ORIGIN.y + V_SIZE.height - titleTopOffset - titleSprite->getContentSize().height / 2);
	this->addChild(titleSprite);

	const auto titleToScore = V_SIZE.height / 12;

	// Set label for 'score'
	auto scoreTextLabel = Label::createWithTTF("SCORE", MAIN_FONT, GAME_OVER_SCORE_TEXT_FONT_SIZE);
	scoreTextLabel->setPosition(
		ORIGIN.x + V_SIZE.width / 3 * 1, 
		ORIGIN.y + V_SIZE.height - titleTopOffset - titleSprite->getContentSize().height - titleToScore - scoreTextLabel->getContentSize().height / 2);
	scoreTextLabel->setColor(GAME_SCORE_COLOR);
	scoreTextLabel->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * GAME_OVER_SCORE_TEXT_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(scoreTextLabel);

	// Set label for 'highest'
	auto hScoreTextLabel = Label::createWithTTF("HIGHEST", MAIN_FONT, GAME_OVER_SCORE_TEXT_FONT_SIZE);
	hScoreTextLabel->setPosition(
		ORIGIN.x + V_SIZE.width / 3 * 2, 
		ORIGIN.y + V_SIZE.height - titleTopOffset - titleSprite->getContentSize().height - titleToScore - hScoreTextLabel->getContentSize().height / 2);
	hScoreTextLabel->setColor(GAME_SCORE_COLOR);
	hScoreTextLabel->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * GAME_OVER_SCORE_TEXT_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(hScoreTextLabel);

	const auto betweenScores = V_SIZE.height / 40;

	// Set label for actual score 
	scoreLabel_ = Label::createWithTTF("0", MAIN_FONT, GAME_OVER_SCORE_FONT_SIZE);
	scoreLabel_->setPosition(
		ORIGIN.x + V_SIZE.width / 3 * 1,
		ORIGIN.y + V_SIZE.height - titleTopOffset - titleSprite->getContentSize().height - titleToScore - scoreTextLabel->getContentSize().height - betweenScores - scoreLabel_->getContentSize().height / 2);
	scoreLabel_->setColor(GAME_SCORE_COLOR);
	scoreLabel_->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * GAME_OVER_SCORE_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(scoreLabel_);

	// Set label for highest score 
	UserDefault* def = UserDefault::getInstance();
	highestScore = def->getIntegerForKey(HIGH_SCORE_TAG, 0);
	shownHScore_ = highestScore; // We show previous highest score right away
	if (gainedScore > highestScore) {
		highestScore = gainedScore;
		def->setIntegerForKey(HIGH_SCORE_TAG, highestScore);
	}
	def->flush();
	hScoreLabel_ = Label::createWithTTF(__String::createWithFormat("%d", shownHScore_)->getCString(), MAIN_FONT, GAME_OVER_SCORE_FONT_SIZE);
	hScoreLabel_->setPosition(
		ORIGIN.x + V_SIZE.width / 3 * 2,
		ORIGIN.y + V_SIZE.height - titleTopOffset - titleSprite->getContentSize().height - titleToScore - scoreTextLabel->getContentSize().height - betweenScores - hScoreLabel_->getContentSize().height / 2);
	hScoreLabel_->setColor(GAME_SCORE_COLOR);
	hScoreLabel_->enableShadow(Color4B(GAME_SCORE_SHADOW_COLOR), Size(1, -1) * GAME_OVER_SCORE_FONT_SIZE * GAME_SCORE_SHADOW_SIZE);
	this->addChild(hScoreLabel_);

	// Schedule incrementing shown score
	if(gainedScore > 0)
		this->scheduleOnce(schedule_selector(GameOverScene::incrementShownScore), GAME_OVER_SCORE_MIN_DELAY + SCENE_TRANSITION_TIME);

	const auto scoreToMenu = V_SIZE.height / 15;

	// Menu
	std::vector<MenuItem*> menuItems; // We will use this vector to set positions for all items later. This way adding new items is easier
	menuItems.push_back(MenuItemImage::create("RetryButtonNormal.png", "RetryButtonPressed.png", CC_CALLBACK_1(GameOverScene<T>::menuRetryCallback, this))); // retry button
	menuItems.push_back(MenuItemImage::create("MenuButtonNormal.png", "MenuButtonPressed.png", CC_CALLBACK_1(GameOverScene<T>::menuMenuCallback, this))); // menu button
	menuItems.push_back(MenuItemImage::create("ExitButtonNormal.png", "ExitButtonPressed.png", CC_CALLBACK_1(GameOverScene<T>::menuExitCallback, this))); // exit button
	const auto itemsBottomOffset = V_SIZE.height / 5;
	auto spaceForItems = V_SIZE.height - titleTopOffset - titleSprite->getContentSize().height - titleToScore - scoreTextLabel->getContentSize().height - betweenScores - scoreLabel_->getContentSize().height - scoreToMenu - itemsBottomOffset;
	spaceForItems += (spaceForItems - menuItems.size() * menuItems[0]->getContentSize().height) / (menuItems.size() - 1);
	for (unsigned int i = 0; i < menuItems.size(); ++i) {
		const auto item = menuItems[i];
		item->setPosition(CENTER_X, ORIGIN.y + itemsBottomOffset + spaceForItems - spaceForItems / menuItems.size() * (i + 1) + item->getContentSize().height / 2);
	}
	auto menu = Menu::create(menuItems[0], menuItems[1], menuItems[2], nullptr); // Make sure to add/remove items here if you add/remove them elsewhere
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

// Retry the game
template<typename T>
void GameOverScene<T>::menuRetryCallback(cocos2d::Ref* sender)
{
	CCLOG("restart");

	SimpleAudioEngine::getInstance()->playEffect(CLICK_SOUND_EFFECT);
	const auto scene = T::createScene();
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}

// Returns to menu
template<typename T>
void GameOverScene<T>::menuMenuCallback(cocos2d::Ref* sender)
{
	CCLOG("back to menu");

	SimpleAudioEngine::getInstance()->playEffect(CLICK_SOUND_EFFECT);
	const auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}

// Exits the game
template<typename T>
void GameOverScene<T>::menuExitCallback(cocos2d::Ref* sender)
{
	CCLOG("exit");

	SimpleAudioEngine::getInstance()->playEffect(CLICK_SOUND_EFFECT);
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

// Updates shown score by one and schedules itself
template <typename T>
void GameOverScene<T>::incrementShownScore(float dT)
{	
	++shownScore_;
	scoreLabel_->setString(__String::createWithFormat("%d", shownScore_)->getCString());
	SimpleAudioEngine::getInstance()->playEffect(SCORE_SOUND_EFFECT);
	if(shownScore_ > shownHScore_) {
		++shownHScore_;
		// Increases shown highest score along with current score if it's higher than highest
		hScoreLabel_->setString(__String::createWithFormat("%d", shownHScore_)->getCString());
	}
	if (shownScore_ < gainedScore) 
		// Updates shown score slower as it reaches actual score
		this->scheduleOnce(schedule_selector(GameOverScene::incrementShownScore), std::pow(GAME_OVER_SCORE_MIN_DELAY + shownScore_ / gainedScore * (GAME_OVER_SCORE_MAX_DELAY - GAME_OVER_SCORE_MIN_DELAY), 1.3));
}

#endif // __GAME_OVER_SCENE_H__
