#include "MenuScene.h"
#include "CocosFiles/CocosGameScene.h"
#include "Box2DFiles/Box2DGameScene.h"
#include "CustomFiles/CustomGameScene.h"
#include "Definitions.h"

#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

// Initialize instance
bool MenuScene::init()
{
	// Super init first
	if (!Scene::init())
		return false;

	// Background image
	auto backSprite = Sprite::create("Background.png");
	backSprite->setPosition(CENTER);
	this->addChild(backSprite);

	// Title image on the top
	auto titleSprite = Sprite::create("Title.png");
	const auto titleTopOffset = V_SIZE.height / 5;
	titleSprite->setPosition(CENTER_X, ORIGIN.y + V_SIZE.height - titleTopOffset - titleSprite->getContentSize().height / 2);
	this->addChild(titleSprite);

	// Menu
	std::vector<MenuItem*> menuItems; // We will use this vector to set positions for all items later. This way adding new items is easier
	menuItems.push_back(MenuItemImage::create("PlayCocosButtonNormal.png", "PlayCocosButtonPressed.png", CC_CALLBACK_1(MenuScene::menuPlayCocosCallback, this))); // play button for mode with cocos physics
	menuItems.push_back(MenuItemImage::create("PlayBox2DButtonNormal.png", "PlayBox2DButtonPressed.png", CC_CALLBACK_1(MenuScene::menuPlayBox2DCallback, this))); // -||- box2d physics
	menuItems.push_back(MenuItemImage::create("PlayCustomButtonNormal.png", "PlayCustomButtonPressed.png", CC_CALLBACK_1(MenuScene::menuPlayCustomCallback, this))); // -||- custom physics
	menuItems.push_back(MenuItemImage::create("ExitButtonNormal.png", "ExitButtonPressed.png", CC_CALLBACK_1(MenuScene::menuExitCallback, this))); // exit button
	const auto itemsBottomOffset = V_SIZE.height / 5;
	const auto itemsTopOffset = V_SIZE.height / 10;
	const auto spaceForItems = V_SIZE.height - itemsBottomOffset - itemsTopOffset - titleTopOffset - titleSprite->getContentSize().height;
	for (unsigned int i = 0; i < menuItems.size(); ++i) {
		const auto item = menuItems[i];
		item->setPosition(CENTER_X, ORIGIN.y + itemsBottomOffset + spaceForItems - spaceForItems / menuItems.size() * (i + 1) + item->getContentSize().height / 2);
	}
	auto menu = Menu::create(menuItems[0], menuItems[1], menuItems[2], menuItems[3], nullptr); // Make sure to add/remove items here if you add/remove them elsewhere
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

// Start the game
// ...with cocos physics
void MenuScene::menuPlayCocosCallback(cocos2d::Ref* sender)
{
	CCLOG("play Cocos");

	SimpleAudioEngine::getInstance()->playEffect(CLICK_SOUND_EFFECT);
	const auto scene = CocosGameScene::createScene();
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}
// ...with Box 2D physics
void MenuScene::menuPlayBox2DCallback(cocos2d::Ref* sender)
{
	CCLOG("play Box 2D");

	SimpleAudioEngine::getInstance()->playEffect(CLICK_SOUND_EFFECT);
	const auto scene = Box2DGameScene::createScene();
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}
// ...with custom physics
void MenuScene::menuPlayCustomCallback(cocos2d::Ref* sender)
{
	CCLOG("play Custom");

	SimpleAudioEngine::getInstance()->playEffect(CLICK_SOUND_EFFECT);
	const auto scene = CustomGameScene::createScene();
	Director::getInstance()->replaceScene(SCENE_TRANSITION(scene));
}

// Exits the game
void MenuScene::menuExitCallback(cocos2d::Ref* sender)
{
	CCLOG("exit");

	SimpleAudioEngine::getInstance()->playEffect(CLICK_SOUND_EFFECT);
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
