#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

// Visible origin, size (of screen) and center
#define ORIGIN Director::getInstance()->getVisibleOrigin()
#define V_SIZE Director::getInstance()->getVisibleSize()
#define CENTER_X (ORIGIN.x + V_SIZE.width / 2.0)   // sometimes we only 
#define CENTER_Y (ORIGIN.y + V_SIZE.height / 2.0) // need one axis
#define CENTER Vec2(CENTER_X, CENTER_Y) 

// For UI
#define MAIN_FONT "fonts/y2k.ttf"
#define GREEN_COLOR Color3B(161, 209, 117)
#define GAME_SCORE_COLOR Color3B::WHITE
#define GAME_SCORE_SHADOW_COLOR GREEN_COLOR
#define GAME_SCORE_SHADOW_SIZE 0.04 // depends on size
#define GAME_SCORE_FONT_SIZE (0.04 * V_SIZE.height)
#define GAME_SCORE_X_OFFSET (0.07 * V_SIZE.width) // from right
#define GAME_SCORE_Y_OFFSET GAME_SCORE_X_OFFSET // from top
#define GAME_OVER_SCORE_TEXT_FONT_SIZE (0.035 * V_SIZE.height)
#define GAME_OVER_SCORE_FONT_SIZE (0.08 * V_SIZE.height)
#define GAME_OVER_SCORE_MIN_DELAY 0.17
#define GAME_OVER_SCORE_MAX_DELAY 0.55
#define PHYSICS_LABEL_FONT_SIZE (0.03 * V_SIZE.height)
#define PHYSICS_LABEL_X_OFFSET GAME_SCORE_X_OFFSET // from right
#define PHYSICS_LABEL_Y_OFFSET GAME_SCORE_X_OFFSET // from bottom

// For memory
#define HIGH_SCORE_TAG "HighestScore"

// For sounds
#define CRASH_SOUND_EFFECT "audio/crash.wav"
#define SCORE_SOUND_EFFECT "audio/score.wav"
#define BOOST_SOUND_EFFECT "audio/boost.wav"
#define CLICK_SOUND_EFFECT "audio/click.wav"
#define POINT_SOUND_EFFECT "audio/point.wav"
#define BACKGROUND_MUSIC "audio/background.mp3"
#define MENU_BACKGROUND_MUSIC "audio/menuBackground.wav"

// For scene transitions
#define SCENE_TRANSITION_TIME 0.5
#define SCENE_TRANSITION_TYPE TransitionCrossFade
#define SCENE_TRANSITION(scene) SCENE_TRANSITION_TYPE::create(SCENE_TRANSITION_TIME, scene)
#define CRASH_SCENE_TRANSITION_DELAY 1.5 // delay after crashing and before going to game over screen

// For pillars
#define PILLAR_SPAWN_INTERVAL 2.2
#define MAX_PILLAR_POS 0.9 // based on screen size
#define MIN_PILLAR_POS 0.1
#define MAX_PILLAR_GAP 0.35
#define MIN_PILLAR_GAP 0.2
#define PILLAR_SPEED   0.2
#define PILLAR_X_SCALE 0.9 // changes pillars' width

// For spaceship
#define SPACESHIP_X_POS 0.3 // based on screen size
#define GRAVITY_FORCE (0.5 * V_SIZE.height) // acceleration down
#define BOOSTER_SPEED (0.3 * V_SIZE.height) // initial "jump" speed
#define CRASH_ROTATION_SPEED 100.0
#define CRASH_SPEED_K 1.4 // moves back faster than pillars
#define SPEED_TO_ANGLE (-100.0 / V_SIZE.height)

// For physics
// General
#define PHYSICS_UPDATE_INTERVAL (1.0 / 60)
#define COLLISION_BITMASK_ALL       0xFFFF
#define COLLISION_BITMASK_SPACESHIP 0x0001
#define COLLISION_BITMASK_OBSTACLE  0x0002
// Box 2D specific
#define PTM_RATIO (V_SIZE.height / 10.0) // pixels to meters. It is important since Box2D works best with objects between 0.1 and 10 meters size
#define TO_M(num) ((num) / PTM_RATIO) // transforms pixels into meters
#define TO_MV(x, y) b2Vec2(TO_M(x), TO_M(y)) // transforms pixels into metric vector
#define V_TO_MV(vector) b2Vec2(TO_M((vector).x), TO_M((vector).y)) // transforms pixel vector into metric vector
#define VELOCITY_ITERATIONS 2 // for physics 'step'
#define POSITION_ITERATIONS 5 // -||-
// Custom specific
#define BOUNDARY_WIDTH 10 // for top and bottom screen boundary (created as two rectangles)

#endif // __DEFINITIONS_H__
