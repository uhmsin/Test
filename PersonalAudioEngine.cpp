//
//  PersonalAudioEngine.cpp
//  FishingJoy
//
//  Created by Ringo_D on 12-9-27.
//
//

#include "PersonalAudioEngine.h"
#include "GameData.h"
#include "Define.h"
static PersonalAudioEngine* _sharedEngine = NULL;
using namespace CocosDenshion;
USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define ANDROID_CLASS_NAME1 "com/vemobi/fight/fight"
#define ANDROID_FUNCTION_NAME1 "addXueTong"
//#define ANDROID_FUNCTION_NAME "charge"
#define ANDROID_PARAM_TYPE "(Ljava/lang/String;Ljava/lang/String;)V"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
    //void  Java_mm_mf_org_ooo_musicIsOn(JNIEnv *env, jobject thiz,jint IsmusicOn)
    void  Java_com_vemobi_fight_fight_musicIsOn(JNIEnv *env, jobject thiz,jint IsmusicOn)
    {
        if (IsmusicOn == 0)
        {
            PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(-100);
            PersonalAudioEngine::sharedEngine()->setEffectsVolume(-20);
        }
        else if(IsmusicOn == 1)
        {
            PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(100);
            PersonalAudioEngine::sharedEngine()->setEffectsVolume(20);
        }
    }
}
#endif

void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
    KingData->setMusicVolume(volume);
}
void PersonalAudioEngine::setEffectsVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
    KingData->setSoundVolume(volume);
}
PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
    if(_sharedEngine==NULL)
    {
        _sharedEngine = new PersonalAudioEngine();
        _sharedEngine->init();
    }
    return _sharedEngine;
}
bool PersonalAudioEngine::init()
{
   
    this->preloadBackgroundMusic("music/jiemianbgmusic.mp3");
    this->preloadEffect("music/baoqi.mp3");
    this->preloadEffect("music/dajiqie1.mp3");
    this->preloadEffect("music/dajiqie2.mp3"/*.wav*/);
    this->preloadEffect("music/dajiqing.mp3"/*.wav*/);
    this->preloadEffect("music/dajiqie1.mp3");
    this->preloadEffect("music/dajiz.mp3"/*.wav*/);
    this->preloadEffect("music/dajizhong.mp3"/*.wav*/);
    this->preloadEffect("music/dazhao.mp3");
    this->preloadEffect("music/ko.mp3");
    this->preloadEffect("music/shanbi.mp3");
    this->preloadEffect("music/zhugongji1.mp3");
    this->preloadEffect("music/zhugongji2.mp3");
    this->preloadEffect("music/zhushouji.mp3");
    this->preloadEffect("music/prop.mp3"/*.wav*/);
    this->setBackgroundMusicVolume(100);
    this->setEffectsVolume(20.0);
   
    return true;
}
void PersonalAudioEngine::purge()
{

}
PersonalAudioEngine::PersonalAudioEngine()
{
    
}
PersonalAudioEngine::~PersonalAudioEngine()
{
    
}
