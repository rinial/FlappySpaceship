LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/SplashScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/MenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Spaceship.cpp \
                   $(LOCAL_PATH)/../../../Classes/Pillar.cpp \
                   $(LOCAL_PATH)/../../../Classes/CocosFiles/CocosGameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/CocosFiles/CocosSpaceship.cpp \
                   $(LOCAL_PATH)/../../../Classes/CocosFiles/CocosPillar.cpp \
                   $(LOCAL_PATH)/../../../Classes/Box2DFiles/Box2DGameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Box2DFiles/Box2DSpaceship.cpp \
                   $(LOCAL_PATH)/../../../Classes/Box2DFiles/Box2DPillar.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomFiles/CustomGameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomFiles/CustomSpaceship.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomFiles/CustomPillar.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomPhysics/CPWorld.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomPhysics/CPContactEvaluator.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomPhysics/CPBody.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomPhysics/CPCircle.cpp \
                   $(LOCAL_PATH)/../../../Classes/CustomPhysics/CPRectangle.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
