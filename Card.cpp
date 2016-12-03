//
//  Card.cpp
//  king04
//
//  Created by mac on 14-5-27.
//
//

/*#include "Card.h"
#include "ShopBuy.h"
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

Card* Card::create(int id)
{
    Card* card = new Card();
    card->init(id);
    card->autorelease();
    return card;
}

//游戏内技能礼包
bool Card::init(int id)
{
    if (!CCLayer::init())
    {
        return false;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;//弹窗-----------游戏内单个技能礼包
		jint proInt = 15;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif


    this->id = id;
    
    bg = CCSprite::create(cards[id].c_str());
    this->addChild(bg);
	button = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("goumai.png"), CCSprite::createWithSpriteFrameName("goumai2.png"), this, menu_selector(Card::huode));
	//放大购买按钮尺寸
	button->setScale(2.0f);
	
	CCMenu* menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(ccp(0, 0));
    menu->addChild(button);
	
    button->setPosition(ccp(SIZE.width/2, SIZE.height*0.25));
    bg->setPosition(ccp(SIZE.width/2, SIZE.height*0.52));
	xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("x1.png"), CCSprite::createWithSpriteFrameName("x2.png"), this, menu_selector(Card::remove));
    menu->addChild(xiaocha);
    xiaocha->setPosition(ccp(SIZE.width*0.77, SIZE.height*0.74));
    
    return true;
}

CCScene* Card::scene(CCRenderTexture *sqr, bool isFlip ,int id)
{
    CCScene *scene = CCScene::create();
    Card* layer = Card::create(id);
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    scene->addChild(_spr);
    return scene;
}

void Card::remove(CCObject* pSender)
{
	CCLog("Card::remove-->>");
    CCDirector::sharedDirector()->popScene();
}

void Card::huode(CCObject* pSender)
{
    CCLog("Card::huode-->>");

    if (HUB!=NULL)
    {
        //HUB->setVisible(false);
        //gameLayer->setVisible(false);
    }
    
  
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 0), 800, 480);
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer,10001,10001);
    Card::huode2(1.0);
}


void Card::huode2(float dt)
{
	//0   shousheng;
	//1   getBazhinv;
	//2  getBajiubei;
	//3  getJinjiDuobi

    CCLog("huode2-->>");
    if (this->id == 0)
    {
		//计费点
        showInfo(24);
    }else if (this->id == 1)
    {
		//计费点
        showInfo(8);
        //CCDirector::sharedDirector()->pause();
    }else if (this->id == 2)
    {
		//计费点
        showInfo(9);
        //CCDirector::sharedDirector()->pause();
    }else if (this->id == 3)
    {
		//计费点
        showInfo(23);
        //CCDirector::sharedDirector()->pause();
    }
    CCDirector::sharedDirector()->popScene();
}


void Card::showInfo(int id)
{
	//Game::instance()->getGameLayer()->updateSkillCard();

	CCLOG("Card::showInfo");
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
}*/








