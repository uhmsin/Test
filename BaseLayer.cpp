//
//  BaseLayer.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "BaseLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#define ANDROID_CLASS_NAME "com/vemobi/fight/fight"
//"gedou/mofeng/cn/ooo"
#define ANDROID_FUNCTION_NAME "showDialogs"
//#define ANDROID_FUNCTION_NAME "charge"
#define ANDROID_PARAM_TYPE "(Ljava/lang/String;Ljava/lang/String;)V"

bool BaseLayer::init()
{

    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        setKeypadEnabled(true);
        isExit = false;
        bRet = true;
    } while (0);
    return bRet;
}

void BaseLayer::keyBackClicked()
{
	CCLOG("BaseLayer::keyBackClicked");
    int SceneTag = CCDirector::sharedDirector()->getRunningScene()->getTag();
	if (666 == SceneTag)
	{
		CCLOG("Exit Game");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		jobject jobj;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo, ANDROID_CLASS_NAME,
			ANDROID_FUNCTION_NAME,
			"(I)V");
		if (isHave)
		{
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, 823);
		}else{

		}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
}

void BaseLayer::keyMenuClicked()
{
    
}


