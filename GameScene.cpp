//
//  GameScene.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "GameScene.h"
#include "Define.h"
#include "Hero.h"
#include "HubLayer.h"
#include "Game.h"
#include "Wave.h"
#include "NpcMap.h"
#include "GameOverScene.h"
//#include "Flower.h"
#include "PersonalAudioEngine.h"
#include "GameData.h"
#include "Prop.h"
#include "SelectScene.h"
#include "ShopBuy.h"
#include "Ef.h"
//#include "TeachScene.h"
#include "XMLData.h"
#include "Bullet.h"
#include "ShopBuy2.h"
#include "Jihuo.h"
#include "Card.h"
//#include "FourJihuo.h" 


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
//背景图
//static int mapsAll[] = {0,1,1,1,3,3,3 ,2,2,2,3,3,3,1,1,1,3,2,1,2,1,3,1};
static int mapsAll[] = { 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2 };

GameScene::~GameScene()
{
    CC_SAFE_RELEASE_NULL(npc);
    CC_SAFE_RELEASE_NULL(waves);
    CC_SAFE_RELEASE_NULL(props);
    CC_SAFE_RELEASE_NULL(bullets);
    Game::instance()->setHero(NULL);
    Game::instance()->setGameLayer(NULL);
    Game::instance()->setHubLayer(NULL);
}

Map* Map::create(int id)
{
    Map* map = new Map();
    map->init(id);
    map->autorelease();
    return map;
}

bool Map::init(int id)
{
    if(id>20 && id!=100)
    {
        id = 20;
    }
    
    if (id == 100)
    {
        s1 = CCSprite::create("maps/map03.jpg");
        CCSprite* s2 = CCSprite::create("maps/map03.jpg");
        CCSprite* s3 = CCSprite::create("maps/map03.jpg");
        CCSize contSizr = s1->getContentSize();
        s1->setAnchorPoint(ccp(0,0));
        s2->setAnchorPoint(ccp(0,0));
        s3->setAnchorPoint(ccp(0,0));
        this->addChild(s1);
        this->addChild(s2);
        this->addChild(s3);
        
        CCLayerColor* black = CCLayerColor::create(ccc4(200, 0, 0,76.5), 3*contSizr.width, SIZE.height);
        this->addChild(black,999999);
        black->runAction( CCRepeatForever::create(CCSequence::create(CCTintTo::create(0.5, 0, 200, 0),CCTintTo::create(0.5, 160, 160, 0),CCTintTo::create(0.5, 0, 0, 200) ,CCTintTo::create(0.5,200, 0, 0),NULL  )  ) );
        s1->setPosition(CCPoint(0,0));
        s2->setPosition(CCPoint(contSizr.width,0));
        s3->setPosition(CCPoint(2*contSizr.width,0));
    }else
    {
    char mapStr[30] = {0};
        sprintf(mapStr, "maps/map%02d.jpg",id);
        s1 = CCSprite::create(mapStr);
        CCSprite* s2 = CCSprite::create(mapStr);
        CCSprite* s3 = CCSprite::create(mapStr);
        CCSize contSizr = s1->getContentSize();
        s1->setAnchorPoint(ccp(0,0));
        s2->setAnchorPoint(ccp(0,0));
        s3->setAnchorPoint(ccp(0,0));
        this->addChild(s1);
        this->addChild(s2);
        this->addChild(s3);
        s1->setPosition(CCPoint(0,0));
        s2->setPosition(CCPoint(contSizr.width,0));
        s3->setPosition(CCPoint(2*contSizr.width,0));
    }

    return true;
}

CCSize Map::getContentSize()
{
    return  CCSize( 3*s1->getContentSize().width, s1->getContentSize().height) ;
}

void GameScene::resumeJiangzhi()
{
    Role->s->resumeSchedulerAndActions();
    Role->s->getAnimation()->resume();
    Role->resumeSchedulerAndActions();
}

GameScene::GameScene()
{
    heroBoss = NULL;
    hasOver = false;
    tip01 = NULL;
    isJuqingFour = false;
    mapThreeJuqing = false;
    killMonsterNum = 0.0f;
    remainTime = 100;
    failture = false;
    kilometer = 0;
    maxLianji = 0;
    isGameOver = false;
    boss = NULL;
    first = true;
    black = NULL;
    isGameStart = false;
    isAddMonster = true;
    tipsTouch = false;
    tip1 = NULL;
    label = NULL;
    label1 = NULL;
    menu = NULL;
    tip2 = NULL;
    isTeach = false;
    juqingThreeIndex = 0;
    jiaodiTishi = NULL;
    mapsHasGoneNum = 0;
    targetKilometer = 600;
    isNuqiTishi = false;
    canSay = true;
}

GameScene* GameScene::create(int index,int modeId)
{
    GameScene* layer = new GameScene();
    layer->autorelease();
    layer->init(index,modeId);
    return layer;
}

bool GameScene::init(int index,int modeId)
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 10;
		jint proInt = index;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif
    }
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;
		jint proInt = 6;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif
    }

	m_isTwo = false;
	if (index == 2)
	{
		index = 8;
		m_isTwo = true;
	}
	
	

    hunhuntouxiang = CCSprite::create("duihuakuang/hunhun.png");
    this->addChild(hunhuntouxiang,99999999);
    hunhuntouxiang->setPosition(ccp(1.1*SIZE.width,10));
    hunhuntouxiang->setAnchorPoint(ccp(0, 0));
    hunhuntouxiang->setVisible(false);
    
    bosstouxiang = CCSprite::create("duihuakuang/BOSS.png");
    this->addChild(bosstouxiang,99999999);
    bosstouxiang->setPosition(ccp(1.1*SIZE.width,10));
    bosstouxiang->setAnchorPoint(ccp(0, 0));
    bosstouxiang->setVisible(false);
    
    nvroletouxiang = CCSprite::create("duihuakuang/xiaowu.png");
    this->addChild(nvroletouxiang,99999999);
    nvroletouxiang->setPosition(ccp(-0.1*SIZE.width,10));
    nvroletouxiang->setAnchorPoint(ccp(1, 0));
    nvroletouxiang->setVisible(false);
    
    roletouxiang = CCSprite::create("duihuakuang/bashen.png");
    this->addChild(roletouxiang,99999999);
    roletouxiang->setPosition(ccp(-0.1*SIZE.width,10));
    roletouxiang->setAnchorPoint(ccp(1, 0));
    roletouxiang->setVisible(false);

    this->modeID = modeId;

    if (index == 3)  //限时模式 限时一分钟，必须杀死20个怪
    {
        remainTime = 68;//60
    }
    else if (index == 6) 
    {
        remainTime = 60;
    }
 
    else if (index == 7)
    {
        targetKilometer = 600;
    }
    else if (index == 9)
    {
        targetKilometer = 800;
    }
    else if (index == 10)
    {
        remainTime = 120;
    }

    else if (index == 14)
    {
        remainTime = 120;
    }
    else if (index == 15)
    {
        targetKilometer = 1200;
    }
    else if (index == 18)
    {
        targetKilometer = 1500;
    }
    else if (index == 19)
    {
        remainTime = 180;
    }
    
    this->setTouchEnabled(true);
    if(index > 20 && index != 100)
    {
        index = 20;
    }
    isGameOver = false;
    isPause = false;
    _menuLayer = NULL;
    
    if (index == 100) {
        bg1 = Map::create(100);
        bg1->setAnchorPoint(ccp(0,0));
        this->addChild(bg1);
        
    }else
    {
        bg1 = Map::create(mapsAll[index]);
        bg1->setAnchorPoint(ccp(0,0));
        this->addChild(bg1);
    }

    if (this->modeID == 3)
    {
        bg2 = Map::create(mapsAll[index]);
        bg2->setAnchorPoint(ccp(0, 0));
        this->addChild(bg2);
        bg2->setPositionX(bg1->getContentSize().width);
    }
    
    id = index;
    waveID = 0;
    monsterNum = 0;
    monsterTypes = 0;
    for (int i=0; i<sizeof(NpcMapDate2[index])/sizeof(int); i++)
    {
        if (NpcMapDate2[index][i] == -1)
        {
            break;
        }
        monsterTypes++;
    }
    initHero();
    monsterNum = NpcMapNums[index-1];
    oldmonsterNum = monsterNum;
    waves = CCArray::create();
    waves->retain();
    this->addWaves();
    npc = CCArray::create();
    npc->retain();
    props = CCArray::create();
    props->retain();
    bullets = CCArray::create();
    bullets->retain();
    bool isBeginner =  KingData->getIsbeginer();
    if(this->id == 1 && isBeginner)
    {
        black = CCLayerColor::create(ccc4(0, 0, 0,255), 3*SIZE.width, SIZE.height);
        this->addChild(black,blackTag);
        this->scheduleOnce(schedule_selector(GameScene::juqingLogic),0.016f);
    }

    bool juqing_thisMap = KingData->getJuqing(index);    //获得本关的剧情
    if ( juqing_thisMap)
    {
         this->scheduleOnce(schedule_selector(GameScene::juqingMap),0.016f);
    }
    
    /*if (this->id == 4 && KingData->getIsJihuo() == false)
    {
          this->scheduleOnce(schedule_selector(GameScene::juqingMap),0.016f);
    }*/

    this->scheduleUpdate();
    this->scheduleOnce(schedule_selector(GameScene::readyGo), 0.6f);
    
    return true;
}

void GameScene::readyGo(float dt)
{
    r = CCSprite::createWithSpriteFrameName("r.png");
	e = CCSprite::createWithSpriteFrameName("e.png");
	a = CCSprite::createWithSpriteFrameName("a.png");
	d = CCSprite::createWithSpriteFrameName("d.png");
	y = CCSprite::createWithSpriteFrameName("y.png");
	g = CCSprite::createWithSpriteFrameName("g.png");
	o = CCSprite::createWithSpriteFrameName("o.png");
    this->addChild(r,readygoTagZorder);
    this->addChild(e,readygoTagZorder);
    this->addChild(a,readygoTagZorder);
    this->addChild(d,readygoTagZorder);
    this->addChild(y,readygoTagZorder);
    this->addChild(g,readygoTagZorder);
    this->addChild(o,readygoTagZorder);
    readyGoArr = CCArray::create();
    readyGoArr->addObject(r);
    readyGoArr->addObject(e);
    readyGoArr->addObject(a);
    readyGoArr->addObject(d);
    readyGoArr->addObject(y);
    g->setVisible(false);
    o->setVisible(false);
    g->setScale(2.0f);
    o->setScale(2.0f);
    CCPoint p = this->convertToNodeSpace(ccp( SIZE.width/2+g->getContentSize().width*-1, SIZE.height/2));
    CCPoint p1 = this->convertToNodeSpace(ccp( SIZE.width/2+o->getContentSize().width*1, SIZE.height/2));
    g->setPosition(p);
    o->setPosition(p1);
    CCObject* obj;
    CCARRAY_FOREACH(readyGoArr, obj)
    {
        int index = readyGoArr->indexOfObject(obj);
        CCSprite* s = dynamic_cast<CCSprite*>(obj);
        s->setScale(0.8);
        CCPoint p = this->convertToNodeSpace(ccp( SIZE.width+s->getContentSize().width*index, SIZE.height/2));
        s->setPosition(p);
        CCMoveBy* move1 = CCMoveBy::create(0.1+index*0.05, ccp(-SIZE.width/2-2*s->getContentSize().width,0));
        CCDelayTime* delay = CCDelayTime::create(0.3f);
        CCMoveBy* move2 = CCMoveBy::create(0.1+index*0.05, ccp(-SIZE.width/2-2.5*s->getContentSize().width,0));
        CCSequence* SEQ = CCSequence::create(move1,delay,move2,NULL);
        s->runAction(SEQ);
    }
    CCDelayTime* delay = CCDelayTime::create(0.98f);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameScene::goReady));
    CCSequence* SEQ = CCSequence::create(delay,call,NULL);
    this->runAction(SEQ);
}

void GameScene::updateSkillCard()
{

	if (this->getChildByTag(601) != NULL && KingData->getShoushen())
	{
		this->getChildByTag(601)->removeFromParentAndCleanup(true);
	}
	if (this->getChildByTag(602) != NULL && KingData->getBazhinv())
	{
		this->getChildByTag(602)->removeFromParentAndCleanup(true);
	}
	if (this->getChildByTag(603) != NULL && KingData->getBajiubei())
	{
		this->getChildByTag(603)->removeFromParentAndCleanup(true);
	}
	if (this->getChildByTag(604) != NULL && KingData->getJinjiDuobi())
	{
		this->getChildByTag(604)->removeFromParentAndCleanup(true);
	}

}

void GameScene::goReady()
{

	/*0   shousheng;
	1   getBazhinv;
	2  getBajiubei;
	3  getJinjiDuobi*/

	//前3关可以在后面再创建1个
	int level_id = 0;
	if (m_isTwo)
	{
		level_id = 2;
	}
	else
	{
		level_id = id;
	}


	
	int left_pos = -320;
	left_pos = left_pos - rand() % 300;

	int right_pos = 340;
	right_pos = right_pos + rand() % 300;

	int mid_pos = 90;
	mid_pos = mid_pos + rand() % 200;

	int skill_num = 0;

	/*if (level_id == 1)
	{
		skill_num = 1;
	}*/





	if (!KingData->getShoushen())
	{
		skill1 = SkillObject::create(0);
		skill1->setPositionY(hero->getPositionY() - hero->bottomH);
		skill1->setPositionX(hero->getPositionX() + left_pos);
		this->addChild(skill1, 9999999,601);
		skill_num++;
	}

	if (!KingData->getJinjiDuobi() && skill_num < 2)
   {
        skill4 = SkillObject::create(3);
        skill4->setPositionY(hero->getPositionY() - hero->bottomH);
		if (skill_num == 0)
		{
			skill4->setPositionX(hero->getPositionX() + left_pos);
		}
		else
		{
			skill4->setPositionX(hero->getPositionX() + right_pos);
		}
		this->addChild(skill4, 9999999, 604);
		skill_num++;
    }

	if (!KingData->getBazhinv() && skill_num < 2)
    {
        skill2 = SkillObject::create(1);
        skill2->setPositionY(hero->getPositionY() - hero->bottomH);
		if (skill_num == 0)
		{
			skill2->setPositionX(hero->getPositionX() + left_pos);
		}
		else
		{
			skill2->setPositionX(hero->getPositionX() + right_pos);
		}
		this->addChild(skill2, 9999999, 601);
		skill_num++;
    }

	if (!KingData->getBajiubei() && skill_num < 2)
    {
        skill3 = SkillObject::create(2);
        skill3->setPositionY(hero->getPositionY() - hero->bottomH);
		if (skill_num == 0)
		{
			skill3->setPositionX(hero->getPositionX() + left_pos);
		}
		else
		{
			skill3->setPositionX(hero->getPositionX() + right_pos);
		}
		this->addChild(skill3, 9999999, 603);
		skill_num++;
    }

	//固定1个 -570 -320 90 340 590 840 

	//运行展示金币 血瓶 怒气的位置有  -520 90 340 540 740 
	int three_pos = 0;
	int four_pos = 0;
	if (skill_num == 0)
	{
		int le_or_r = rand() % 2;
		if (le_or_r == 0)
		{
			three_pos = left_pos;
			four_pos = right_pos;
		}
		else
		{
			four_pos = left_pos;
			three_pos = right_pos;
		}
	}
	else if (skill_num == 1)
	{
		three_pos = right_pos;
	}

	// 4 5 6 8
	int rans_three = rand() % 4;
	int skill_type = 4;
	switch (rans_three)
	{
	case 0:
		skill_type = 4;
		break;
	case 1:
		skill_type = 5;
		break;
	case 2:
		skill_type = 6;
		break;
	}

	if (three_pos != 0)
	{
		SkillObject* _gold_1 = SkillObject::create(skill_type);
		_gold_1->setPositionY(hero->getPositionY() - hero->bottomH);
		this->addChild(_gold_1, 9999999);
		_gold_1->setPositionX(hero->getPositionX() + three_pos);
	}

	if (four_pos != 0)
	{
		SkillObject* _gold_1 = SkillObject::create(8);
		_gold_1->setPositionY(hero->getPositionY() - hero->bottomH);
		this->addChild(_gold_1, 9999999);
		_gold_1->setPositionX(hero->getPositionX() + four_pos);
	}



	// 5是创建免费的金币
	//一定存在
	//去除掉一定出现的免费金币
	/*{
		//-570 - 320  340 590 840

		int rand_gold = rand() % 8;
		int skillType = 7;

		SkillObject* _gold_1 = SkillObject::create(skillType);
		_gold_1->setPositionY(hero->getPositionY() - hero->bottomH);
		this->addChild(_gold_1, 9999999);
		_gold_1->setPositionX(hero->getPositionX() + mid_pos);

	}*/


	

	if (level_id == 7 || level_id == 9 || level_id == 15 || level_id ==18)
	{
		{
			int _pos = 3000 + rand() % 300;
			int rans_three = rand() % 4;
			int skill_type = 4;
			switch (rans_three)
			{
			case 0:
				skill_type = 4;
				break;
			case 1:
				skill_type = 5;
				break;
			case 2:
				skill_type = 6;
				break;
			case 3:
				skill_type = 8;
				break;
			}

			SkillObject* _gold_1 = SkillObject::create(skill_type);
			_gold_1->setPositionY(hero->getPositionY() - hero->bottomH);
			this->addChild(_gold_1, 9999999);
			_gold_1->setPositionX(hero->getPositionX() + _pos);
		}
	}


	/*int pos_xx = 240;
	int distance = 500;
	int rand_distance = 200;

	for (int i = 0; i <= 6; i++)
	{
		{
			pos_xx = pos_xx + distance;
			int _pos = pos_xx + rand() % 300;

			int rand_gold = rand() % 6;
			int skillType = 7;
			if (rand_gold == 0)
			{
				skillType = 8;
			}
			else if (rand_gold ==1)
			{
				skillType = 6;
			}

			SkillObject* _gold_1 = SkillObject::create(skillType);
			_gold_1->setPositionY(hero->getPositionY() - hero->bottomH);
			this->addChild(_gold_1, 9999999);
			_gold_1->setPositionX(hero->getPositionX() + _pos);

		}
		{
		pos_xx = pos_xx + distance;
		int _pos = pos_xx + rand() % 300;
		int rans_three = rand() % 4;
		int skill_type = 4;
		switch (rans_three)
		{
		case 0:
			skill_type = 4;
			break;
		case 1:
			skill_type = 5;
			break;
		case 2:
			skill_type = 6;
			break;
		}

		SkillObject* _gold_1 = SkillObject::create(skill_type);
		_gold_1->setPositionY(hero->getPositionY() - hero->bottomH);
		this->addChild(_gold_1, 9999999);
		_gold_1->setPositionX(hero->getPositionX() + _pos);
	}
	}*/



	//第5关3个地图






    r->removeFromParentAndCleanup(true);
    e->removeFromParentAndCleanup(true);
    a->removeFromParentAndCleanup(true);
    d->removeFromParentAndCleanup(true);
    y->removeFromParentAndCleanup(true);
    g->setVisible(true);
    o->setVisible(true);
    CCDelayTime* delay = CCDelayTime::create(0.3f);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameScene::goReadyCall));
    CCMoveBy* move1 = CCMoveBy::create(0.1f, ccp(-SIZE.width/2-2*g->getContentSize().width,0));
    CCSequence* SEQ = CCSequence::create(delay,move1,call,NULL);
    g->runAction(SEQ);
    CCDelayTime* delay2 = CCDelayTime::create(0.3f);
    CCMoveBy* move2 = CCMoveBy::create(0.1, ccp(SIZE.width/2+2*g->getContentSize().width,0));
    CCSequence* SEQ2 = CCSequence::create(delay2,move2,NULL);
    o->runAction(SEQ2);
}



void GameScene::tishiNuqi()
{
    this->pause1();
    HUB->tishiNuqi();
}

void GameScene::pause1()
{
    this->operateAllSchedulerAndActions2(this, k_Operate_Pause);
}

void GameScene::resume1()
{
    isNuqiTishi = false;
    this->operateAllSchedulerAndActions2(this, k_Operate_Resume);
}

void GameScene::operateAllSchedulerAndActions2(cocos2d::CCNode* node, OperateFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case k_Operate_Pause:
                node->pauseSchedulerAndActions();
                break;
            case k_Operate_Resume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();
        if(array != NULL && array->count()>0){
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions2(child, flag);
            }
        }
    }
}


void GameScene::goReadyCall()
{
	CCLog("GameScene::goReadyCall()-->>starrt");
    if (this->id == 3 && !KingData->getFirstTishiNuqi())
    {
        tishiNuqi();
        isNuqiTishi = true;
        KingData->setFirstTishiNuqi(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("firstTishiNuqi", KingData->getFirstTishiNuqi());
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    isTeach = false;
    isGameStart = true;
    g->removeFromParentAndCleanup(true);
    o->removeFromParentAndCleanup(true);
    
    if (this->id != 100)
    {
		CCLog("GameScene::goReadyCall()-->>this->id != 100");
        this->schedule(schedule_selector(GameScene::gameLogic), 1.0f);
		
    }else
    {
        HUB->setVisible(true);
        heroBoss = Monster::create(16,21);
        this->addChild(heroBoss,heroBoss->getZOrder());
        heroBoss->delegate = this;
        npc->addObject(heroBoss);

    }
	CCLog("GameScene::goReadyCall()-->>modeID=%d!",modeID);
    switch (modeID) {
        case 1:
        {
            HUB->showNpcNum(gameLayer->monsterNum);
            HUB->showTime();
            break;
        }
        case 0:
        {
            HUB->showNpcNum(gameLayer->monsterNum);
            break;
        }
        case 3:
        {
            HUB->showKiloMeter();
            break;
        }
        case 2:
        {
            HUB->showKillMonster();
            break;
        }
        case 4:
        {
            HUB->showTime();
            break;
        }
        default:
            break;
    }
    
    if ( this->id !=100)
    {
		CCLog("GameScene::goReadyCall()-->>this->addBoss");
        this->addBoss();
    }
	CCLog("GameScene::goReadyCall()-->>end");
}

/*void GameScene::Tipstory()
{
    CCDirector::sharedDirector()->pushScene(TipStory::scene());
}*/

void GameScene::addBoss()
{
    if(this->id%4 == 0)
    {
        if (mapThreeJuqing)
        {
            int bossID = 10 + this->id/4;
            boss = Monster::create(bossID, this->id);
            this->addChild(boss);
            boss->delegate = this;
            boss->setAttackP(50000);
            boss->bloodbar->setVisible(false);
        }else
        {
            int bossID = 10 + this->id/4;
            boss = Monster::create(bossID, this->id);
            npc->addObject(boss);
            this->addChild(boss);
            boss->delegate = this;
        }
    }
}

void GameScene::initHero()
{
    hero = Hero::create();
	hero->m_canSkill = true;
    this->addChild(hero,10);
    hero->setPosition(850, SIZE.height/4 + hero->bottomH);
    hero->delegate = this;
    Game::instance()->setHero(hero);
    Game::instance()->setGameLayer(this);
    hero->stand();
    hero->shadow2 = CCSprite::createWithSpriteFrameName("yingzi.png");
    gameLayer->addChild(hero->shadow2);
    
    if (this->id == 1)
    {
        hero->nuqi = hero->maxNengliangdou*100 + 99;
    }else
    {
        hero->nuqi = KingData->getLastNuqi();
    }
}

void GameScene::juqingLogic(float dt)
{
    bool isBeginner =  KingData->getIsbeginer();
    if (isBeginner)
    {
        KingData->setIsbeginer(false);   //将玩家设为不是第一次进入
		CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", false); //将改写文
    }else
    {
         this->unschedule(schedule_selector(GameScene::juqingLogic));
    }
	
	
    /*first = isBeginner;
    if (first)
    {
        HUB->setVisible(false);
        this->Tipstory();
        first = false;
        this->scheduleOnce(schedule_selector(GameScene::tech),0.016f);
    }else*/
    {
        if (black) {
            black->removeFromParentAndCleanup(true);
         }
        this->unschedule(schedule_selector(GameScene::juqingLogic));
    }
	
	
}

void GameScene::juqingMap(float dt)
{
    switch (id) {
        case 1:
        {
            
            HUB->setVisible(true);
            break;
        }
        case 2:
        {
            tipsPause();
            addTips();
            break;
        }
        case 3:
        {
            tipsPause();
            addTips();
            break;
        }
       case 4:
        {
			HUB->setVisible(true);
			break;
            break;
        }
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        {
            tipsPause();
            addTips();
            break;
        }
        default:
        {
            HUB->setVisible(true);
            break;
        }
    }
}

void GameScene::addTip1(int index , int roleid)
{
    canSay = false;
    roletouxiang->setVisible(true);
    label->setVisible(false);
    roletouxiang->setPosition( ccp(hero->getPositionX()-SIZE.width*0.55, 10));
    tip1->runAction(CCMoveTo::create(0.2f, ccp(hero->getPositionX()-SIZE.width*0.5+280,80)));
    
    if (roleid == 0)
    {
        roletouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(hero->getPositionX()-SIZE.width*0.26, 10))
                                                   ,CCCallFunc::create(this, callfunc_selector(GameScene::setText1)),NULL ));
    }else if (roleid == 1)
    {
        nvroletouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(hero->getPositionX() - SIZE.width*0.26, 10))
                                                     ,CCCallFunc::create(this, callfunc_selector(GameScene::setText1)),NULL ));
    }
}

void GameScene::addTip01(int index ,int monsterID)
{
    canSay = false;
    if (monsterID == 1)
    {
         bosstouxiang->setVisible(true);
         bosstouxiang->setPosition( ccp(hero->getPositionX()+SIZE.width*0.55, 10));
    }else
    {
         hunhuntouxiang->setVisible(true);
         hunhuntouxiang->setPosition( ccp(hero->getPositionX()+SIZE.width*0.55, 10));
    }
    tip01->setVisible(true);
    label2->setVisible(false);
    tip01->runAction(CCMoveTo::create(0.2f, ccp(hero->getPositionX() + 0.5*SIZE.width-280,80)));
    
    if (monsterID == 0)
    {
        hunhuntouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(hero->getPositionX()+SIZE.width*0.28, 10))
                                                     ,CCCallFunc::create(this, callfunc_selector(GameScene::setText)),NULL ));
    }else if (monsterID == 1)
    {
        if (index == 101)
        {
            bosstouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(hero->getPositionX()+SIZE.width*0.28, 10))
                                                       ,CCCallFunc::create(this, callfunc_selector(GameScene::setText2)),NULL ));
        }else
        {
            bosstouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(hero->getPositionX()+SIZE.width*0.24, 10))
                                                       ,CCCallFunc::create(this, callfunc_selector(GameScene::setText)),NULL ));
        }
  
    }
    
    // this->schedule(schedule_selector(TipStory::scheduleduihua),0.1);
}

void GameScene::setText1()
{
    canSay = true;
  
    //label->setText(juqingMapText[id]);
	label->setText(I18N_STR(id+121));
    label->setVisible(true);

	label->ignoreContentAdaptWithSize(false); 
	label->setSize(CCSizeMake(250, 100));
}

void GameScene::setText()
{
    canSay = true;
    //label2->setText(juqingMapText[id]);
	label2->setText(I18N_STR(id+121));
    label2->setVisible(true);

	label2->ignoreContentAdaptWithSize(false);
	label2->setSize(CCSizeMake(250, 100));
}

void GameScene::setText2()
{
    canSay = true;
  
	label2->setText(I18N_STR(119));
    label2->setVisible(true);

	label2->ignoreContentAdaptWithSize(false);
	label2->setSize(CCSizeMake(250, 100));
}

void GameScene::addTips()
{
    HUB->setVisible(false);
    tipsTouch = true;
    tip1 = CCSprite::create("duihuakuang/UI80.png");
    tip1->setPosition(ccp( hero->getPositionX()-SIZE.width*0.5 -150, -120));
    this->addChild(tip1,999999);
    tip01 = CCSprite::create("duihuakuang/UI80.png");
    tip01->setPosition(ccp(hero->getPositionX()+SIZE.width*0.5+150,-120));
    this->addChild(tip01,999999);
    label = UILabel::create();
    tip1->addChild(label);
    label->setFontName("CarterOne");
    label->setFontSize(20);
    label->setPosition(ccp(170, tip1->getContentSize().height));
    label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    label->setAnchorPoint(ccp(0, 1));
    label->setColor(ccc3(241, 191, 194));
    label->setTextAreaSize(CCSize(210,150));
    label2 = UILabel::create();
    tip01->addChild(label2);
    label2->setFontName("CarterOne");
    label2->setFontSize(20);
    label2->setPosition(ccp(100, tip01->getContentSize().height));
    label2->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    label2->setAnchorPoint(ccp(0, 1));
    label2->setColor(ccc3(241, 191, 194));
    label2->setTextAreaSize(CCSize(210,150));
	CCLog("GameScene::addTips()-->>");
   /* if ( strcmp(juqingMapTitle[id].c_str(), "��")  == 0 )
    {
        addTip1(id,0);
    }else*/
    {
       addTip01(id,0);
    }
    
}

void GameScene::addTips2()
{
    addTip01(101,1);
    tip3 = CCSprite::create("duihuakuang/duihuakuang_2.png");
    tip3->setAnchorPoint(ccp(0.5, 0));
    UILabel* label3 = UILabel::create();
 
	label3->setText(I18N_STR(120));
	label3->ignoreContentAdaptWithSize(false);
	label3->setSize(CCSizeMake(150, 200));
    tip3->addChild(label3);
    label3->setFontName("CarterOne");
    label3->setFontSize(20);
    label3->setPosition(ccp(30, tip3->getContentSize().height -50));
    label3->setAnchorPoint(ccp(0, 0));
    label3->setColor(ccc3(241, 191, 194));
    boss->addChild(tip3);
    tip3->setAnchorPoint(ccp(0.5, 0.5));
    tip3->setPosition(ccp(0, boss->s->getContentSize().height-30));
}

void GameScene::removeTips()
{
    if (tip1!=NULL)
    {
        tip1->setVisible(false);
    }
    if(tip2!=NULL)
    {
        tip2->setVisible(false);
    }
    if (hunhuntouxiang)
    {
        hunhuntouxiang->setVisible(false);
    }
    if (bosstouxiang)
    {
        bosstouxiang->setVisible(false);
    }
    if (roletouxiang)
    {
          roletouxiang->setVisible(false);
    }
    if (nvroletouxiang)
    {
        nvroletouxiang->setVisible(false);

    }
    if (tip01!=NULL) {
        tip01->setVisible(false);
    }
}

void GameScene::tipsResume()
{
    HUB->setVisible(true);
    this->scheduleUpdate();
    this->scheduleOnce(schedule_selector(GameScene::readyGo), 0.6f);
}

void GameScene::tipsPause()
{
    this->unscheduleAllSelectors();
    this->unscheduleUpdate();
}

void GameScene::tech(float dt)
{
    if (black)
    {
        black->removeFromParentAndCleanup(true);
    }
    HUB->setVisible(true);
    this->isTeach = true;
    this->unschedule(schedule_selector(GameScene::readyGo));
    HUB->isTeach = true;
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson","effect","tx_jiaodi","tx_jiaodi");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    jiaodiTishi = CCArmature::create("tx_jiaodi");
    jiaodiTishi->getAnimation()->playWithIndex(0);
    jiaodiTishi->setPosition(ccp(hero->getPositionX()+300, hero->getPositionY()));
    this->addChild(jiaodiTishi);
    Monster* m = Monster::create(1,this->id);
    this->addChild(m);
    npc->addObject(m);
    m->delegate = this;
    Monster* m2 = Monster::create(2,this->id);
    this->addChild(m2);
    npc->addObject(m2);
    m->delegate = this;
    m->setPositionX(Role->getPositionX() + 340);
    m2->setPositionX(Role->getPositionX() + 375);
    m->s->setScaleX(-1);
    m2->s->setScaleX(-1);
}

void GameScene::gameLogic(float dt)
{
	
    if (isTeach)
    {
         return;
    }
    if (isNuqiTishi)
    {
         return;
    }
    
    if(this->getRemainTime()>=0)
    {
        this->setRemainTime(this->getRemainTime()-1);
    }
    
    if (waveID>=oldmonsterNum)
    {
        isAddMonster = false;
        return;
    }
    else
    {
		
        Wave* wave = this->getCurrentWave();
        static long lastTimeTargetAdded = 0;
        long now = millisecondNow();
		CCLog("now=%d,lastTimeTargetAdded=%d",now,lastTimeTargetAdded);
		
        if( wave!=NULL && (lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->getSpawnRate() * 1000))
        {
			
            if(npc->count()<7 && this->modeID != 3 )
            {
				CCLog("addMonster1");
                this->addMonster();
                lastTimeTargetAdded = now;
            }
            
            if (this->modeID == 3 )
            {
				CCLog("addMonster2");
                this->addMonster();
                lastTimeTargetAdded = now;
            }
			
        }
		
		
    }
	
}

void GameScene::addMonster()
{
    int mons = monsterTypes * CCRANDOM_0_1();
    int monsterId =NpcMapDate2[id][mons];
    
	int map_id = this->id;
	if (m_isTwo)
	{
		map_id = 2;
	}

    int remoteNum = 0;
    CCObject* obj;
    CCARRAY_FOREACH(npc, obj)
    {
        Monster* mons = dynamic_cast<Monster*>(obj);
        if (mons->id == 2)
        {
            remoteNum++;
        }
    }
    
    if (monsterId == 2 && remoteNum>=2)
    {
        if (this->id%4 != 0)
        {
            monsterId =NpcMapDate2[id][mons+1];
            waveID++;
			Monster* m = Monster::create(monsterId, map_id);
            this->addChild(m);
            npc->addObject(m);
            m->delegate = this;
        }
    }else
    {
		
        waveID++;
		CCLog("monsterId=%d,waveID=%d,this->id=%d",monsterId,waveID,this->id);
		Monster* m = Monster::create(monsterId, map_id);
        this->addChild(m);
        npc->addObject(m);
        m->delegate = this;
		
    }
}

void GameScene::update(float dt)
{
	//之前是检测主角不在释放技能状态的时候，弹出

	//修改为技能全部未进入冷却.

	/*if (!show_hide && gameLayer->killMonsterNum >= 3)
	{
		if (!hero->isSkill1 && !hero->isSkill2 &&  !hero->isSkill3)
		{
			show_hide = true;
			gameLayer->shop2();
			KingData->setIsShenmi(true);
			CCUserDefault::sharedUserDefault()->setBoolForKey("isShenmi", true);
			CCUserDefault::sharedUserDefault()->flush();
			CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
		}
	}*/
	if (!show_hide && gameLayer->killMonsterNum >= 5)
	{
		CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill1TimerTag));
		if (timer1->getPercentage() > 50)//第一个技能
		{
			CCProgressTimer* timer2 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill2TimerTag));
			if (timer2->getPercentage() > 75)//第2个技能
			{
				CCProgressTimer* timer3 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill3TimerTag));
				if (timer3->getPercentage() > 75)//第3个技能
				{
					CCProgressTimer* timer4 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill4TimerTag));
					if (timer4->getPercentage() > 50)////第4个技能
					{
						show_hide = true;
						gameLayer->shop2();
						KingData->setIsShenmi(true);
						CCUserDefault::sharedUserDefault()->setBoolForKey("isShenmi", true);
						CCUserDefault::sharedUserDefault()->flush();
						CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
					}
				}
			}
		}
	}


    
    if (hasOver)
    {
        return;
    }
    
    updatePosition(dt);
	if (this->isGameover())
    {
        hasOver = true;
        Gameover(dt);
    }
    checkCollisionWithProps();
    
    if (this->id != 100)
    {
        if (monsterNum>0 && npc->count()==0 && isAddMonster == false)
        {
            for (int i=0; i<monsterNum;i++)
            {
                addMonster();
            }
        }
        
        if (modeID == 4 || modeID == 3)
        {
            if (monsterNum < 3 && npc->count() < 3)
            {
                for (int i=0; i<10;i++)
                {
                    addMonster();
                }
            }
        }
    }
    
}

void GameScene::checkCollisionWithProps()
{
    CCObject* obj;
    CCARRAY_FOREACH(props, obj)
    {
        Prop* prop = dynamic_cast<Prop*>(obj);
        if(Role->getBondingBox().intersectsRect(prop->getBondingBox()) && prop->getIs_hold()==false)
        {
            if(prop->getType() == 1)                    //type 1
            {
                float Random =  CCRANDOM_0_1()*3+1.0f;
                CCSprite* sprite = CCSprite::createWithSpriteFrameName("jl1.png");
                sprite->setScale(2.5f);
                CCMoveBy* moveBy = CCMoveBy::create(Random, ccp(0, 500));
                CCFadeOut* fadeOut = CCFadeOut::create(Random);
                CCSpawn* spawn = CCSpawn::create(moveBy,fadeOut,NULL);
                CCCallFunc* call = CCCallFunc::create(sprite, callfunc_selector(GameScene::removeProp));
                this->addChild(sprite,9898998,8989);
                sprite->runAction(CCSequence::create(spawn,call,NULL));
                sprite->setPosition(prop->getPosition());
                Role->setHP( Role->getHP() + prop->getNum());
                if(Role->getHP() >Role->getMaxHp())
                {
                    Role->setHP(Role->getMaxHp());
                    
                }
            }else if(prop->getType() == 2)           //type2 
            {
                float Random =  CCRANDOM_0_1()*3+1.0f;
                CCSprite* sprite = CCSprite::createWithSpriteFrameName("nl1.png");
                CCMoveBy* moveBy = CCMoveBy::create(Random, ccp(0, 500));
                CCFadeOut* fadeOut = CCFadeOut::create(Random);
                CCSpawn* spawn = CCSpawn::create(moveBy,fadeOut,NULL);
                CCCallFunc* call = CCCallFunc::create(sprite, callfunc_selector(GameScene::removeProp));
                this->addChild(sprite,9898998,8989);
                sprite->runAction(CCSequence::create(spawn,call,NULL));
                sprite->setPosition(prop->getPosition());
                
                if(Role->nuqi + KingData->getExtraNuqi() >(Role->maxNengliangdou)*100 + 99)
                {
                    
                }else
                {
                    Role->nuqi = Role->nuqi + prop->getNum();//怒气值
                }
            }else if (prop->getType() == 3)
            	{
                float Random =  CCRANDOM_0_1()*3+1.0f;
                CCSprite* spriteMOBAN = CCSprite::create("num/jianglifen1.png");
                CCSize size = spriteMOBAN->getContentSize();
                CCSprite* sprite = CCSprite::create("num/jianglifen1.png",CCRect( 10*size.width/11, 0, size.width/11, size.height));
                int num =  prop->getNum();
                CCSprite* s1 =  CCSprite::create("num/jianglifen1.png",CCRect( (num/10)*size.width/11, 0, size.width/11, size.height));
                CCSprite* s2 =  CCSprite::create("num/jianglifen1.png",CCRect( (num%10)*size.width/11, 0, size.width/11, size.height));
                sprite->addChild(s1);
                sprite->addChild(s2);
                s1->setPositionX(1.3*size.width/11);
                s2->setPositionX(2.3*size.width/11);
                s1->setPositionY(size.height/2);
                s2->setPositionY(size.height/2);
                CCMoveBy* moveBy = CCMoveBy::create(Random, ccp(0, 500));
                CCFadeOut* fadeOut = CCFadeOut::create(Random);
                CCSpawn* spawn = CCSpawn::create(moveBy,fadeOut,NULL);
                CCCallFunc* call = CCCallFunc::create(sprite, callfunc_selector(GameScene::removeProp));
                this->addChild(sprite,9898998,8989);
                sprite->runAction(CCSequence::create(spawn,call,NULL));
                sprite->setPosition(prop->getPosition());
                KingData->setMoney(KingData->getMoney() + prop->getNum());    //type3  
				HUB->headUI->changeMoney();
            }
            prop->setIs_hold(true);
            prop->removeFromParentAndCleanup(true);
			PersonalAudioEngine::sharedEngine()->playEffect("music/prop.mp3"/*.wav*/);
        }
    }
}

void GameScene::removeProp()
{
    if (this->getChildByTag(8989))
    {
        this->removeChildByTag(8989);
    }
}

bool GameScene::isGameover()
{
    if (this->id == 100)
    {
        if (heroBoss !=NULL && heroBoss->isDie)
        {
            failture = false;
            return true;
        }
    }
    
    if(hero->abDie)
    {
        failture = true;
        return true;
    }
    
    if (this->modeID == 3)
    {
        if(kilometer > targetKilometer)
        {
            failture = false;
            return true;
        }
    }
    else if (this->modeID == 1 || this->modeID == 4)
    {
        if (this->remainTime <=0)
        {
            if (this->modeID == 1)
            {
                failture = true;
            }
            else if (this->modeID == 4)
            {
                failture = false;
            }
            return true;
        }
    }

    if (modeID != 4)
    {
		//int af = npc->count();
		//if (monsterNum <= 0 && npc->count() <= 0 && modeID != 5)
		if (monsterNum <= 0 && id != 100)
        {
            failture = false;
            return true;
        }
        else
        {
            failture = false;
            return false;
        }

    }else
    {
        failture = false;
        return false;
    }
}

bool GameScene::isHav_RemainTime()
{
    return true;
}

void GameScene::updatePosition(float dt)
{
    bool canRight = true;
    bool canLeft = true;
    CCObject* obj = NULL;
    float minx = hero->getPositionX() - 999999999;
    float maxx = hero->getPositionX() + 999999999;
    hero->isZudang = false;
    CCARRAY_FOREACH(npc, obj)
    {
        Monster* monster = dynamic_cast<Monster*>(obj);
        if(monster->isDie == false && this->id != 100){
            this->protect(monster);  
            if (monster->getZuDangBox().intersectsRect(hero->getZuDangBox()))
            {
                hero->isZudang = true;
               
                int bondWidth = 90;
                if(hero->actionID == 18 || hero->actionID == 10)
                {
                    bondWidth = 0;
                }
                if (monster->getPositionX() + monster->s->getPositionX() > hero->getPositionX() + hero->s->getPositionX())
                {
                    canRight = false;
                    monster->setPositionX( MAX(monster->getPosition().x, monster->oldPosition.x));
                    if(hero->m_state == s_skill)
                    {
                        monster->setPositionX(hero->getPositionX()+bondWidth);
                    }
                    
                    if(monster->getPositionX() < maxx)
                    {
                        maxx = monster->getPositionX() + monster->s->getPositionX();
                    }
                }else
                {
                    canLeft = false;
                    monster->setPositionX( MIN(monster->getPosition().x, monster->oldPosition.x));
                    if(hero->m_state == s_skill)
                    {
                        monster->setPositionX(hero->getPositionX() - bondWidth);
                    }
                    if(monster->getPositionX() > minx)
                    {
                        minx = monster->getPositionX()+ monster->s->getPositionX();
                    }
                }
                hero->oldPosition = hero->getPosition();

            }
            monster->oldPosition = monster->getPosition();
        }
    }
    int x  = 0;
    int speed = hero->speedMain;
    
    if(hero->m_state == s_attack)
    {
        speed = speed/4;
        x = hero->getPositionX() + dt*speed;
    }
    if(hero->isCanDirect == false )
    {
        return;
    }
    if (!Role->isJinjiDuobi) {
        switch (hero->orientation) {
            case  HOLDER:
                hero->isZudang = false;
                x = hero->getPositionX();
                if(!hero->oldPosition.equals(ccp(0,0))){
                    
                }
                if (!canLeft) {
                    x = hero->getPositionX();
                }else if (!canRight) {
                    
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
        
        if (this->modeID!=3)
        {
            float mapSizeX = bg1->getContentSize().width;
            x = MIN(mapSizeX, MAX(x, 100));
            
            protect(hero);
            if(!hero->offMove)
            {
                hero->setPositionX(x);
            }
        }else
        {
            float mapSizeX = bg1->getContentSize().width;
            mapsHasGoneNum = MAX(mapsHasGoneNum,(int)(hero->getPositionX() - SIZE.width/2)/((int)mapSizeX)) ;
            x = MAX(x,  mapsHasGoneNum*mapSizeX + 100);
            protect(hero);
            if(!hero->offMove)
            {
                hero->setPositionX(x);
            }
            bg1->setPositionX(  2*(int)((mapsHasGoneNum+1)/2)  * mapSizeX );
            bg2->setPositionX( (1+2*((int)(mapsHasGoneNum/2))) * mapSizeX );
        }
    }
    
    if( (hero->m_state == s_skill && Role->isCollision) || hero->isqianqian)
    {
        int bondWidth = 90;
        if(hero->actionID == 18 || hero->actionID == 10)
        {
            bondWidth = 0;
        }
        if(canLeft && canRight)
        {
        }else
        {
           
            if( (hero->isqianqian== true) && (hero->m_state != s_skill))
            {
                if(gameLayer->getChildByTag(1000)!=NULL)
                {
                    gameLayer->getChildByTag(1000)->stopAllActions();
                    gameLayer->removeChildByTag(1000);
                }
            }
            if(!canLeft && hero->s->getScaleX()==-1 && (hero->getPositionX()-minx < 200))
            {
                hero->setPositionX(minx+bondWidth);
            }else if (!canRight && hero->s->getScaleX()==1 && (maxx - hero->getPositionX() < 200))
            {
                hero->setPositionX(maxx-bondWidth);
            }
        }
    }
    
    this->setViewpointCenter(this->convertToNodeSpace(hero->convertToWorldSpace(hero->s->getPosition())));
 }

void GameScene::protect(ARPG* arpg) 
{
//    if(arpg->s->getPositionY()<0.001 && arpg->s->getPositionX() < 0.001)
//    {
//        if (arpg->getType() == 1)
//        {
//            if(arpg->getPositionX()<=140)
//            {
//                arpg->setPositionX(140);
//            }else if (arpg->getPositionX() >= bg1->getContentSize().width - 140)
//            {
//                arpg->setPositionX(bg1->getContentSize().width - 140);
//            }
//        }else
//        {
//            if(arpg->getPositionX()<=10)
//            {
//                 arpg->setPositionX(10);
//            }else if (arpg->getPositionX() >= bg1->getContentSize().width - 10)
//            {
//                 arpg->setPositionX(bg1->getContentSize().width - 10);
//            }
//        }
//    }
}

void GameScene::setViewpointCenter(CCPoint P,bool instant)
{
    if (Role->getActionByTag(5555) && abs( int(Role->getPositionX() - Role->oldPosition.x )) <  50 )
    {
        Role->stopActionByTag(5555);
        Role->isqianqian = false;
        return;
    }else
    {

    }
    float mapSizeX = bg1->getContentSize().width;
    if (this->modeID == 3)
    {
        float x = MAX(P.x, mapSizeX*mapsHasGoneNum + (1)*(SIZE.width / 2));
        float viewPointX = SIZE.width/2 - x;
        if(instant == true)
        {
            this->setPositionX(viewPointX);
        }
        else
        {
            if(this->getPositionX() != viewPointX && this->getActionByTag(1001)==NULL)
            {
                CCMoveTo* viewMove = CCMoveTo::create(0.5, ccp(viewPointX,0));
                viewMove->setTag(1001);
                this->runAction(viewMove);
            }
        }
    }else
    {
        float x = MAX(P.x, SIZE.width / 2);
        x = MIN(x, mapSizeX - SIZE.width / 2);
        float viewPointX = SIZE.width/2 - x;
        if(instant == true)
        {
            this->setPositionX(viewPointX);
        }
        else
        {
            if(this->getPositionX() != viewPointX && this->getActionByTag(1001)==NULL)
            {
                CCMoveTo* viewMove = CCMoveTo::create(0.5, ccp(viewPointX,0));
                viewMove->setTag(1001);
                this->runAction(viewMove);
            }
        }
    }
}


void GameScene::addCard(int id)
{
	//弹出卡牌
	//Game::instance()->getHubLayer()->TouchEnd();
	//PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    //CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
   // renderTexture->begin();
    //gameLayer->visit();
    //renderTexture->end();
   // CCDirector::sharedDirector()->pushScene( Card::scene(renderTexture, false, id));*/

//修改为直接调用支付

	CCLog("huode2-->>");
	if (id == 0)
	{
		showInfo(24);
	}
	else if (id == 1)
	{
		showInfo(8);
	}
	else if (id == 2)
	{
		showInfo(9);
	}
	else if (id == 3)
	{
		showInfo(23);
	}
	else if (id == 4)//金币低 
	{
		showInfo(25);
	}
	else if (id == 5)//金币低 
	{
		showInfo(26);
	}
	else if (id == 6)//金币低 
	{
		showInfo(27);
	}
	else if (id == 7)//金币低 
	{
		float Random = CCRANDOM_0_1() * 3 + 1.0f;
		CCSprite* spriteMOBAN = CCSprite::create("num/jianglifen1.png");
		CCSize size = spriteMOBAN->getContentSize();
		CCSprite* sprite = CCSprite::create("num/jianglifen1.png", CCRect(10 * size.width / 11, 0, size.width / 11, size.height));

		int num_rand = rand()%10;
		int num = 99;
		if (num_rand <= 2)
		{
			num = 33;
		}
		else if (num_rand <= 5)
		{
			num = 66;
		}
		else if (num_rand <= 7)
		{
			num = 88;
		}

		CCSprite* s1 = CCSprite::create("num/jianglifen1.png", CCRect((num / 10)*size.width / 11, 0, size.width / 11, size.height));
		CCSprite* s2 = CCSprite::create("num/jianglifen1.png", CCRect((num % 10)*size.width / 11, 0, size.width / 11, size.height));
		sprite->addChild(s1);
		sprite->addChild(s2);
		s1->setPositionX(1.3*size.width / 11);
		s2->setPositionX(2.3*size.width / 11);
		s1->setPositionY(size.height / 2);
		s2->setPositionY(size.height / 2);
		CCMoveBy* moveBy = CCMoveBy::create(Random, ccp(0, 500));
		CCFadeOut* fadeOut = CCFadeOut::create(Random);
		CCSpawn* spawn = CCSpawn::create(moveBy, fadeOut, NULL);
		CCCallFunc* call = CCCallFunc::create(sprite, callfunc_selector(GameScene::removeProp));
		this->addChild(sprite, 9898998, 8989);
		sprite->runAction(CCSequence::create(spawn, call, NULL));
		sprite->setPosition(hero->getPosition());
		KingData->setMoney(KingData->getMoney() + num);    //type3  
		HUB->headUI->changeMoney();
	}
	else if (id == 8)//怒气
	{
		showInfo(15);

		float Random = CCRANDOM_0_1() * 3 + 1.0f;
		CCSprite* sprite = CCSprite::createWithSpriteFrameName("nl1.png");
		CCMoveBy* moveBy = CCMoveBy::create(Random, ccp(0, 500));
		CCFadeOut* fadeOut = CCFadeOut::create(Random);
		CCSpawn* spawn = CCSpawn::create(moveBy, fadeOut, NULL);
		CCCallFunc* call = CCCallFunc::create(sprite, callfunc_selector(GameScene::removeProp));
		this->addChild(sprite, 9898998, 8989);
		sprite->runAction(CCSequence::create(spawn, call, NULL));
		sprite->setPosition(hero->getPosition());
	}

}

void GameScene::showInfo(int id)
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

	}
	else
	{

	}
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SHOP->C_backAction(id);

#endif
}



CCScene* GameScene::scene(int index,int modeId)
{

    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create(index,modeId);
    scene->addChild(layer,0);
	HubLayer* hub = HubLayer::create();
    scene->addChild(hub,1);
    hub->setPosition(0,0);
    hub->setCommonAttackDelegate(layer);
    Game::instance()->setHubLayer(hub);
    
    bool juqing_thisMap = KingData->getJuqing(index);
    if (juqing_thisMap)
    {
        hub->setVisible(false);
    }else
    {
        HUB->setVisible(true);
    }
    bool isBeginner =  KingData->getIsbeginer();
    if (isBeginner) {
        hub->setVisible(false);
    }else
    {
    }
    return scene;
}

void GameScene::commanAttack()
{
    hero->commanAttack();
}

void GameScene::addWaves()
{
    Wave* wave = NULL;
  
    for (int i =0;i< oldmonsterNum; i++)
    {
        int s = CCRANDOM_0_1()*3 + 1;
        if(this->modeID == 4)
        {
            s = CCRANDOM_0_1()*2 + 1;
        }
        if (this->modeID == 1)
        {
            s = CCRANDOM_0_1()*2 + 1;
        }
        wave = Wave::create(s);
        waves->addObject(wave);
    }
}

Wave* GameScene::getCurrentWave()
{
    if( waveID >= waves->count())
    {
        return NULL;
    }
    Wave* wave = (Wave*)waves->objectAtIndex(waveID);
	return wave;
}

bool GameScene::actionDidAttack(ARPG* p)
{
    bool didHit = false;
    CCPoint attackPosition;

    if (p == hero)
    {
        CCObject* obj;
        CCARRAY_FOREACH(npc, obj)
        {
            ARPG* monster = (ARPG*)obj;
            if(this->collisionBetweenAttacker(p, monster, attackPosition) && monster->isDie == false)
            {
                monster->suffer(hero,1);
                didHit = true;
            }
        }
        Role->has_hitARPG = didHit;
        if (Role->has_hitARPG)
        {
            Role->hasCollisionNum++;
        }
        CCObject* bulletObj;
        CCARRAY_FOREACH(bullets, bulletObj)
        {
            Bullet* bullet = dynamic_cast<Bullet*>(bulletObj);
            if (Role->getAttackBox().intersectsRect(bullet->getBondingBox()))
            {
                bullet->remove();
            }
        }
        return didHit;
    }
    else
    {
        if (this->collisionBetweenAttacker(p, hero, attackPosition))
        {
            hero->suffer(p, 1);
            didHit = true;
        }
        return didHit;
    }
}

bool GameScene::actionDidDie(ARPG* p)
{
    return false;
}

bool GameScene::collisionBetweenAttacker(ARPG* attacker,ARPG* target,CCPoint position)
{
    if (!attacker->isFight(target)) {
        return false;
    }else if(attacker->getAttackBox().intersectsRect(target->getBondingBox()) )
    {
        target->setIsEffectAttack(false);
        return true;
    }else if(attacker->effectRect.intersectsRect(target->getBondingBox()))
    {
        target->setIsEffectAttack(true);
        return true;
    }
    return false;
}

void GameScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
    addCache();
    if (isGameStart)
    {
        //PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }else
    {
        PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/kof20001.mp3",true);
    }
}

void GameScene::onExit()
{
	//弹出卡牌
	Game::instance()->getHubLayer()->TouchEnd();

    PersonalAudioEngine::sharedEngine()->stopAllEffects();
    //PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CCLayer::onExit();
}

void GameScene::Gameover(float dt)
{
	CCLog("GameScene::Gameover-->");
    if(failture == false)
    {
        this->alertData();
        PersonalAudioEngine::sharedEngine()->playEffect("music/ko.mp3");
    }
    HUB->setVisible(false);
    this->isGameOver = true;
    Role->wudi = true;
    CCDelayTime* delay;
    if (this->id% 4 == 0)
    {
        delay  = CCDelayTime::create(2.0f);
    }else
    {
        delay  = CCDelayTime::create(1.6f);
    }

    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameScene::GameoverCallback));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    this->runAction(seq);
}

void GameScene::screenShake(int frameNum,int yValue)
{
    CCMoveBy* moveUp = CCMoveBy::create(AttackFrame, ccp(0,yValue));
    CCMoveBy* moveDown = dynamic_cast<CCMoveBy*>(moveUp->reverse());
    CCCallFunc* shakeResume = CCCallFunc::create(this,callfunc_selector(GameScene::resumeShake));
    this->getParent()->runAction(CCSequence::create(CCRepeat::create(CCSequence::create(moveUp,moveDown,NULL), frameNum),shakeResume,NULL));
}

void GameScene::resumeShake()
{
    this->getParent()->setPositionY(0.0f);
}

void GameScene::alertData()
{
	int m_mapid = this->id;
	if (m_isTwo)
	{
		m_mapid = 2;
	}

	if (m_mapid == KingData->getMapIndex())
    {
        KingData->alertMapIndex(1);
    }
}

void GameScene::GameoverCallback()
{
    KingData->setLastNuqi(Role->nuqi);
    CCUserDefault::sharedUserDefault()->setBoolForKey("lastNuqi",KingData->getLastNuqi());
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    if (!Role->isDie && Role->abDie && monsterNum > 0)
    {
        Role->abDie = false;
        return;
    }

	//弹出卡牌
	Game::instance()->getHubLayer()->TouchEnd();


	if (this->failture)
	{
		KingData->setFirstTishiShuxing(false);
		CCLOG("KingData->getFirstTishiShuxing 2");
		CCUserDefault::sharedUserDefault()->setBoolForKey("firstTishiShuxing", KingData->getFirstTishiShuxing());
		CCLOG("KingData->getFirstTishiShuxing 3");
		CCUserDefault::sharedUserDefault()->flush();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		std::string _strs = "";
		JniMethodInfo methodInfo;
		bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
		if (ishave)
		{
			jint TypeInt = 11;
			jint proInt = 0;
			jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
		}
#endif
	}
	else
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		std::string _strs = "";
		JniMethodInfo methodInfo;
		bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
		if (ishave)
		{
			jint TypeInt = 12;
			jint proInt = 0;
			jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
		}
#endif

	}
	
	int m_id = this->id + 1;

	if (m_isTwo)
	{
		m_id = 3;
	}

	this->getParent()->addChild(GameOverScene::create(this->getMaxLianji(), Role->getHPPercent(), this->getRemainTime(), m_id, this->failture), 99999999, 66666);
//    this->unscheduleAllSelectors();
    
    this->scheduleOnce(schedule_selector(GameScene::removeNpc), 1.5f);
}

void GameScene::removeNpc(float dt)
{
    CCObject* pSender;
    CCARRAY_FOREACH(npc, pSender)
    {
        CCNode* node  =dynamic_cast<CCNode*>(pSender);
        node->removeFromParent();
    }
}

#pragma mark
void GameScene::hitEffect(CCPoint p)
{
    Ef* ef = Ef::create("tx_shouji2");
    if(ef->getScaleX() == -1)
    {
        ef->setPosition(ccpAdd(ccp(50,0),  p));
    }else
    {
        ef->setPosition(ccpAdd(ccp(-50,0),  p));
    }
    this->addChild(ef,10000);
    ef->setScaleX(Role->s->getScaleX());
}

void GameScene::remove(CCNode* pSender)
{
    pSender->removeFromParentAndCleanup(true);
}

void GameScene::pause(CCObject* pSender)
{
    if (!HUB->canTouch)
    {
        return;
    }
    
    if (HUB->isTeach)
    {
        return;
    }
    CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
    renderTexture->begin();
    gameLayer->visit();
    renderTexture->end();
    CCDirector::sharedDirector()->pushScene( MenuLayer::scene(renderTexture));
}

void GameScene::shop(CCObject* pSender)
{
    if (HUB->isTeach)
    {
        return;
    }
    //PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
    renderTexture->begin();
    gameLayer->visit();
    renderTexture->end();
    if (!HUB->canTouch)
    {
        HUB->removetishiNuqi1();
        
        CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false,3));
    }else
    {
         CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false));
    }
}

void GameScene::shop2()
{
    if (HUB->isTeach)
    {
        return;
    }
    //PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
    renderTexture->begin();
    gameLayer->visit();
    renderTexture->end();
    CCDirector::sharedDirector()->pushScene( ShopBuy2::scene(renderTexture,false));
}

/*void GameScene::jihuo()
{*/
	
	//PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    /*if(mapThreeJuqing)
    {
      
        removeTips();
        if(boss)
        {
            boss->removeFromParentAndCleanup(true);
            boss->shadow->removeFromParentAndCleanup(true);
        }
    }

    CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
    renderTexture->begin();
    gameLayer->visit();
    renderTexture->end();
    CCDirector::sharedDirector()->pushScene(FourJihuo::scene(renderTexture,false));
	


    
}*/

void GameScene::shop(int index)
{
    //PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    if(mapThreeJuqing)
    {
        removeTips();
        if(boss)
        {
            boss->removeFromParentAndCleanup(true);
            boss->shadow->removeFromParentAndCleanup(true);
        }
    }
    CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
    renderTexture->begin();
    gameLayer->visit();
    renderTexture->end();
    CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false,index));
}

void GameScene::resume()
{
    //PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
    gameLayer->setIsPause(false);
    this->operateAllSchedulerAndActions(this, k_Operate_Resume);
    HUB->setTouchEnabled(true);
    this->setTouchEnabled(true);
}

void GameScene::sound()
{
    bool flag = KingData->getSoundVolume()>0;
    PersonalAudioEngine::sharedEngine()->setEffectsVolume(!flag);
}

void GameScene::music()
{
    bool flag = KingData->getMusicVolume()>0;
    PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(!flag);
}

void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
    switch (flag)
    {
        case k_Operate_Pause:
            CCDirector::sharedDirector()->pause();
            break;
        case k_Operate_Resume:
             CCDirector::sharedDirector()->resume();
            break;
        default:
            break;
    }
}

void GameScene::addCache()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect/zadi.plist", "effect/zadi.png");
}

void GameScene::next(CCObject* pSender)
{
     CCDirector::sharedDirector()->replaceScene(GameScene::scene(id+1));
}

void GameScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,false);
}
bool GameScene::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if (canSay == false && isGameStart == true)
    {
        return false;
    }
    if (tipsTouch)
    {
        if(this->id !=4)
        {
            tipsTouch = false;
            tipsResume();
            this->removeTips();
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }else
        {
            if(juqingThreeIndex==0)
            {
                 mapThreeLogic();
                 juqingThreeIndex = 1;
            }
        }
    }
    return true;
}

void GameScene::mapThreeLogic()
{
    removeTips();
    mapThreeJuqing = true;
    addBoss();
    this->schedule(schedule_selector(GameScene::JuqingHeroDie), 0.016);
}

void GameScene::JuqingHeroDie(float dt)
{
    if(hero->isDie)
    {
        this->unschedule(schedule_selector(GameScene::JuqingHeroDie));
        addTips2();
    }
}

void GameScene::juqingThreeEnd()
{
    mapThreeJuqing = false;
    CCDelayTime* delay = CCDelayTime::create(3);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameScene::juqingThreeEndCallback));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    this->runAction(seq);
}

void GameScene::juqingThreeEndCallback()
{
    this->tipsResume();
}

