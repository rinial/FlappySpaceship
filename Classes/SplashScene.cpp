#include "SplashScene.h"
#include "MenuScene.h"
#include "Definitions.h"

#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* SplashScene::createScene()
{
	return SplashScene::create();
}

constexpr float splashScreenDuration = 0.8;

// Initialize instance
bool SplashScene::init()
{
	// Super init first
	if (!Scene::init())
		return false;

	// Preload sounds
	SimpleAudioEngine::getInstance()->preloadEffect(CRASH_SOUND_EFFECT);
	SimpleAudioEngine::getInstance()->preloadEffect(SCORE_SOUND_EFFECT);
	SimpleAudioEngine::getInstance()->preloadEffect(BOOST_SOUND_EFFECT);
	SimpleAudioEngine::getInstance()->preloadEffect(CLICK_SOUND_EFFECT);
	SimpleAudioEngine::getInstance()->preloadEffect(POINT_SOUND_EFFECT);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC);

	// Background music
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MENU_BACKGROUND_MUSIC);

	// Background image
	auto splashSprite = Sprite::create("SplashScreen.png");
	splashSprite->setPosition(ORIGIN.x + V_SIZE.width / 2, ORIGIN.y + V_SIZE.height / 2);
	this->addChild(splashSprite);
		
	// Go to main menu in a bit
	this->scheduleOnce(schedule_selector(SplashScene::continueToMenu), splashScreenDuration);

	return true;
}

// Go to main menu
void SplashScene::continueToMenu(float deltaTime)
{
	const auto scene1 = MenuScene::createScene();
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene1));
}
