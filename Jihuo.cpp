//
//  Jihuo.cpp
//  king04
//
//  Created by mac on 14-5-13.
//
//

#include "Jihuo.h"
#include "Define.h"
#include "Hero.h"
#include "Game.h"
#include "GameScene.h"
#include "GameData.h"
#include "SelectScene.h"
#include "LoadingLayer.h"

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

Jihuo::Jihuo()
{
    ispop = false;
}

void Jihuo::onEnterTransitionDidFinish()
{
	CCPoint posNow = this->getPosition();


	this->setPosition(posNow  + ccp(0,SIZE.height));
	this->runAction(CCMoveTo::create(0.5f, posNow));
}

bool Jihuo::init()
{
	//���ߴ��������
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;//����-----------���ߴ����
		jint proInt = 8;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif


    background = CCSprite::create("guanka1.png");
    this->addChild(background);
    background->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
    
    bg = CCSprite::create("dalibao/onlineLibao.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
    
	xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("x1.png"), CCSprite::createWithSpriteFrameName("x2.png"), this, menu_selector(Jihuo::resume));
	goumai = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("goumai.png"), CCSprite::createWithSpriteFrameName("goumai2.png"), this, menu_selector(Jihuo::buy));
	//�Ŵ���ť�ߴ�
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

CCScene* Jihuo::scene(CCRenderTexture *sqr, bool isFlip )
{
    CCScene *scene = CCScene::create();
    Jihuo* layer = Jihuo::create();
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //�Ƿ�ת
    _spr->setColor(ccGRAY);  //��ɫ����Ұ���
    scene->addChild(_spr);
    return scene;
}

void Jihuo::showInfo(int id)
{
	CCLOG("Jihuo::showInfo");
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

void Jihuo::buy(CCObject* pSender)
{
    
    this->scheduleOnce(schedule_selector(Jihuo::buy2 ), 0.1);
    if (HUB!=NULL)
    {
        //HUB->setVisible(false);
        //gameLayer->setVisible(false);
    }
    
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 0), 800, 480);
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer,10001,10001);
  
}

void Jihuo::buy2(float dt)
{
    //�Ʒѵ�
    showInfo(32);

	//�����ֱ�ӽ�����һ��
	if (m_isEnterNext)
	{
		//ֱ�ӽ�����һ��
		CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(guan, moshiID));
	}


    this->removeFromParent();
}
void Jihuo::resume(CCObject* pSender)
{
	//�����ֱ�ӽ�����һ��
	if (m_isEnterNext)
	{
		//ֱ�ӽ�����һ��
		CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(guan, moshiID));
	}


    this->removeFromParent();
}

void Jihuo::update(float dt)
{
    if (this->ispop)
    {
        this->jihuo();
    }
}

void Jihuo::jihuo()
{
    gameLayer->juqingThreeEnd();
    Role->fuhuo();
    CCDirector::sharedDirector()->popScene();
    KingData->setIsJihuo(true);
    HUB->jihuo();
    CCUserDefault::sharedUserDefault()->setBoolForKey("isJihuo",KingData->getIsJihuo());
    CCUserDefault::sharedUserDefault()->flush();
}

