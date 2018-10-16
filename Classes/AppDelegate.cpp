#include "AppDelegate.h"
#include "SplashScene.h"

#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(720, 1280);

AppDelegate::~AppDelegate()
{
	SimpleAudioEngine::end();
}

// If you want a different context, modify the value of glContextAttrs
// It will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// Set OpenGL context attributes: red, green, blue, alpha, depth, stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use the package manager to install more packages,  
// Don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// Initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Flappy");
		director->setOpenGLView(glview);
	}

	// Turn on display FPS
	director->setDisplayStats(true);

	// Set FPS. The default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

	// Set shorter search paths for sprites
	FileUtils::getInstance()->setSearchPaths({ "sprites" });

	register_all_packages();

	// Create a scene. It's an autorelease object
	const auto scene = SplashScene::createScene();

	// Run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive
// Note, when receiving a phone call it is invoked
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// This function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
}
