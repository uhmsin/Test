//
//  ShopScene.cpp
//  king04
//
//  Created by mac on 14-5-15.
//
//

#include "ShopScene.h"
#include "HubShop.h"
#include "Game.h"
#include "SelectScene.h"
#include "GameData.h"
#include "Dalibao.h"
#include "Define.h"

void ShopScene::keyBackClicked()
{

	CCLOG("ShopScene");



}

CCScene* ShopScene::scene()
{
    CCScene* scene = CCScene::create();
    ShopScene* layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
}

void ShopScene::onEnterTransitionDidFinish()
{
	PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/jiemianbgmusic.mp3", true);
}

bool ShopScene::init()
{
    if (!BaseLayer::init())
    {
        return false;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;//游戏界面——街道界面
		jint proInt = 2;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif


    goumaiweizhi = 1;
    bg = CCSprite::create("shopsc/ditu.jpg");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    
    nvrole = CCSprite::createWithSpriteFrameName("nvrole.png");
    this->addChild(nvrole);
    nvrole->setPosition(ccp(SIZE.width*0.28, SIZE.height*0.28));
    nvrole->setAnchorPoint(ccp(0.5, 0));
   
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("shopsc/112121/112121.ExportJson");
    duboji = CCArmature::create("112121");
    this->addChild(duboji);
    duboji->setPosition(ccp(SIZE.width*0.2, SIZE.height*0.28));
    duboji->setAnchorPoint(ccp(0.5, 0));
    duboji->getAnimation()->playWithIndex(0);
    duboji->setScale(1.3f);
    
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("shopsc/baoxiang/baoxiang.ExportJson");
    baoxiang = CCArmature::create("baoxiang");
    this->addChild(baoxiang);
    baoxiang->setPosition(ccp(SIZE.width*0.65, SIZE.height*0.32));
    baoxiang->setAnchorPoint(ccp(0.5, 0));
    baoxiang->getAnimation()->playWithIndex(0);
    baoxiang->setScale(1.3f);
    
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("shopsc/texiao1/texiao1.ExportJson");
    texiao = CCArmature::create("texiao1");
    this->addChild(texiao);
    texiao->setPosition(ccp(SIZE.width*0.85, SIZE.height*0.12));
    texiao->setAnchorPoint(ccp(0.5, 0));
    texiao->getAnimation()->playWithIndex(0);
    texiao->setScale(1.3f);
    
    jinbi = CCSprite::createWithSpriteFrameName("4321.png");
    jinbi->setPosition(ccp(SIZE.width*0.43, SIZE.height*0.32));
    jinbi->setAnchorPoint(ccp(0.5, 0));
    this->addChild(jinbi);
    jinbi->setScale(1.3f);
    
	jiantou = CCSprite::createWithSpriteFrameName("5432.png");
    this->addChild(jiantou);
    jiantou->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, 20)),CCMoveBy::create(0.5f, ccp(0, -20)),NULL)) );
    
    jiantou->setPosition(ccpAdd( jinbi->getPosition() , ccp(0,jinbi->getContentSize().height + 25)));
    
    hero = Hero::create();
    this->addChild(hero, 101, 101);

	//if (this->id == 1)
	if (false)
	{
		hero->nuqi = hero->maxNengliangdou * 100 + 99;
	}
	else
	{
		hero->nuqi = KingData->getLastNuqi();
	}

	



    Game::instance()->setShopRole(hero);
    hero->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.15));
    hero->setAnchorPoint(ccp(0.5, 0));
    hero->shadow2 = CCSprite::createWithSpriteFrameName("yingzi.png");
    this->addChild(hero->shadow2);
    
    
    HubShop* hub = HubShop::create();
    this->addChild(hub,102,102);
    this->scheduleUpdate();
    



	//直接点击按钮
	CCMenu* menu = CCMenu::create();
	this->addChild(menu, 1000);

	CCMenuItemSprite* item_0 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_rw.png"), CCSprite::createWithSpriteFrameName("scxt_rw.png"), this, menu_selector(ShopScene::item_0));
	item_0->setPosition(ccp(SIZE.width*0.2, SIZE.height*0.28));
	item_0->setAnchorPoint(ccp(0.5, 0));
	menu->addChild(item_0);


	CCMenuItemSprite* item_1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_rw.png"), CCSprite::createWithSpriteFrameName("scxt_rw.png"), this, menu_selector(ShopScene::item_1));
	item_1->setPosition(ccp(SIZE.width*0.43, SIZE.height*0.32));
	item_1->setAnchorPoint(ccp(0.5, 0));
	menu->addChild(item_1);


	CCMenuItemSprite* item_2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_rw.png"), CCSprite::createWithSpriteFrameName("scxt_rw.png"), this, menu_selector(ShopScene::item_2));
	item_2->setPosition(ccp(SIZE.width*0.65, SIZE.height*0.32));
	item_2->setAnchorPoint(ccp(0.5, 0));
	menu->addChild(item_2);

	

	CCMenuItemSprite* EnterGame = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("youxikaishi.png"), CCSprite::createWithSpriteFrameName("youxikaishi.png"), this, menu_selector(ShopScene::EnterGame));
	EnterGame->setPosition(ccp(SIZE.width*0.85, SIZE.height*0.12+180));
	EnterGame->setAnchorPoint(ccp(0.5, 0));
	menu->addChild(EnterGame);
	EnterGame->setScale(0.5f);

	CCSprite* jiantou = CCSprite::createWithSpriteFrameName("qtsz_fxj.png");
	EnterGame->addChild(jiantou);
	jiantou->setScale(1.5f);
	jiantou->setPosition(ccp(EnterGame->getContentSize().width/2, 100));

	EnterGame->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCMoveBy::create(0.5f,ccp(50,0)),
		CCMoveBy::create(0.5f,ccp(-50,0))
		,NULL)));

	item_0->setOpacity(0);
	item_1->setOpacity(0);
	item_2->setOpacity(0);

	menu->setPosition(ccp(30,-10));


	//dalibao();
	ShowGift();

    return true;
}

void ShopScene::update(float dt)
{
    updatePosition(dt);
}

void ShopScene::updatePosition(float dt)
{
    bool canRight = true;
    bool canLeft = true;
    
    if (hero->getPositionX() < SIZE.width*0.34)
    {
        goumaiweizhi = 0;
       
        
    }else if (hero->getPositionX() > SIZE.width*0.34 && hero->getPositionX() < SIZE.width*0.55)
    {
        goumaiweizhi = 1;
      
        
    }else if (hero->getPositionX() > SIZE.width*0.55)
    {
        goumaiweizhi = 2;
    }
    
    if (goumaiweizhi != oldgoumaiweizhi)
    {
        oldgoumaiweizhi = goumaiweizhi;
        
        if (goumaiweizhi == 0)
        {
            jiantou->setPosition(ccpAdd( duboji->getPosition() , ccp(0,duboji->getContentSize().height*1.3 + 30)));
            
        }else if (goumaiweizhi == 1)
        {
            jiantou->setPosition(ccpAdd( jinbi->getPosition() , ccp(0,jinbi->getContentSize().height*1.3 + 25)));
            
        }else if (goumaiweizhi == 2)
        {
            jiantou->setPosition(ccpAdd( baoxiang->getPosition() , ccp(0,baoxiang->getContentSize().height*1.2 + 15)));
        }
    }
    
    if (hero->getPositionX()<100)
    {
        canLeft = false;
    }else if (hero->getPositionX() > SIZE.width - 100)
    {
        canRight = false;
    }
    
    int x = 0;
    int speed = hero->speedMain;
    switch (hero->orientation) {
        case  HOLDER:
            x = hero->getPositionX();
            if(!hero->oldPosition.equals(ccp(0,0))){
                
            }
            if (!canLeft)
            {
                x = hero->getPositionX();
            }else if (!canRight)
            {
                
            }else
            {
                
            }
            break;
            
        case LEFT:
            
            if (canLeft  /*&& Role->isBeAttack == false*/)
            {
                x = hero->getPositionX() - dt*speed;
                hero->move();
            }else{
                x = hero->getPositionX();
            }
            break;
        case RIGHT:
            if (canRight /*&& Role->isBeAttack == false*/)
            {
                x = hero->getPositionX() + dt*speed;
                hero->move();
            }else{
                x = hero->getPositionX();
            }
            break;
        default:
            break;
    }
    hero->setPositionX(x);
    if (hero->getBondingBox2().intersectsRect(texiao->boundingBox())  && hero->getPositionX() >texiao->getPositionX() + 10 )
    {
        this->unscheduleAllSelectors();
        CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
    }
}

void ShopScene::item_0(CCObject* _sender)
{
	if (this->getChildByTag(dalibaotag) != NULL)
	{
		return;
	}
	Dalibao* dalibao = Dalibao::create(0);
	dalibao->setPosition(ccp(0, SIZE.height * 1));
	dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
	this->addChild(dalibao, dalibaozorder, dalibaotag);
}
void ShopScene::item_1(CCObject* _sender)
{
	if (this->getChildByTag(dalibaotag) != NULL)
	{
		return;
	}
	Dalibao* dalibao = Dalibao::create(1);
	dalibao->setPosition(ccp(0, SIZE.height * 1));
	dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
	this->addChild(dalibao, dalibaozorder, dalibaotag);
}
void ShopScene::item_2(CCObject* _sender)
{
	if (this->getChildByTag(dalibaotag) != NULL)
	{
		return;
	}
	Dalibao* dalibao = Dalibao::create(2);
	dalibao->setPosition(ccp(0, SIZE.height * 1));
	dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
	this->addChild(dalibao, dalibaozorder, dalibaotag);
}
void ShopScene::EnterGame(CCObject* _sender)
{
	this->unscheduleAllSelectors();
	CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
}

void ShopScene::dalibao()
{
    if (this->getChildByTag(dalibaotag)!=NULL)
    {
        return;
    }
    Dalibao* dalibao =  Dalibao::create(goumaiweizhi);
    dalibao->setPosition(ccp(0 , SIZE.height*1));
    dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f,ccp(0, 0) ) , 2) );
    this->addChild(dalibao,dalibaozorder,dalibaotag);
}


void ShopScene::ShowGift()
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