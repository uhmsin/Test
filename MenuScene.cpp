///Users/mac/Documents/cocos2d-x-2.2.2/projects/King/proj.ios/King.xcodeproj
//  MenuScene.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "MenuScene.h"
//
//  LoadingScene.cpp
//  GedouKing
//
//  Created by mac on 14-3-26.
//
//

#include "Define.h"
//#include "AboutScene.h"
#include "SelectScene.h"
#include "PersonalAudioEngine.h"
#include "GameData.h"
#include "ShopScene.h"
#include "LoadingLayer.h"
#include "Dalibao.h"
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

bool MenuScene::init()
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
    CCSprite* menu_main = CCSprite::create("menu/zhujiemian_bj.jpg");
    this->addChild(menu_main,-1);
    menu_main->setPosition(CCPoint(SIZE.width/2,SIZE.height/2));
    return true;
}

void MenuScene::screenShake(int frameNum,int yValue)
{
    CCMoveBy* moveUp = CCMoveBy::create(AttackFrame, ccp(0,yValue));
    CCMoveBy* moveDown = dynamic_cast<CCMoveBy*>(moveUp->reverse());
    CCCallFunc* shakeResume = CCCallFunc::create(this,callfunc_selector(GameScene::resumeShake));
    this->getParent()->runAction(CCSequence::create(CCRepeat::create(CCSequence::create(moveUp,moveDown,NULL), frameNum),shakeResume,NULL));
}

void MenuScene::resumeShake(CCObject* pSender)
{
    this->getParent()->setPositionY(0.0f);
}

void MenuScene::onEnterTransitionDidFinish()
{
	if (!m_has_init)
	{
		m_has_init = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		jobject jobj;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo, ANDROID_CLASS_NAME1,
			ANDROID_FUNCTION_NAME1,
			"(I)V");
		if (isHave)
		{
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, -1);

		}
		else
		{

		}
#endif


		CCSprite* menu_title = CCSprite::create("menu/biaoti.png");
		menu_title->setAnchorPoint(ccp(0, 0.5));
		this->addChild(menu_title, 0);
		menu_title->setPosition(CCPoint(SIZE.width*0.05, SIZE.height*0.78));
		menu_title->setScale(2.2f);

		menu_title->runAction(CCSequence::create(CCScaleTo::create(0.5f, 1.0f), CCCallFunc::create(this, callfunc_selector(MenuScene::brate)), NULL));

		CCMenu* menu = CCMenu::create();
		beginItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("youxikaishi.png"), CCSprite::createWithSpriteFrameName("youxikaishi.png"), this, menu_selector(MenuScene::StartGame));
		menu->addChild(beginItem, 2);
		beginItem->setPosition(CCPoint(SIZE.width*1.5, SIZE.height*0.25));
		beginItem->setScale(1.5f);
		beginItem->runAction(CCSequence::create(CCDelayTime::create(0.55f), CCMoveTo::create(0.4f, CCPoint(SIZE.width*0.5, SIZE.height*0.25)), CCCallFunc::create(this, callfunc_selector(MenuScene::begingame)), NULL));

		this->addChild(menu);
		menu->setPosition(ccp(0, 0));

		CCMenuItemSprite* shopbutton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shangcheng1.png"), CCSprite::createWithSpriteFrameName("shangcheng2.png"), this, menu_selector(MenuScene::shopButtonCallback));

		menu->addChild(shopbutton);
		shopbutton->setPosition(ccp(SIZE.width*0.94, SIZE.height*0.07));


		CCMenuItemSprite* onlineLibao = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("zaixianlibao.png"), CCSprite::createWithSpriteFrameName("zaixianlibao.png"), this, menu_selector(MenuScene::onlineLibaoMenu));

		onlineLibao->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.3, 1.2), CCScaleTo::create(0.3, 0.9), NULL)));

		menu->addChild(onlineLibao);
		onlineLibao->setPosition(ccp(SIZE.width*0.82, SIZE.height*0.07));

		//moreGame = CCMenuItemImage::create("menu/youxiji.png", "menu/youxiji.png", this,menu_selector(MenuScene::MoreGame));


		if (KingData->getMusicVolume() > 0)
		{
			music = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::musicOn), CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shengyin.png"), CCSprite::createWithSpriteFrameName("shengyin.png")), CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shengyin2.png"), CCSprite::createWithSpriteFrameName("shengyin2.png")), NULL);
		}
		else
		{
			music = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::musicOn), CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shengyin2.png"), CCSprite::createWithSpriteFrameName("shengyin2.png")), CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shengyin.png"), CCSprite::createWithSpriteFrameName("shengyin.png")), NULL);
		}
		//about = CCMenuItemImage::create("menu/guanyu2.png", "menu/guanyu2.png", this,menu_selector(MenuScene::AboutGame));
		// menu->addChild(about,2);
		// menu->addChild(moreGame,2);
		menu->addChild(music, 2);

		//about->setPosition(ccp(-0.5*SIZE.width, SIZE.height*0.1));
		music->setPosition(ccp(-0.5*SIZE.width, SIZE.height*0.1));
		//moreGame->setPosition(ccp(-0.5*SIZE.width, SIZE.height*0.1));
		music->runAction(CCMoveBy::create(0.65f, ccp(0.6*SIZE.width, 0)));
		//about->runAction(CCMoveBy::create(0.77f, ccp(0.7*SIZE.width, 0)));
		//moreGame->runAction(CCMoveBy::create(0.90f, ccp(0.6*SIZE.width, 0)));

	}
}

void MenuScene::shopButtonCallback(CCObject* pSender)
{
	PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
	CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
	renderTexture->begin();
	this->visit();
	renderTexture->end();
	CCDirector::sharedDirector()->pushScene(ShopBuy::scene(renderTexture, false));
}

void MenuScene::onlineLibaoMenu()
{
	if (this->getChildByTag(10101) == NULL) {
		Jihuo* jihuo = Jihuo::create();
		this->addChild(jihuo, 1010);
		jihuo->setTag(10101);
	}
}

void MenuScene::ShowGift()
{
	int id = rand() % 4;
	if (id < 3 && this->getChildByTag(dalibaotag) == NULL)
	{
		//大礼包 技能 金币 随机
		int big_int = rand() % 3;// 0礼包 1金币 2技能
		if (big_int >= 3)
		{
			big_int = 2;
		}
		//如果随机到了技能 礼包 两个技能都拥有的时候 换成其他两个中的一个
		if (big_int == 2 && KingData->getJinjiDuobi() && KingData->getShoushen())
		{
			int big_or_gold = rand() % 2;
			if (big_or_gold >= 2)
			{
				big_or_gold = 1;
			}
			big_int = big_or_gold;
		}
		Dalibao* dalibao = Dalibao::create(big_int);// 0 1 2
		dalibao->setPosition(ccp(0, SIZE.height * 1));
		dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
		this->addChild(dalibao, dalibaozorder, dalibaotag);
	}
	else
	{
		//在线大礼包
		if (this->getChildByTag(10101) == NULL) {
			Jihuo* jihuo = Jihuo::create();
			this->addChild(jihuo, 1010);
			jihuo->setTag(10101);
		}
	}
}


void MenuScene::onlineLibaoMenu(CCObject* pSender)
{
	onlineLibaoMenu();
}

void MenuScene::musicOn(CCObject* pSender)
{
    
    if(KingData->getMusicVolume() > 0)
    {
        IsmusicOn = 0;
    }else
    {
        IsmusicOn = 1;
    }
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


void MenuScene::begingame()
{
	ShowGift();
	//onlineLibaoMenu();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;
		jint proInt = 1;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif

    beginItem->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(0.5, 250),CCFadeTo::create(0.5, 80),NULL )  ));
}

void MenuScene::brate()
{
    screenShake(8,15);
}

void MenuScene::onEnter()
{
    PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/jiemianbgmusic.mp3",true);
    CCLayer::onEnter();
}

void MenuScene::StartGame(CCObject* pSender)
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    bool inbeginner = KingData->getIsbeginer();
    if (inbeginner)
    {
		KingData->setIsbeginer(false);   //将玩家设为不是第一次进入
		CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", false); //将改写文
		//直接进入了游戏界面
        //CCDirector::sharedDirector()->replaceScene(GameScene::scene(1));
		CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(1, 0));
    }else
    {
        CCDirector::sharedDirector()->replaceScene(ShopScene::scene());
    }

	//CCDirector::sharedDirector()->replaceScene(GameScene::scene(100, 5));
}

/*void MenuScene::AboutGame(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(AboutScene::scene());
}*/

/*void MenuScene::MoreGame(CCObject* pSender)
{
}*/

void MenuScene::openAWebsite(string url)
{
}


void MenuScene::onExit()
{
    PersonalAudioEngine::sharedEngine()->stopAllEffects();
    PersonalAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    CCLayer::onExit();
}

void MenuScene::loadingBack(CCObject* pSender)
{
    
}
cocos2d::CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
	scene->setTag(666);
    return scene;
}
