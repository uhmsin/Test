//
//  ShopBuy2.cpp
//  king04
//
//  Created by mac on 14-5-12.
//
//

#include "ShopBuy2.h"
#include "Define.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define ANDROID_CLASS_NAME1 "com/vemobi/fight/fight"
//"gedou/mofeng/cn/ooo"
#define ANDROID_FUNCTION_NAME1 "addXueTong"
//#define ANDROID_FUNCTION_NAME "charge"
#define ANDROID_PARAM_TYPE "(Ljava/lang/String;Ljava/lang/String;)V"

ShopBuy2::ShopBuy2()
{
    
}

bool ShopBuy2::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;//弹窗-----------游戏内幸运礼包
		jint proInt = 16;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif

    background = CCSprite::create("guanka1.png");
    this->addChild(background);
    background->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
    
    bg = CCSprite::create("dalibao/hiddenLibao.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
    
	xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("x1.png"), CCSprite::createWithSpriteFrameName("x2.png"), this, menu_selector(ShopBuy2::resume));
	goumai = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("goumai.png"), CCSprite::createWithSpriteFrameName("goumai2.png"), this, menu_selector(ShopBuy2::buy));
    //放大购买按钮尺寸
	goumai->setScale(2.0f);
	
	CCMenu* menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(0, 0);
    menu->addChild(xiaocha);
    
    xiaocha->setPosition(ccp(SIZE.width*0.82, SIZE.height*0.82));
    menu->addChild(goumai);
    goumai->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.22));
    return true;
}

CCScene* ShopBuy2::scene(CCRenderTexture *sqr, bool isFlip )
{
    CCScene *scene = CCScene::create();
    ShopBuy2* layer = ShopBuy2::create();
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    _spr->setColor(ccGRAY);  //颜色（变灰暗）
    scene->addChild(_spr);
    return scene;
}

void ShopBuy2::showInfo(int id)
{
	CCLOG("ShopBuy2::showInfo");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    jobject jobj;
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo, ANDROID_CLASS_NAME1,
                                                ANDROID_FUNCTION_NAME1,
                                                 "(I)V");

    if (isHave)
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id);
        
    }else
    {
        
    }
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SHOP->C_backAction(id);

#endif
}

void ShopBuy2::buy(CCObject* pSender)
{
    this->scheduleOnce(schedule_selector(ShopBuy2::buy2 ), 0.1);
    
    if (HUB!=NULL)
    {
        //HUB->setVisible(false);
        //gameLayer->setVisible(false);
    }
    

    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 0), 800, 480);
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer,10001,10001);
}

void ShopBuy2::buy2( float dt)
{
	//计费点
    showInfo(31);
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.mp3"/*.wav*/);
    CCDirector::sharedDirector()->popScene();
    
}



void ShopBuy2::resume(CCObject* pSender)
{
   
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.mp3"/*.wav*/);
    CCDirector::sharedDirector()->popScene();
}