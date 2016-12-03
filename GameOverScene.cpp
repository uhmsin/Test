//
//  GameOverScene.cpp
//  King
//
//  Created by mac on 14-3-28.
//
//
#include "GameOverScene.h"
#include "Define.h"
#include "GameData.h"
#include "GuoduScene.h"
#include "Counter.h"
#include "GoldCounterLayer.h"
#include "SelectScene.h"
#include "PersonalAudioEngine.h"
#include "XMLData.h"
#include "ShopScene.h"
#include "TipStory2.h"
#include "TipStory3.h"
#include "Dalibao.h"
#include "LoadingLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

GameOverScene::GameOverScene()
{
    totalScore = 0;
    HeroIsDie = false;
    goldLayer  = NULL;
    goldLayer2 = NULL;
    goldLayer3 = NULL;
    goldLayer4 = NULL;
    goldLayer5 = NULL;
    jixu = NULL;

}

void GameOverScene::update(float dt)
{
	

	if (this->getChildByTag(dalibaotag) == NULL)
	{
		_del += dt;
		if (_del >= 1)
		{
			unscheduleUpdate();
			menuCloseCallback();
		}
		
	}
}


void GameOverScene::ShowGift()
{
	if (HeroIsDie)
	{
		int big_int = 2;
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
		//dalibao->guan = guan;
		//dalibao->moshiID = moshiID[guan];
		//dalibao->m_isEnterNext = !HeroIsDie;
		dalibao->setPosition(ccp(0, SIZE.height * 1));
		dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
		this->addChild(dalibao, dalibaozorder, dalibaotag);
	}
	else
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
			//dalibao->m_isEnterNext = !HeroIsDie;
			//dalibao->guan = guan;
			//dalibao->moshiID = moshiID[guan];
			dalibao->setPosition(ccp(0, SIZE.height * 1));
			dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
			this->addChild(dalibao, dalibaozorder, dalibaotag);
		}
		else
		{
			//在线大礼包
			if (this->getChildByTag(dalibaotag) == NULL) {
				Jihuo* jihuo = Jihuo::create();
				//jihuo->guan = guan;
				//jihuo->moshiID = moshiID[guan];
				//jihuo->m_isEnterNext = !HeroIsDie;
				this->addChild(jihuo, 1010);
				jihuo->setTag(dalibaotag);
			}
		}
	}

}


GameOverScene* GameOverScene::create()
{
	GameOverScene *pRet = new GameOverScene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}
GameOverScene* GameOverScene::create(int lianji,int hpPercent,int remainTime,int guan,bool heroisDie )
{
    GameOverScene *pRet = new GameOverScene();
    if (pRet && pRet->init(lianji,hpPercent,remainTime,guan,heroisDie))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool GameOverScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(goldLayer != NULL && menu->isVisible() )
    {
        goldLayer->setNumbet2(this->getLianji()*50);
        goldLayer2->setNumbet2(this->getHpPercent()*50);
        goldLayer3->setNumbet2(this->getRemainTime()*100);
        goldLayer4->setNumbet2(this->getTotalScore());
        if (goldLayer5!=NULL)
        {
            if (HeroIsDie)
            {
                goldLayer5->setNumbet2(0);
                
            }else
            {
                float jiangliRate =  powf(0.66, guanjiangli);
                int mm = (guan+1)/4;
                if (mm < 1)
                {
                    mm = 1;
                }
                int money = (mm)*(this->getTotalScore()/100);
                goldLayer5->setNumbet2(money*jiangliRate);
            }
        }
    }
    return false;
}

void GameOverScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-129,true);
}

void GameOverScene::callback()
{
	
    
    CCLayerColor* bg2 = CCLayerColor::create(ccc4(0x0c, 0x10, 0x1a, 179), SIZE.width*0.86,SIZE.height*0.73 );
    bg2->ignoreAnchorPointForPosition(false);
    this->addChild(bg2);
    bg2->setPosition(ccp(SIZE.width * 0.5,SIZE.height * 0.44));
    CCScale9Sprite* bgsprite2 = CCScale9Sprite::createWithSpriteFrameName("ggjm_k4.png");
    bgsprite2->setContentSize(bg2->getContentSize());
    this->addChild(bgsprite2,1000);
    bgsprite2->setPosition(bg2->getPosition());
    CCSprite* bg = CCSprite::create("gameover/ggjm_k1.png");
    bg->setPosition(ccp(SIZE.width * 0.5,SIZE.height * 0.45));
    this->addChild(bg);
    CCSprite* lbg1 = CCSprite::create("gameover/ggjm_mj.png");
    CCSprite* lbg2 = CCSprite::create("gameover/ggjm_mj.png");
    CCSprite* lbg3 = CCSprite::create("gameover/ggjm_mj.png");
    CCSprite* lbg4 = CCSprite::create("gameover/ggjm_mj.png");
    
    this->addChild(lbg1,100);
    this->addChild(lbg2,100);
    this->addChild(lbg3,100);
    this->addChild(lbg4,100);
    CCSize bgSize = bg->getContentSize();
    
    lbg1->setAnchorPoint(ccp(0,0));
    lbg2->setAnchorPoint(ccp(0,0));
    lbg3->setAnchorPoint(ccp(0,0));
    lbg4->setAnchorPoint(ccp(0,0));
    lbg1->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.57));
    lbg2->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.455));
    lbg3->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.340));
    lbg4->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.225));
    
    CCSprite* lianji = CCSprite::createWithSpriteFrameName("ggjm_lj.png");
    CCSprite* life = CCSprite::createWithSpriteFrameName("ggjm_sm.png");
    CCSprite* time = CCSprite::createWithSpriteFrameName("ggjm_sj.png");
    CCSprite* total = CCSprite::createWithSpriteFrameName("ggjm_zdf.png");
    
    lianji->setAnchorPoint(ccp(0,0));
    life->setAnchorPoint(ccp(0,0));
    time->setAnchorPoint(ccp(0,0));
    total->setAnchorPoint(ccp(0,0));
    
    lianji->setPositionX(30);
    life->setPositionX(30);
    time->setPositionX(30);
    total->setPositionX(30);
    
    lbg1->addChild(lianji);
    lbg2->addChild(life);
    lbg3->addChild(time);
    lbg4->addChild(total);
    
    CCSprite* reward = CCSprite::createWithSpriteFrameName("ggjm_bx.png");
    this->addChild(reward);
    reward->setPosition(ccp(SIZE.width*0.7,SIZE.height*0.48));
    
    CCSprite* rewardMoney = CCSprite::createWithSpriteFrameName("ggjm_jb.png");
    this->addChild(rewardMoney);
    rewardMoney->setPosition(ccp(SIZE.width*0.7,SIZE.height*0.28));
    
	jixu = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ggjm_jx.png"), CCSprite::createWithSpriteFrameName("ggjm_jxdown.png"), this, menu_selector(GameOverScene::menuCloseCallback));
   
    menu = CCMenu::create();
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
    menu->addChild(jixu);
    menu->setVisible(false);
    
    this->runAction(CCSequence::create(CCDelayTime::create(1.2f),CCCallFunc::create(this, callfunc_selector( GameOverScene::show )  ),NULL  ));
    
    jixu->setPosition(ccp(SIZE.width/2,SIZE.height*0.14));
    
    goldLayer = GoldCounterLayer::create(this->getLianji()*50);
    lbg1->addChild(goldLayer,1000);
    goldLayer->setPosition(ccp(150,20));
    
    
    int hpp = this->getHpPercent();
    if (this->getHpPercent() == 0) {
        hpp = 0;
    }
    
    int hpTole =hpp *50;
    goldLayer2 = GoldCounterLayer::create(hpTole);
    lbg2->addChild(goldLayer2,1500);
    goldLayer2->setPosition(ccp(150,20));
    
    goldLayer3 = GoldCounterLayer::create(this->getRemainTime()*100);
    lbg3->addChild(goldLayer3,1001);
    goldLayer3->setPosition(ccp(150,20));
    
    goldLayer4 = GoldCounterLayer::create(this->getTotalScore());
    lbg4->addChild(goldLayer4,1000);
    goldLayer4->setPosition(ccp(160,20));
    
    if (HeroIsDie)
    {
        goldLayer5 = GoldCounterLayer::create(0);
        rewardMoney->addChild(goldLayer5,1000);
        goldLayer5->setPosition(ccp(70,25));


    }else
    {
        float jiangliRate =  powf(0.66, guanjiangli);
        int mm = (guan+1)/4;
        if (guan == 101)
        {
            mm = (27+1)/4;
        }
        if (mm<1)
        {
            mm = 1;
        }
        int money = jiangliRate*mm*(this->getTotalScore()/100);
        goldLayer5 = GoldCounterLayer::create(money);
        rewardMoney->addChild(goldLayer5,1000);
        goldLayer5->setPosition(ccp(70,25));
        KingData->alterMoney((mm)*(totalScore/100));
    }
}

void GameOverScene::show()
{
	scheduleUpdate();

    menu->setVisible(true);
}


void GameOverScene::setNumber(int number, int ceiling)
{
    number = MIN(ceiling, number);
    number = MAX(number, 0);
    for(int i = 0 ;i < 6;i++)
    {
        Counter* counter = (Counter*)this->getChildByTag(i);
        int digit = number / (int)(pow(10.0, 6-i-1)) % 10;
        counter->setDigit(digit);
    }
}

bool GameOverScene::init(int lianji,int hpPercent,int remainTime,int guan,bool heroisDie )
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;
		jint proInt = 7;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif


	bool bRet = false;

	CCLog("GameOverScene::init->>");
    do
    {
        if(!BaseLayer::init())
        {
            return false;
        }
        PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/gameover.mp3",true);
        this->HeroIsDie = heroisDie;

        this->guan = guan;

		ShowGift();
        
        this->setLianji(lianji);
        this->setHpPercent(hpPercent);
        
        if (!heroisDie)
        {
            this->setRemainTime(remainTime);
        }else
        {
            this->setRemainTime(remainTime/5);
        }
        totalScore = this->getLianji()*50 + this->getHpPercent()*50 + this->getRemainTime()*100;
        if (guan <= 21)
        {
            
            CCLog("GameOverScene::init--1");
            XMLData* xmlData = XMLData::sharedXMLData();
			CCLog("GameOverScene::init--2");
            int score = xmlData->getScore(guan-1);
            int times = xmlData->getTimes(guan-1);
			CCLog("GameOverScene::init--score=%d,times=%d,guan=%d",score,times,guan);
            if (totalScore>score)
            {
            	CCLog("GameOverScene::init--3");
                xmlData->update(guan-1, totalScore,times+1);
				CCLog("GameOverScene::init--4");
            }
			else
            {
            	CCLog("GameOverScene::init--4");
                xmlData->update(guan-1, score,times+1);
				CCLog("GameOverScene::init--5");
            }
            this->guanjiangli = times;
        }
        
        
        
        if (this->guan == 101)
        {
            this->guanjiangli = 1;
        }
        
        this->setTouchEnabled(true);
        CCLayerColor* colorBackground1 = CCLayerColor::create(ccc4(0, 0, 0, 0),SIZE.width*0.5,SIZE.height);
        CCLayerColor* colorBackground2 = CCLayerColor::create(ccc4(0, 0, 0, 0),SIZE.width*0.5,SIZE.height);
        this->addChild(colorBackground1);
        this->addChild(colorBackground2);
        colorBackground1->setAnchorPoint(ccp(0,0));
        colorBackground2->setAnchorPoint(ccp(0,0));
        colorBackground1->ignoreAnchorPointForPosition(false);
        colorBackground2->ignoreAnchorPointForPosition(false);
        colorBackground1->setPosition(ccp(-SIZE.width/2,0));
        colorBackground2->setPosition(ccp(SIZE.width,0));
        colorBackground1->runAction(CCSequence::create(CCEaseIn::create(CCMoveBy::create(1.5, ccp(SIZE.width/2,0)), 2.0) ,NULL));
        colorBackground2->runAction(CCSequence::create( CCEaseIn::create(CCMoveBy::create(1.5, ccp(-SIZE.width/2,0)), 2.0),CCCallFunc::create(this,callfunc_selector(GameOverScene::callback)),NULL));
        
        CCSprite* gongxitongguan;
        if(heroisDie == false)
        {
            gongxitongguan = CCSprite::createWithSpriteFrameName("ggjm_gxtg.png");
            
        }else
        {
            gongxitongguan = CCSprite::createWithSpriteFrameName("fail.png");
        }
        this->addChild(gongxitongguan,100);
        gongxitongguan->setPosition(ccp(SIZE.width/2,SIZE.height*0.6));
        gongxitongguan->setScale(4.0f);
        gongxitongguan->runAction(CCScaleBy::create(1, 0.25));
        gongxitongguan->runAction(CCMoveTo::create(1, ccp(SIZE.width/2,SIZE.height*0.87)));
        bRet = true;
    } while (0);
    return bRet;
}

bool GameOverScene::init()
{
	bool bRet = false;
    do
    {
        if(!BaseLayer::init())
        {
            return false;
        }
        CCSprite* bg = CCSprite::create("UI/gg2.png");
        bg->setPosition(ccp(SIZE.width * 0.5,SIZE.height * 0.5));
        this->addChild(bg);
        bRet = true;
    } while (0);
    return bRet;
}

void GameOverScene::alertData() 
{
    if(HeroIsDie == false && this->guan <=20)
    {
        KingData->alertMapIndex(1);
    }
}

CCScene* GameOverScene::scene()
{
    CCScene *scene = CCScene::create();
    GameOverScene *layer = GameOverScene::create();
    scene->addChild(layer,0);
    return scene;
}

CCScene* GameOverScene::scene(int lianji,int hpPercent,int remainTime,int guan,CCRenderTexture* tx,bool heroisDie )
{
    CCScene *scene = CCScene::create();
    GameOverScene *layer = GameOverScene::create(lianji,hpPercent,remainTime,guan,heroisDie);
    scene->addChild(layer,0);
    CCSprite *_spr = CCSprite::createWithTexture(tx->getSprite()->getTexture());
    _spr->setPosition(ccp(SIZE.width / 2, SIZE.height / 2));
    _spr->setFlipY(true); 
    _spr->setColor(ccGRAY); 
    return scene;
}

void GameOverScene::menuCloseCallback(CCObject* pSender)
{
	menuCloseCallback();
}

void GameOverScene::menuCloseCallback()
{
    if (this->guan == 101)
    {
        //CCDirector::sharedDirector()->resume();
        if (HeroIsDie)
        {
            GuoduScene2* scene = GuoduScene2::create();
            CCDirector::sharedDirector()->replaceScene(scene);
        }else
        {
            CCScene* scene = TipStory3::scene();
            CCDirector::sharedDirector()->replaceScene(scene);
        }
    }else
    {
        
        if (HeroIsDie)//游戏失败了
        {
            //CCDirector::sharedDirector()->resume();
            //CCDirector::sharedDirector()->replaceScene(ShopScene::scene());
			CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
        }
        else
        {
           if (this->guan  <= 20) //游戏成功了直接下一关
            {
                //CCDirector::sharedDirector()->resume();
               // CCDirector::sharedDirector()->replaceScene(ShopScene::scene());

			   //返回选关界面
			   //CCDirector::sharedDirector()->replaceScene(SelectScene::scene());

			   CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(guan, moshiID[guan]));

            }else if(this->guan  == 21)
            {
                //CCDirector::sharedDirector()->resume();
				PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/kof20001.mp3", true);
                CCDirector::sharedDirector()->replaceScene(TipStory2::scene());
            }
        }
    }
    
}
