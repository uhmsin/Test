//
//  Dalibao.cpp
//  king04
//
//  Created by mac on 14-5-18.
//
//

#include "Dalibao.h"
#include "Define.h"
#include "GameData.h"
#include "HubLayer.h"
#include "Hero.h"
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

Dalibao* Dalibao::create(int id)
{
    Dalibao* libao = new Dalibao();
    libao->init(id);
    libao->autorelease();
    return libao;
}

bool Dalibao::init(int id)
{
    this->id = id;
    switch (id) {
        case 0:
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

				  std::string _strs = "";
				  JniMethodInfo methodInfo;
				  bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
				  if (ishave)
				  {
					  jint TypeInt = 4;//弹窗-----------大礼包
					  jint proInt = 9;
					  jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
					  methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
				  }
#endif


            bg = CCSprite::create("guanka1.png");
            this->addChild(bg);
            bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
            title = CCSprite::create("dalibao/libaobao.png");
            this->addChild(title);
            title->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.56));
			xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("x1.png"), CCSprite::createWithSpriteFrameName("x2.png"), this, menu_selector(Dalibao::resume));
			goumai = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("goumai.png"), CCSprite::createWithSpriteFrameName("goumai2.png"), this, menu_selector(Dalibao::buy));
			//放大购买按钮尺寸
			goumai->setScale(2.0f);
			
			CCMenu* menu = CCMenu::create();
            this->addChild(menu);
            menu->setPosition(0, 0);
            menu->addChild(xiaocha);
            xiaocha->setPosition(ccp(SIZE.width*0.82, SIZE.height*0.82));
            menu->addChild(goumai);
            goumai->setPosition(ccp(SIZE.width*0.50, SIZE.height*0.255));

        }
        break;
            
        case 1:
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

				  std::string _strs = "";
				  JniMethodInfo methodInfo;
				  bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
				  if (ishave)
				  {
					  jint TypeInt = 4;//弹窗-----------金币大礼包
					  jint proInt = 10;
					  jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
					  methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
				  }
#endif

           
            bg = CCSprite::create("guanka1.png");
            this->addChild(bg);
            bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
            
            title = CCSprite::create("dalibao/goldwenzi.png");
            this->addChild(title);
            title->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.56));

            titleMoney = CCSprite::createWithSpriteFrameName("ClikcOnget.png");
            this->addChild(titleMoney);
            titleMoney->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.665));
            
			xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("x1.png"), CCSprite::createWithSpriteFrameName("x2.png"), this, menu_selector(Dalibao::resume));
			goumai = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("goumai.png"), CCSprite::createWithSpriteFrameName("goumai2.png"), this, menu_selector(Dalibao::buy));
			//放大购买按钮尺寸
			goumai->setScale(2.0f);
			
			CCMenu* menu = CCMenu::create();
            this->addChild(menu);
            menu->setPosition(0, 0);
            menu->addChild(xiaocha);
         
            xiaocha->setPosition(ccp(SIZE.width*0.82, SIZE.height*0.82));
            menu->addChild(goumai);
            goumai->setPosition(ccp(SIZE.width*0.50, SIZE.height*0.255));
            
			menu5888 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("5888jin.png"), CCSprite::createWithSpriteFrameName("5888jin.png"), this, menu_selector(Dalibao::jinbi));
			menu2888 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("2888jin.png"), CCSprite::createWithSpriteFrameName("2888jin.png"), this, menu_selector(Dalibao::jinbi));
			menu1888 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("1888jin.png"), CCSprite::createWithSpriteFrameName("1888jin.png"), this, menu_selector(Dalibao::jinbi));
            menu5888->setScale(1.2f);
            menu2888->setScale(1.2f);
            menu1888->setScale(1.2f);
            menu->addChild(menu1888);
            menu->addChild(menu2888);
            menu->addChild(menu5888);
            menu5888->setTag(2);
            menu1888->setTag(0);
            menu2888->setTag(1);
            menu1888->setPosition(SIZE.width*0.34, SIZE.height*0.52);
            menu2888->setPosition(SIZE.width*0.50, SIZE.height*0.52);
            menu5888->setPosition(SIZE.width*0.66, SIZE.height*0.52);
			xuanzekuang = CCSprite::createWithSpriteFrameName("xuanzhongkuang.png");
			this->addChild(xuanzekuang);
			xuanzekuang->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
			xuanzekuang->setScale(1.1f);
			int rand_gold = rand() % 3;
			if (rand_gold == 0)
			{
				this->id = 1888;
				xuanzekuang->setPosition(ccpAdd(menu1888->getPosition(), ccp(0, 0)));
			}
			else if (rand_gold == 1)
			{
				this->id = 2888;
				xuanzekuang->setPosition(ccpAdd(menu2888->getPosition(), ccp(0, 0)));
			}
			else
			{
				this->id = 5888;
				xuanzekuang->setPosition(ccpAdd(menu5888->getPosition(), ccp(0, 0)));
			}

        }
            break;
        case 2:
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

				  std::string _strs = "";
				  JniMethodInfo methodInfo;
				  bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
				  if (ishave)
				  {
					  jint TypeInt = 4;//弹窗-----------技能大礼包
					  jint proInt = 11;
					  jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
					  methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
				  }
#endif

            bg = CCSprite::create("guanka1.png");
            this->addChild(bg);
            bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
            
            title = CCSprite::create("dalibao/huodedalibao.png");
            this->addChild(title);
            title->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.56));
            
			xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("x1.png"), CCSprite::createWithSpriteFrameName("x2.png"), this, menu_selector(Dalibao::resume));
			goumai = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("goumai.png"), CCSprite::createWithSpriteFrameName("goumai2.png"), this, menu_selector(Dalibao::buy));
			//放大购买按钮尺寸
			goumai->setScale(2.0f);
			
			touming = CCSprite::createWithSpriteFrameName("yihuode.png");
            touming2 = CCSprite::createWithSpriteFrameName("yihuode.png");            
			xuanzekuang = CCSprite::createWithSpriteFrameName("xuanzhongkuang.png");
			duobi = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("duobi.png"), CCSprite::createWithSpriteFrameName("duobi.png"), this, menu_selector(Dalibao::duobiMenu));
			shoushen = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shoushen.png"), CCSprite::createWithSpriteFrameName("shoushen.png"), this, menu_selector(Dalibao::shoushenMenu));
            
            CCMenu* menu = CCMenu::create();
            this->addChild(menu,2);
            menu->setPosition(0, 0);
            menu->addChild(xiaocha);
            xiaocha->setPosition(ccp(SIZE.width*0.82, SIZE.height*0.82));
            menu->addChild(goumai);
            goumai->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.26));
            
            this->addChild(touming,1000);
            this->addChild(touming2,1000);
            touming->setScale(0.25);
            touming2->setScale(0.25);
            this->addChild(xuanzekuang);
            menu->addChild(duobi,2);
            menu->addChild(shoushen,2);
            
            duobi->setPosition(ccp(SIZE.width*0.35, SIZE.height*0.55));
            shoushen->setPosition(ccp(SIZE.width*0.65, SIZE.height*0.55));
            xuanzekuang->setPosition(ccpAdd( duobi->getPosition(), ccp(0,0)));
            xuanzekuang->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
 
            this->id = 1000;   //躲避
			int _xPos = 12;
            if (KingData->getJinjiDuobi() && KingData->getShoushen())
            {
                xuanzekuang->stopAllActions();
                xuanzekuang->setVisible(false);
				touming->setPosition(ccpAdd(shoushen->getPosition(), ccp(_xPos, _xPos)));
				touming2->setPosition(ccpAdd(duobi->getPosition(), ccp(_xPos, _xPos)));
                this->id = 3000;  //躲避
            }else
            {
                if (KingData->getJinjiDuobi())
                {
                    
					touming->setPosition(ccpAdd(duobi->getPosition(), ccp(_xPos, _xPos)));
                    xuanzekuang->setPosition(ccpAdd( shoushen->getPosition(), ccp(0,0)));
                    this->id = 2000;  //瘦身
                }else
                {
                    touming->setVisible(false);
                }
                if (KingData->getShoushen())
                {
					touming2->setPosition(ccpAdd(shoushen->getPosition(), ccp(_xPos, _xPos)));
                    xuanzekuang->setPosition(ccpAdd( duobi->getPosition(), ccp(0,0)));
                    this->id = 1000;  //躲避
                }else
                {
                    touming2->setVisible(false);
                }
            }
            libaoid = 1;
        }
            break;
        default:
            break;
    }
    return true;
}

void Dalibao::jinbi(CCObject* pSender)
{
    this->removeChild(titleMoney);
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(pSender);
    int tag = item->getTag();
    if (tag == 0)
    {
        
        titleMoney = CCSprite::createWithSpriteFrameName("ClikcOnget.png");
        this->addChild(titleMoney);
        titleMoney->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.665));
        this->id = 1888;
        xuanzekuang->setPosition(ccpAdd( menu1888->getPosition(), ccp(0, 0)));
    }else if (tag == 1)
    {
        titleMoney = CCSprite::createWithSpriteFrameName("ClikcOnget.png");
        this->addChild(titleMoney);
        titleMoney->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.665));
        this->id = 2888;
        xuanzekuang->setPosition(ccpAdd( menu2888->getPosition(), ccp(0, 0)));
    }else if (tag == 2)
    {
        titleMoney = CCSprite::createWithSpriteFrameName("ClikcOnget.png");
        this->addChild(titleMoney);
        titleMoney->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.665));
        this->id = 5888;
        xuanzekuang->setPosition(ccpAdd( menu5888->getPosition(), ccp(0, 0)));
    }
}


void Dalibao::duobiMenu(CCObject* pSender)
{
    
    if (KingData->getJinjiDuobi() && KingData->getShoushen())
    {
        this->removeFromParent();
		//计费点
        //showInfo(26);
        return;
    }

	int _xPos = 12;
    if (KingData->getJinjiDuobi())
    {
		//touming->setPosition(ccpAdd(shoushen->getPosition(), ccp(_xPos, _xPos)));
        xuanzekuang->setPosition(ccpAdd( shoushen->getPosition(), ccp(0,0)));
        this->id = 2000;  //瘦身
    }else
    {
		xuanzekuang->setPosition(ccpAdd(duobi->getPosition(), ccp(0, 0)));
        this->id = 1000;  //shoushen
        //touming->setVisible(false);
    }

}

void Dalibao::shoushenMenu(CCObject* pSender)
{
    if (KingData->getJinjiDuobi() && KingData->getShoushen())
    {
        this->removeFromParent();
		//计费点
        //showInfo(26);
        return;
    }

	int _xPos = 12;
    if (KingData->getShoushen())
    {
		//touming2->setPosition(ccpAdd(duobi->getPosition(), ccp(_xPos, _xPos)));
        xuanzekuang->setPosition(ccpAdd( duobi->getPosition(), ccp(0,0)));
        this->id = 1000;  //躲避
        return;
    }else
    {
		xuanzekuang->setPosition(ccpAdd(shoushen->getPosition(), ccp(0, 0)));
         this->id = 2000;  //shoushen
         //touming2->setVisible(false);
    }
}


CCScene* Dalibao::scene(int id)
{
    CCScene *scene = CCScene::create();
    Dalibao* layer = Dalibao::create(id);
    scene->addChild(layer,100);
    return scene;
}

void Dalibao::showInfo(int id)
{
	CCLOG("Dalibao::showInfo");
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


void Dalibao::buy2(float dt)
{
    
    switch (id) {
            
        case 0:
        {
				  //计费点
            showInfo(16);
        }
            break;
        case 1:
        {
				  //计费点
            showInfo(21);
        }
            break;
        case 2:
        {
				  //计费点
            showInfo(22);
        }
            break;
        case 1888:
        {
					 //计费点
            showInfo(25);
        }
            break;
        case 2888:
        {
					 //计费点
            showInfo(26);
        }
            break;
        case 5888:
        {
					 //计费点
            showInfo(27);
        }
            break;
            
        case 1000:
        {
            if (KingData->getMoney() < 10000)
            {
				//计费点
				showInfo(23);
            }else
            {
                KingData->setJinjiDuobi(true);
                KingData->alterMoney(-10000);
                CCUserDefault::sharedUserDefault()->setBoolForKey("jinjiduobi",true);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
				//计费点
                //showInfo(29);
            }
        }
            break;
        case 2000:
        {
            if (KingData->getMoney() < 5000)
            {
				//计费点
                showInfo(24);
            }else
            {
                KingData->setShoushen(true);
                KingData->alterMoney(-5000);
                CCUserDefault::sharedUserDefault()->setBoolForKey("shoushen",true);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
				//计费点
                //showInfo(30);
            }
        }
            break;
        case 3000:
        {
					 //计费点
            showInfo(28);
        }
            break;
            
        default:
            break;
    }


	//如果是直接进入下一关
	if (m_isEnterNext)
	{
		//直接进入下一关
	

		CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(guan, moshiID));
	}

    this->removeFromParent();
}

void Dalibao::buy(CCObject* pSender)
{
    this->setVisible(false);
    
    this->scheduleOnce(schedule_selector(Dalibao::buy2 ), 0.2f);

    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 0), 800, 480);
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer,10001,10001);

}

void Dalibao::resume(CCObject* pSender)
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.mp3"/*.wav*/);

	//如果是直接进入下一关
	if (m_isEnterNext)
	{
		//直接进入下一关
		CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(guan, moshiID));
	}

    this->removeFromParent();
}


