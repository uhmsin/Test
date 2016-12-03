//
//  ShopBuy.cpp
//  King
//
//  Created by mac on 14-3-28.
//
//

#include "ShopBuy.h"
#include "ShopBuyLayer.h"
#include "HubLayer.h"
#include "Define.h"
#include "cocos-ext.h"
#include "GameData.h"
#include "HubLayer.h"
#include "PlayerHeadUI.h"
#include "PersonalAudioEngine.h"
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

using namespace gui;

ShopBuy::ShopBuy()
{
	m_useSkill = 0;
    currToshoW = 0;
    nengliSort = 0;
    shopSort = 0;
}

void ShopBuy::onEnterTransitionDidFinish()
{
	this->setPositionY(SIZE.height * 2);
	this->runAction(CCMoveTo::create(0.5f, ccp(0, 0)));
}

void ShopBuy::isShowFuhuo()
{

}

void ShopBuy::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-129,true);
}

bool ShopBuy::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(this->isVisible())
    {
        if(bg->boundingBox().containsPoint(pTouch->getLocation()))
        {
            return false;
        }else if(pTouch->getLocation().x < SIZE.width*0.2)
        {
            return false;
        }
        
        return true;
    }else
    {
        return false;
    }
}

bool ShopBuy::init()
{
    if (!CCLayer::init())
    {
      
        return false;
    }
    this->setTouchEnabled(true);
    ShopInit();
	this->setTag(55210);
    return true;
}

void ShopBuy::update(float dt)
{
    char moneyChar[20] = {0};
    sprintf(moneyChar,"x %d",KingData->getMoney());
    current_money_nuM->setText(moneyChar);
    if (KingData->getBazhinv() && duobi->getChildByTag(1001)==NULL)
    {
       
          addGoumai(duobi,  CCPoint(88,88));
        
    }
    if (KingData->getBajiubei()&& shoushen->getChildByTag(1001)==NULL)
    {
          addGoumai(shoushen, CCPoint(88,88));
    }
    if (KingData->getFuhuo()&& fuhuo->getChildByTag(1001)==NULL )
    {
        addGoumai(fuhuo, CCPoint(88,88));
    }
    if (this->ispop)
    {
        Role->fuhuo();
        CCDirector::sharedDirector()->popScene();
    }

	updateAdd();


	if (m_canSkill && m_useSkill != 0)
	{
		skill_time += dt;
		if (skill_time >= 1)
		{
			skill_time = 0;
			m_useSkill = 0;
		}
	}

	if (m_canSkill)
	{
		if (m_useSkill != 0)
		{
			int level = 0;
			//
			switch (m_useSkill)
			{
			case 1:
				level = KingData->getShengmingLevel();
				break;
			case 2:
				level = KingData->getGongjiLevel();
				break;
			case 3:
				level = KingData->getFangyuLevel();
				break;
			case 4:
				level = KingData->getNuqiLevel();
				break;
			}

			if (level >= 10)
			{
				skill_time = 0;
				m_useSkill = 0;
				return;
			}

			int price_life = 1000;
			int price_attack = 2000;
			int price_fangyu = 1000;
			int price_nuqi = 2500;

			int need_money = 0;
			switch (m_useSkill)
			{
			case 1:
				need_money = price_life*(level + 1);
				break;
			case 2:
				need_money = 200 + price_attack*(level - 1);
				break;
			case 3:
				need_money = price_fangyu*(level - 1);
				break;
			case 4:
				need_money = price_nuqi*(level - 1);
				break;
			}

			int money = KingData->getMoney();
			if (money  < need_money)
			{
				return;
			}
			//扣除对应金币
			KingData->alterMoney(-need_money);

			//自动升级
			if (m_useSkill == 1)
			{
				KingData->alterShengMingLevel();
				CCSprite* shengmingdou = CCSprite::createWithSpriteFrameName("scxt_bs1.png");
				shengmingbash->addChild(shengmingdou);
				shengmingdou->setPosition(ccp(1 * (KingData->getShengmingLevel()) * 15 + 7.5, 8.5));
			}
			else if (m_useSkill == 2)
			{
				KingData->alterGongJiLevel();
				CCSprite* gongjidou = CCSprite::createWithSpriteFrameName("scxt_bs2.png");
				gongjibash->addChild(gongjidou);
				gongjidou->setPosition(ccp(1 * (KingData->getGongjiLevel()) * 15 + 7.5, 8.5));
			}
			else if (m_useSkill == 3)
			{
				KingData->alterFangyuLevel();
				CCSprite* fangyudou = CCSprite::createWithSpriteFrameName("scxt_bs3.png");
				fangyubash->addChild(fangyudou);
				fangyudou->setPosition(ccp(1 * (KingData->getFangyuLevel()) * 15 + 7.5, 8.5));
			}
			else if (m_useSkill == 4)
			{
				KingData->alterNuqiLevel();
				CCSprite* nuqidou = CCSprite::createWithSpriteFrameName("scxt_bs4.png");
				nuqibash->addChild(nuqidou);
				nuqidou->setPosition(ccp(1 * (KingData->getNuqiLevel()) * 15 + 7.5, 8.5));
			}

			char moneyChar2[10] = { 0 };
			sprintf(moneyChar2, "- %d", price_life*(1 + KingData->getShengmingLevel()));
			shengmingMoneylabel->setText(moneyChar2);
			if (KingData->getShengmingLevel() >= 10)
			{
				//shengmingMoneylabel->setText("已经最高等级");
				shengmingMoneylabel->setText(I18N_STR(157));

			}
			sprintf(moneyChar2, "- %d", 200 + price_attack*(KingData->getGongjiLevel() - 1));
			gongjitiaoMoneylabel->setText(moneyChar2);
			if (KingData->getGongjiLevel() >= 10)
			{
				//gongjitiaoMoneylabel->setText("已经最高等级");
				gongjitiaoMoneylabel->setText(I18N_STR(157));

			}
			sprintf(moneyChar2, "- %d", price_fangyu*(1 + KingData->getFangyuLevel()));
			fangyutiaoMoneylabel->setText(moneyChar2);

			if (KingData->getFangyuLevel() >= 10)
			{
				//fangyutiaoMoneylabel->setText("已经最高等级");
				fangyutiaoMoneylabel->setText(I18N_STR(157));

			}
			sprintf(moneyChar2, "- %d", price_nuqi*(KingData->getNuqiLevel() + 1 - 2));
			nuqitiaoMoneylabel->setText(moneyChar2);
			if (KingData->getNuqiLevel() >= 10)
			{
				//nuqitiaoMoneylabel->setText("已经最高等级");
				nuqitiaoMoneylabel->setText(I18N_STR(157));

			}


			skill_time = 0;
			m_useSkill = 0;
		}
	}

}

void ShopBuy::updateAdd()
{
	


	if (KingData->getShengmingLevel()< 10)
	{
		_add_0->setVisible(true);
	}
	else
	{
		_add_0->setVisible(false);
	}

	if (KingData->getGongjiLevel()< 10)
	{
		_add_1->setVisible(true);
	}
	else
	{
		_add_1->setVisible(false);
	}

	if (KingData->getFangyuLevel()< 10)
	{
		_add_2->setVisible(true);
	}
	else
	{
		_add_2->setVisible(false);
	}

	if (KingData->getNuqiLevel()< 10)
	{
		_add_3->setVisible(true);
	}
	else
	{
		_add_3->setVisible(false);
	}

}


void ShopBuy::ShopInit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;//弹窗-----------商店技能 12 升级 13 金币 14
		jint proInt = 12;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif
    
	tishi_sprite = CCSprite::create("tishi.png");
	addChild(tishi_sprite, 2002);
	tishi_sprite->setScale(8.0f);
	tishi_sprite->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.0f, 0.0f), CCScaleTo::create(0.0f, 8.0f), NULL)));
	tishi_sprite->setVisible(false);


    tip1 = CCSprite::create("duihuakuang/UI80.png");
    jiaoshi = CCSprite::create("duihuakuang/jiaoshi.png");
    this->addChild(jiaoshi,9999999);
    this->addChild(tip1,999999);
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    jiaoshi->setAnchorPoint(ccp(0.5, 0));
    tip1->setPosition(ccp( -150, -120));
    label = UILabel::create();
    tip1->addChild(label);
    label->setFontName("CarterOne");
    label->setFontSize(20);
    label->setPosition(ccp(120, tip1->getContentSize().height));
    label->setAnchorPoint(ccp(0, 1));
    label->setColor(ccc3(241, 191, 194));
    label->setTextAreaSize(CCSize(200,150));
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    
    
    ispop = false;
    Game::instance()->setShopLayer(this);
    this->scheduleUpdate();
    current_money = CCSprite::createWithSpriteFrameName("scnl_qb.png");
    current_money_nuM = UILabel::create();
    current_money->addChild(current_money_nuM);
    current_money_nuM->setFontName("CarterOne");
    current_money_nuM->setColor(ccc3(0xe3, 0x9e, 0x78));
    current_money_nuM->setFontSize(16);
    current_money_nuM->setPosition(ccp(130,10));
    char moneyChar[20] = {0};
    sprintf(moneyChar,"x %d",KingData->getMoney());
    current_money_nuM->setText(moneyChar);
    this->addChild(current_money,200);
    current_money->setPosition(ccp(SIZE.width*0.7,SIZE.height*0.86));
    bg = CCScale9Sprite::create("scnl_dk1.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width*0.5325, SIZE.height/2));
    bg->setContentSize(CCSize(SIZE.width*0.8,SIZE.height*0.8));
	CCMenuItemSprite* nengli = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_nl_down.png"), CCSprite::createWithSpriteFrameName("scnl_nl.png"), CCSprite::createWithSpriteFrameName("scnl_nl.png"), this, menu_selector(ShopBuy::qiehuanCallback));
	CCMenuItemSprite* xuetong = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_xt_down.png"), CCSprite::createWithSpriteFrameName("scnl_xt.png"), CCSprite::createWithSpriteFrameName("scnl_xt.png"), this, menu_selector(ShopBuy::qiehuanCallback));
	CCMenuItemSprite* shangcheng = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_sc_down.png"), CCSprite::createWithSpriteFrameName("scnl_sc.png"), CCSprite::createWithSpriteFrameName("scnl_sc.png"), this, menu_selector(ShopBuy::qiehuanCallback));
    nengli->setEnabled(false);
    menus = CCArray::create();
    menus->retain();
    menus->addObject(nengli);
    menus->addObject(xuetong);
    menus->addObject(shangcheng);
    menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(ccp(0,0));
    menu->addChild(shangcheng);
    menu->addChild(xuetong);
    menu->addChild(nengli);
    nengli->setPosition(ccp(SIZE.width*0.1,SIZE.height*0.64));
    xuetong->setPosition(ccp(SIZE.width*0.1,SIZE.height*0.47));
    shangcheng->setPosition(ccp(SIZE.width*0.1,SIZE.height*0.30));
    /*****    能力          *****/
    nengliNode = CCNode::create();
    this->addChild(nengliNode);
    nengliNode->setPosition(ccp(0, 0));
    CCScale9Sprite* bg1 = CCScale9Sprite::createWithSpriteFrameName("scnl_dk2.png");
    nengliNode->addChild(bg1);
    bg1->setPosition(ccp(SIZE.width*0.37, SIZE.height/2));
    bg1->setContentSize(CCSize(SIZE.width*0.38,SIZE.height*0.6));
    CCScale9Sprite* bg2 = CCScale9Sprite::createWithSpriteFrameName("scnl_dk2.png");
    nengliNode->addChild(bg2);
    bg2->setPosition(ccp(SIZE.width*0.73, SIZE.height/2));
    bg2->setContentSize(CCSize(SIZE.width*0.32,SIZE.height*0.6));
    CCSprite* nenglidescSprite = CCSprite::createWithSpriteFrameName("scnl_dk3.png");
    nenglidescSprite->setScale(0.85);
    nengliNode->addChild(nenglidescSprite);
    nenglidescSprite->setPosition(ccp(SIZE.width*0.735,SIZE.height*0.58));
    CCSize descSize = nenglidescSprite->getContentSize();
    nengliDescTitle = UILabel::create();
    nengliDescTitle->setFontName("CarterOne");
    nengliDescTitle->setColor(ccc3(0xe3, 0x9e, 0x78));
    nengliDescTitle->setFontSize(22);
    nengliDescTitle->setPosition(ccp(descSize.width/2, descSize.height-20));
    //nengliDescTitle->setText(nenglidescTitle[0]);
    nengliDescTitle->setText(I18N_STR(85));
    nenglidescSprite->addChild(nengliDescTitle);
    nengliDesc = UILabel::create();
    nengliDesc->setColor(ccc3(0xff, 0xae, 0x00));
    nengliDesc->setFontSize(16);
    nengliDesc->setFontName("CarterOne");
	nengliDesc->ignoreContentAdaptWithSize(false);
	nengliDesc->setSize(CCSizeMake(250, 100));
    nengliDesc->setPosition(ccp(descSize.width/2, descSize.height-34));
    //nengliDesc->setText(nenglidescText[0]);
	nengliDesc->setText(I18N_STR(89));
    nenglidescSprite->addChild(nengliDesc);
    nengliDesc->setTextAreaSize(CCSize(descSize.width-20,descSize.height-40));
    nengliDesc->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
    nengliDesc->setAnchorPoint(ccp(0.5,1));
	duobi = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_jjdb.png"), CCSprite::createWithSpriteFrameName("scnl_jjdb.png"), this, menu_selector(ShopBuy::nengliCallback));
	shoushen = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_ss.png"), CCSprite::createWithSpriteFrameName("scnl_ss.png"), this, menu_selector(ShopBuy::nengliCallback));
	fuhuo = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_swfh.png"), CCSprite::createWithSpriteFrameName("scnl_swfh.png"), this, menu_selector(ShopBuy::nengliCallback));
	nuqibao = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_nqb.png"), CCSprite::createWithSpriteFrameName("scnl_nqb.png"), this, menu_selector(ShopBuy::nengliCallback));
 
    nengliArr = CCArray::create();
    nengliArr->retain();
    nengliArr->addObject(duobi);
    nengliArr->addObject(shoushen);
    nengliArr->addObject(fuhuo);
    nengliArr->addObject(nuqibao);
    CCMenu* menuNengLiang = CCMenu::create();
    menuNengLiang->setPosition(ccp(0, 0));
    nengliNode->addChild(menuNengLiang);
    menuNengLiang->addChild(duobi);
    menuNengLiang->addChild(shoushen);
    menuNengLiang->addChild(fuhuo);
    menuNengLiang->addChild(nuqibao);
    duobi->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.65));
    shoushen->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.65));
    fuhuo->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.35));
    nuqibao->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.35));
	
	CCMenuItemSprite* huode = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_hd.png"), CCSprite::createWithSpriteFrameName("scnl_hd_down.png"), this, menu_selector(ShopBuy::huodenengli));
    menuNengLiang->addChild(huode);
    huode->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.28));
    xuanzhongkuang = CCSprite::createWithSpriteFrameName("scnl_xzk.png");
    xuanzhongkuang->setContentSize(duobi->getContentSize());
    xuanzhongkuang->runAction(CCRepeatForever::create(CCSequence::create( CCScaleBy::create(0.2, 1.1),CCScaleBy::create(0.2, 1/1.1) ,NULL ) ));
    nengliNode->addChild(xuanzhongkuang,1000);
    xuanzhongkuang->setPosition(duobi->getPosition());
    if(currToshoW == 5)
    {
        labelnuqi = UILabel::create();
        labelnuqi->setFontSize(25);
        labelnuqi->setColor(ccc3(0xff, 0xae, 0x00));
        //labelnuqi->setText("首次免费购买");
		labelnuqi->setText(""/*I18N_STR(151)*/);
        addChild(labelnuqi,11,9900);
        labelnuqi->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.45));
        
        xuanzhongkuang->setPosition(fuhuo->getPosition());
        if (gameLayer->mapThreeJuqing) {
            //nengliDesc->setText(nenglidescText[4]);
			nengliDesc->setText(I18N_STR(93));
            sprite = CCSprite::createWithSpriteFrameName("help11.png");
            sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f, ccp(0, 50)),CCMoveBy::create(0.2f, ccp(0, -50)),NULL)));
            nengliNode->addChild(sprite,9898);
            sprite->setScale(0.5f);
            sprite->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.3));
			tishi_sprite->setVisible(true);
			tishi_sprite->setPosition(sprite->getPosition());
			tishi_sprite->setPositionY(tishi_sprite->getPositionY() - 46);
        }else{
             //nengliDesc->setText(nenglidescText[2]);
			 nengliDesc->setText(I18N_STR(91));
        }
        //nengliDescTitle->setText(nenglidescTitle[2]);
        nengliDescTitle->setText(I18N_STR(87));
        nengliSort = 2;
    }else if (currToshoW == 3)
    {
        labelnuqi = UILabel::create();
        labelnuqi->setFontSize(25);
        labelnuqi->setColor(ccc3(0xff, 0xae, 0x00));
        //labelnuqi->setText("首次免费购买");
		labelnuqi->setText(""/*I18N_STR(151)*/);
        addChild(labelnuqi,11,9900);
        labelnuqi->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.45));
		//addTip("首次免费购买");
        sprite = CCSprite::createWithSpriteFrameName("help11.png");
        sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)),CCMoveBy::create(0.3f, ccp(0, -30)),NULL)));
        sprite->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.35));
        sprite->setScale(0.5f);
		tishi_sprite->setVisible(true);
		tishi_sprite->setPosition(sprite->getPosition());
		tishi_sprite->setPositionY(tishi_sprite->getPositionY() - 46);
    
        addChild(sprite,2002);
        
        xuanzhongkuang->setPosition(nuqibao->getPosition());
        //nengliDesc->setText(nenglidescText[3]);
		nengliDesc->setText(I18N_STR(92));
        //nengliDescTitle->setText(nenglidescTitle[3]);
		nengliDescTitle->setText(I18N_STR(88));
        nengliSort = 3;
    }else if (currToshoW == 20)
    {
     
        sprite = CCSprite::createWithSpriteFrameName("help11.png");
        sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)),CCMoveBy::create(0.3f, ccp(0, -30)),NULL)));
        sprite->setPosition(ccp(SIZE.width*0.10, SIZE.height*0.55));
    
        sprite->setScale(0.5f);
        addChild(sprite,2002);
		tishi_sprite->setVisible(true);
		tishi_sprite->setPosition(ccp(SIZE.width*0.10, SIZE.height*0.52));

    }else if (currToshoW == 30)
    {
        xuanzhongkuang->setPosition(nuqibao->getPosition());
        //nengliDesc->setText(nenglidescText[3]);
		nengliDesc->setText(I18N_STR(92));
        //nengliDescTitle->setText(nenglidescTitle[3]);
        nengliDescTitle->setText(I18N_STR(88));
        nengliSort = 3;
    }
    
    /*****    血统          *****/
    xuetogNode = CCNode::create();
    this->addChild(xuetogNode);
    xuetogNode->setPosition(ccp(0, 0));
    CCMenu* menuXuetong = CCMenu::create();
    menuXuetong->setPosition(ccp(0, 0));
    xuetogNode->addChild(menuXuetong);
    CCSprite* bashen = CCSprite::createWithSpriteFrameName("scxt_rw.png");
    xuetogNode->addChild(bashen);
    bashen->setPosition(ccp(SIZE.width*0.3,SIZE.height*0.5));
    CCSprite* shengmingtiao = CCSprite::createWithSpriteFrameName("scxt_k1.png");
    CCSprite* gongjitiao = CCSprite::createWithSpriteFrameName("scxt_k1.png");
    CCSprite* fangyutiao = CCSprite::createWithSpriteFrameName("scxt_k1.png");
    CCSprite* nuqitiao = CCSprite::createWithSpriteFrameName("scxt_k1.png");
    xuetogNode->addChild(shengmingtiao);
    xuetogNode->addChild(gongjitiao);
    xuetogNode->addChild(fangyutiao);
    xuetogNode->addChild(nuqitiao);
    shengmingtiao->setPosition(ccp(SIZE.width*0.55, SIZE.height*0.7));
    gongjitiao->setPosition(ccp(SIZE.width*0.61, SIZE.height*0.58));
    fangyutiao->setPosition(ccp(SIZE.width*0.58, SIZE.height*0.46));
    nuqitiao->setPosition(ccp(SIZE.width*0.55, SIZE.height*0.34));
    UILabel* shengminglabel = UILabel::create();
    UILabel* gongjitiaolabel = UILabel::create();
    UILabel* fangyutiaolabel = UILabel::create();
    UILabel* nuqitiaolabel = UILabel::create();
	/*
    shengminglabel->setText("生命");
    gongjitiaolabel->setText("攻击");
    fangyutiaolabel->setText("防御");
    nuqitiaolabel->setText("怒气");
    */
    
    shengminglabel->setText(I18N_STR(153));
    gongjitiaolabel->setText(I18N_STR(154));
    fangyutiaolabel->setText(I18N_STR(155));
    nuqitiaolabel->setText(I18N_STR(156));
    



	
    CCArray* labelarr = CCArray::create();
    labelarr->addObject(shengminglabel);
    labelarr->addObject(gongjitiaolabel);
    labelarr->addObject(fangyutiaolabel);
    labelarr->addObject(nuqitiaolabel);
    CCObject* object;
    CCARRAY_FOREACH(labelarr, object)
    {
        UILabel* label = dynamic_cast<UILabel*>(object);
        label->setColor(ccc3(0xff, 0xae, 0x00));
        label->setFontSize(16);
        label->setFontName("CarterOne");
        label->setPosition(ccp(46, 27));
    }
    shengmingtiao->addChild(shengminglabel);
    gongjitiao->addChild(gongjitiaolabel);
    fangyutiao->addChild(fangyutiaolabel);
    nuqitiao->addChild(nuqitiaolabel);
	shengmingbash = CCSprite::createWithSpriteFrameName("scxt_bs1.png");
	gongjibash = CCSprite::createWithSpriteFrameName("scxt_bs2.png");
	fangyubash = CCSprite::createWithSpriteFrameName("scxt_bs3.png");
	nuqibash = CCSprite::createWithSpriteFrameName("scxt_bs4.png");
    shengmingtiao->addChild(shengmingbash);
    gongjitiao->addChild(gongjibash);
    fangyutiao->addChild(fangyubash);
    nuqitiao->addChild(nuqibash);
    shengmingbash->setPosition(ccp(70, 11));
    gongjibash->setPosition(ccp(70, 11));
    fangyubash->setPosition(ccp(70, 11));
    nuqibash->setPosition(ccp(70, 11));
    for (int i=1; i<=KingData->getShengmingLevel(); i++)
    {
        CCSprite* shengmingdou =CCSprite::createWithSpriteFrameName("scxt_bs1.png");
        shengmingbash->addChild(shengmingdou);
		shengmingdou->setPosition(ccp(1 * i * 15+7.5, 8.5));
    }
    for (int i=1; i<= KingData->getGongjiLevel(); i++)
    {
		CCSprite* gongjidou = CCSprite::createWithSpriteFrameName("scxt_bs2.png");
        gongjibash->addChild(gongjidou);
		gongjidou->setPosition(ccp(1 * i * 15 + 7.5, 8.5));
    }
    for (int i=1; i<= KingData->getFangyuLevel(); i++)
    {
		CCSprite* fangyudou = CCSprite::createWithSpriteFrameName("scxt_bs3.png");
        fangyubash->addChild(fangyudou);
		fangyudou->setPosition(ccp(1 * i * 15 + 7.5, 8.5));
    }
    for (int i=1; i<= KingData->getNuqiLevel(); i++)
    {
		CCSprite* nuqidou = CCSprite::createWithSpriteFrameName("scxt_bs4.png");
        nuqibash->addChild(nuqidou);
		nuqidou->setPosition(ccp(1 * i * 15 + 7.5, 8.5));
    }
    
	CCMenuItemSprite* shengmingAdd = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"), this, menu_selector(ShopBuy::addCallback));
	CCMenuItemSprite* gongjiAdd = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"), this, menu_selector(ShopBuy::addCallback));
	CCMenuItemSprite* fangyuAdd = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"), this, menu_selector(ShopBuy::addCallback));
	CCMenuItemSprite* nuqiAdd = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"), this, menu_selector(ShopBuy::addCallback));
  

    shengmingAdd->setOpacity(0);
    gongjiAdd->setOpacity(0);
    fangyuAdd->setOpacity(0);
    nuqiAdd->setOpacity(0);
    
    shengmingAdd->setScale(2.0);
    gongjiAdd->setScale(2.0);
    fangyuAdd->setScale(2.0);
    nuqiAdd->setScale(2.0);
    
	CCMenuItemSprite* shengmingAdd1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"));
	CCMenuItemSprite* gongjiAdd1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"));
	CCMenuItemSprite* fangyuAdd1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"));
	CCMenuItemSprite* nuqiAdd1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scxt_jh.png"), CCSprite::createWithSpriteFrameName("scxt_jh_down.png"));

	CCPoint _addPos = ccp(12, 20);
	float _addScale = 0.3f;
	_add_0 = CCSprite::createWithSpriteFrameName("help11.png");
	_add_0->setPosition(_addPos);
	shengmingAdd1->addChild(_add_0);

	_add_1 = CCSprite::createWithSpriteFrameName("help11.png");
	_add_1->setPosition(_addPos);
	gongjiAdd1->addChild(_add_1);

	_add_2 = CCSprite::createWithSpriteFrameName("help11.png");
	_add_2->setPosition(_addPos);
	fangyuAdd1->addChild(_add_2);

	_add_3 = CCSprite::createWithSpriteFrameName("help11.png");
	_add_3->setPosition(_addPos);
	nuqiAdd1->addChild(_add_3);

	_add_0->setVisible(false);
	_add_1->setVisible(false);
	_add_2->setVisible(false);
	_add_3->setVisible(false);

	{
		CCRepeatForever* upd = CCRepeatForever::create(
			CCSequence::create(
			CCMoveBy::create(0.5f, ccp(0, 20)),
			CCMoveBy::create(0.5f, ccp(0, -20))
			, NULL));
		_add_0->runAction(upd);
	}
	{
		CCRepeatForever* upd = CCRepeatForever::create(
			CCSequence::create(
			CCMoveBy::create(0.5f, ccp(0, 20)),
			CCMoveBy::create(0.5f, ccp(0, -20))
			, NULL));
		_add_1->runAction(upd);
	}

	{
		CCRepeatForever* upd = CCRepeatForever::create(
			CCSequence::create(
			CCMoveBy::create(0.5f, ccp(0, 20)),
			CCMoveBy::create(0.5f, ccp(0, -20))
			, NULL));
		_add_2->runAction(upd);
	}

	{
		CCRepeatForever* upd = CCRepeatForever::create(
			CCSequence::create(
			CCMoveBy::create(0.5f, ccp(0, 20)),
			CCMoveBy::create(0.5f, ccp(0, -20))
			, NULL));
		_add_3->runAction(upd);
	}


	{
		
		_add_0->setScale(_addScale);
		_add_1->setScale(_addScale);
		_add_2->setScale(_addScale);
		_add_3->setScale(_addScale);

		_add_0->setRotation(-180);
		_add_1->setRotation(-180);
		_add_2->setRotation(-180);
		_add_3->setRotation(-180);

	}



    xuetongAdd = CCArray::create();
    xuetongAdd->retain();
    xuetongAdd->addObject(shengmingAdd);
    xuetongAdd->addObject(gongjiAdd);
    xuetongAdd->addObject(fangyuAdd);
    xuetongAdd->addObject(nuqiAdd);
    menuXuetong->addChild(shengmingAdd);
    menuXuetong->addChild(gongjiAdd);
    menuXuetong->addChild(fangyuAdd);
    menuXuetong->addChild(nuqiAdd);
    shengmingAdd->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.685));
    gongjiAdd->setPosition(ccp(SIZE.width*0.78,SIZE.height*0.565));
    fangyuAdd->setPosition(ccp(SIZE.width*0.75,SIZE.height*0.445));
    nuqiAdd->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.325));
    
    menuXuetong->addChild(shengmingAdd1);
    menuXuetong->addChild(gongjiAdd1);
    menuXuetong->addChild(fangyuAdd1);
    menuXuetong->addChild(nuqiAdd1);
    shengmingAdd1->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.685));
    gongjiAdd1->setPosition(ccp(SIZE.width*0.78,SIZE.height*0.565));
    fangyuAdd1->setPosition(ccp(SIZE.width*0.75,SIZE.height*0.445));
    nuqiAdd1->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.325));
    
    CCSprite* shengmingMoney = CCSprite::createWithSpriteFrameName("scxt_jbk.png");
    CCSprite* gongjiMoney = CCSprite::createWithSpriteFrameName("scxt_jbk.png");
    CCSprite* fangyuMoney = CCSprite::createWithSpriteFrameName("scxt_jbk.png");
    CCSprite* nuqiMoney = CCSprite::createWithSpriteFrameName("scxt_jbk.png");
    xuetogNode->addChild(shengmingMoney);
    xuetogNode->addChild(gongjiMoney);
    xuetogNode->addChild(fangyuMoney);
    xuetogNode->addChild(nuqiMoney);
    shengmingMoney->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.685));
    gongjiMoney->setPosition(ccp(SIZE.width*0.86, SIZE.height*0.565));
    fangyuMoney->setPosition(ccp(SIZE.width*0.84, SIZE.height*0.445));
    nuqiMoney->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.325));
	/*
    shengminglabel->setText("生命");
    gongjitiaolabel->setText("攻击");
    fangyutiaolabel->setText("防御");
    nuqitiaolabel->setText("怒气");
    */
    shengminglabel->setText(I18N_STR(153));
    gongjitiaolabel->setText(I18N_STR(154));
    fangyutiaolabel->setText(I18N_STR(155));
    nuqitiaolabel->setText(I18N_STR(156));
    shengmingMoneylabel = UILabel::create();
    gongjitiaoMoneylabel = UILabel::create();
    fangyutiaoMoneylabel = UILabel::create();
    nuqitiaoMoneylabel = UILabel::create();
    CCArray* labelarrMoney = CCArray::create();
    labelarrMoney->addObject(shengmingMoneylabel);
    labelarrMoney->addObject(gongjitiaoMoneylabel);
    labelarrMoney->addObject(fangyutiaoMoneylabel);
    labelarrMoney->addObject(nuqitiaoMoneylabel);
    CCObject* objectMoney;
    CCARRAY_FOREACH(labelarrMoney, objectMoney)
    {
        UILabel* label = dynamic_cast<UILabel*>(objectMoney);
        label->setColor(ccc3(0xff, 0xae, 0x00));
        label->setFontSize(16);
        label->setFontName("CarterOne");
		label->setPosition(ccp(30, 10));
    }

	int price_life = 1000;
	int price_attack = 2000;
	int price_fangyu = 1000;
	int price_nuqi = 2500;

	char moneyChar2[10] = { 0 };
	sprintf(moneyChar2, "- %d", price_life*(1 + KingData->getShengmingLevel()));
	shengmingMoneylabel->setText(moneyChar2);
	if (KingData->getShengmingLevel() >= 10)
	{
		//shengmingMoneylabel->setText("已经最高等级");
		shengmingMoneylabel->setText(I18N_STR(157));

	}
	sprintf(moneyChar2, "- %d", 200 + price_attack*(KingData->getGongjiLevel() - 1));
	gongjitiaoMoneylabel->setText(moneyChar2);
	if (KingData->getGongjiLevel() >= 10)
	{
		//gongjitiaoMoneylabel->setText("已经最高等级");
		gongjitiaoMoneylabel->setText(I18N_STR(157));

	}
	sprintf(moneyChar2, "- %d", price_fangyu*(1 + KingData->getFangyuLevel()));
	fangyutiaoMoneylabel->setText(moneyChar2);

	if (KingData->getFangyuLevel() >= 10)
	{
		//fangyutiaoMoneylabel->setText("已经最高等级");
		fangyutiaoMoneylabel->setText(I18N_STR(157));

	}
	sprintf(moneyChar2, "- %d", price_nuqi*(KingData->getNuqiLevel() + 1 - 2));
	nuqitiaoMoneylabel->setText(moneyChar2);
	if (KingData->getNuqiLevel() >= 10)
	{
		//nuqitiaoMoneylabel->setText("已经最高等级");
		nuqitiaoMoneylabel->setText(I18N_STR(157));

	}

    shengmingMoney->addChild(shengmingMoneylabel);
    gongjiMoney->addChild(gongjitiaoMoneylabel);
    fangyuMoney->addChild(fangyutiaoMoneylabel);
    nuqiMoney->addChild(nuqitiaoMoneylabel);
    
    /*****    商城           *****/
    shangchengNode = CCNode::create();
    this->addChild(shangchengNode);
    shangchengNode->setPosition(ccp(0, 0));
    CCScale9Sprite* shangchengbg1 = CCScale9Sprite::createWithSpriteFrameName("scnl_dk2.png");
    shangchengNode->addChild(shangchengbg1);
    shangchengbg1->setPosition(ccp(SIZE.width*0.37, SIZE.height/2));
    shangchengbg1->setContentSize(CCSize(SIZE.width*0.38,SIZE.height*0.64));
    CCScale9Sprite* shangchengbg2 = CCScale9Sprite::createWithSpriteFrameName("scnl_dk2.png");
    shangchengNode->addChild(shangchengbg2);
    shangchengbg2->setPosition(ccp(SIZE.width*0.715, SIZE.height/2));
    shangchengbg2->setContentSize(CCSize(SIZE.width*0.30,SIZE.height*0.64));
	CCMenuItemSprite* yuanbao1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scsc_tb1.png"), CCSprite::createWithSpriteFrameName("scsc_tb1.png"), this, menu_selector(ShopBuy::shopCallback));
	CCMenuItemSprite* yuanbao2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scsc_tb2.png"), CCSprite::createWithSpriteFrameName("scsc_tb2.png"), this, menu_selector(ShopBuy::shopCallback));
	CCMenuItemSprite* yuanbao3 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scsc_tb3.png"), CCSprite::createWithSpriteFrameName("scsc_tb3.png"), this, menu_selector(ShopBuy::shopCallback));
	CCMenuItemSprite* yuanbao4 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scsc_tb4.png"), CCSprite::createWithSpriteFrameName("scsc_tb4.png"), this, menu_selector(ShopBuy::shopCallback));
	CCMenuItemSprite* yuanbao5 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scsc_cjdlb1.png"), CCSprite::createWithSpriteFrameName("scsc_cjdlb1.png"), this, menu_selector(ShopBuy::shopCallback));
    shopArr = CCArray::create();
    shopArr->retain();
    shopArr->addObject(yuanbao1);
    shopArr->addObject(yuanbao2);
    shopArr->addObject(yuanbao3);
    shopArr->addObject(yuanbao4);
    shopArr->addObject(yuanbao5);
    CCMenu* menuShop = CCMenu::create();
    menuShop->setPosition(ccp(0, 0));
    shangchengNode->addChild(menuShop);
    menuShop->addChild(yuanbao1);
    menuShop->addChild(yuanbao2);
    menuShop->addChild(yuanbao3);
    menuShop->addChild(yuanbao4);
    menuShop->addChild(yuanbao5);
    yuanbao1->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.70));
    yuanbao2->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.70));
    yuanbao3->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.50));
    yuanbao4->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.50));
    yuanbao5->setPosition(ccp(SIZE.width*0.37,SIZE.height*0.30));
	CCMenuItemSprite* huode2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_hd.png"), CCSprite::createWithSpriteFrameName("scnl_hd_down.png"), this, menu_selector(ShopBuy::huodeShop));
    menuShop->addChild(huode2);
    huode2->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.28));
    xuanzhongkuang2 = CCSprite::createWithSpriteFrameName("scnl_xzk.png");
    xuanzhongkuang2->setScale(0.75);
    xuanzhongkuang2->runAction(CCRepeatForever::create(CCSequence::create( CCScaleBy::create(0.2, 1.1),CCScaleBy::create(0.2, 1/1.1) ,NULL ) ));
    shangchengNode->addChild(xuanzhongkuang2,1000);
    xuanzhongkuang2->setPosition(yuanbao1->getPosition());
    xuanzhongkuang3 = CCSprite::createWithSpriteFrameName("scnl_xzk.png");
    xuanzhongkuang3->setScaleX(2.0);
    xuanzhongkuang3->setScaleY(0.75);
    xuanzhongkuang3->runAction(CCRepeatForever::create(CCSequence::create( CCScaleBy::create(0.2, 1.1),CCScaleBy::create(0.2, 1/1.1) ,NULL ) ));
    shangchengNode->addChild(xuanzhongkuang3,1000);
    xuanzhongkuang3->setPosition(yuanbao5->getPosition());
    xuanzhongkuang3->setVisible(false);
    CCSprite* shopdescSprite = CCSprite::createWithSpriteFrameName("scnl_dk3.png");
        shopdescSprite->setScale(0.85);
    shangchengNode->addChild(shopdescSprite);
    shopdescSprite->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.60));
    CCSize descSize2 = shopdescSprite->getContentSize();
	//字体换行
    shopDescTitle = UILabel::create();
    shopDescTitle->setColor(ccc3(0xe3, 0x9e, 0x78));
    shopDescTitle->setFontSize(22);
    shopDescTitle->setFontName("CarterOne");
    shopDescTitle->setPosition(ccp(descSize.width/2, descSize.height-20));
    //shopDescTitle->setText(shopdescTitle[0]);
	shopDescTitle->setText(I18N_STR(94));
    shopdescSprite->addChild(shopDescTitle);
    shopDesc = UILabel::create();
	//字体换行
    shopDesc->setColor(ccc3(0xff, 0xae, 0x00));
    shopDesc->setFontSize(16);
    shopDesc->setFontName("CarterOne");
    shopDesc->setPosition(ccp(descSize.width/2, descSize.height-44));
    //shopDesc->setText(shopdescText[0]);
	shopDesc->ignoreContentAdaptWithSize(false);
	shopDesc->setSize(CCSizeMake(250, 100));
	shopDesc->setText(I18N_STR(99));
    shopdescSprite->addChild(shopDesc);
    shopDesc->setTextAreaSize(CCSize(descSize.width-20,descSize.height-40));
    shopDesc->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
    shopDesc->setAnchorPoint(ccp(0.5,1));
    



    if (currToshoW == 10) {
        nengliNode->setVisible(false);
        xuetogNode->setVisible(true);
        shangchengNode->setVisible(false);
        sprite = CCSprite::createWithSpriteFrameName("help11.png");
        sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f, ccp(0, 50)),CCMoveBy::create(0.2f, ccp(0, -50)),NULL)));
        xuetogNode->addChild(sprite,1,9898);
        sprite->setPosition(ccp(SIZE.width*0.7, SIZE.height*0.6));
		tishi_sprite->setVisible(true);
		tishi_sprite->setPosition(sprite->getPosition());
		tishi_sprite->setPositionY(tishi_sprite->getPositionY() - 46);

    }else if (currToshoW == 100)
    {
        nengliNode->setVisible(false);
        xuetogNode->setVisible(true);
        shangchengNode->setVisible(false);
    }
	/*else if (currToshoW == 666)
	{
		nengliNode->setVisible(false);
		xuetogNode->setVisible(true);
		shangchengNode->setVisible(false);
	}
	*/else
    {
		nengliNode->setVisible(true);
		xuetogNode->setVisible(false);
		shangchengNode->setVisible(false);
    }

    
	CCMenuItemSprite* xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_gb.png"), CCSprite::createWithSpriteFrameName("scnl_gb_down.png"), this, menu_selector(ShopBuy::resume));
    menu->addChild(xiaocha);
    
	xiaocha->setPosition(ccp(SIZE.width*0.915,SIZE.height*0.845));
}

void ShopBuy::showXutong()
{
	currToshoW = 0;
	nengliNode->setVisible(false);
	xuetogNode->setVisible(true);
	shangchengNode->setVisible(false);
}


void ShopBuy::addCallback(CCObject* pSender)
{
	/*int price_life = 200;
	int price_attack = 400;
	int price_fangyu = 200;
	int price_nuqi = 500;*/

	int price_life = 1000;
	int price_attack = 2000;
	int price_fangyu = 1000;
	int price_nuqi = 2500;

    if (currToshoW == 21)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    int order = xuetongAdd->indexOfObject(pSender);
    int money = KingData->getMoney();
    if(order==0)
    {
        if (currToshoW == 10)
        {
            return;
        }
        if (currToshoW == 20)
        {
            return;
        }
        int level = KingData->getShengmingLevel();
        if (level>=10)
        {
			//计费点
			showInfo(27);
		}
		else if (money < price_life*(level + 1))
        {
			//关闭跳转到金币界面
            //qiehuanCallback(2);   ///////////////
			//计费点
			m_useSkill = 1;
            showInfo(27);
        }else
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

			std::string _strs = "";
			JniMethodInfo methodInfo;
			bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
			if (ishave)
			{
				jint TypeInt = 16;//升级
				jint proInt = 0;
				jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
				methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
			}
#endif

			KingData->alterMoney(-price_life*(level + 1));
            KingData->alterShengMingLevel();

			CCSprite* shengmingdou = CCSprite::createWithSpriteFrameName("scxt_bs1.png");
			shengmingbash->addChild(shengmingdou);
			shengmingdou->setPosition(ccp(1 * (KingData->getShengmingLevel()) * 15 + 7.5, 8.5));
        }
    }
    else if (order == 1)
    {
		if (currToshoW == 20 && KingData->getGongjiLevel() <= 1)
        {
            

            resetTip();
            sprite->setRotation(180);
            sprite->setPosition(ccp(SIZE.width*0.92, SIZE.height*0.78));
			tishi_sprite->setVisible(true);
			tishi_sprite->setPosition(ccp(SIZE.width*0.92, SIZE.height*0.84));
            currToshoW = 21;
            xuetogNode->removeChildByTag(9898, true);
            KingData->alterGongJiLevel();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

			std::string _strs = "";
			JniMethodInfo methodInfo;
			bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
			if (ishave)
			{
				jint TypeInt = 16;//升级
				jint proInt = 1;
				jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
				methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
			}
#endif
			CCSprite* gongjidou = CCSprite::createWithSpriteFrameName("scxt_bs2.png");
			gongjibash->addChild(gongjidou);
			gongjidou->setPosition(ccp(1 * (KingData->getGongjiLevel()) * 15 + 7.5, 8.5));
            
        }else
        {
			if (currToshoW == 20)
			{
				resetTip();
				sprite->setRotation(180);
				sprite->setPosition(ccp(SIZE.width*0.92, SIZE.height*0.78));

				tishi_sprite->setPosition(ccp(SIZE.width*0.92, SIZE.height*0.84));
				tishi_sprite->setVisible(false);
				sprite->setVisible(false);
				currToshoW = 0;
				xuetogNode->removeChildByTag(9898, true);
			}

            int level = KingData->getGongjiLevel();
            if (level>=10)
            {
				//计费点
				showInfo(27);
                
			}
			else if (money < 200 + price_attack*(level - 1))
            {
                //qiehuanCallback(2);   ///////////////
				//计费点
				m_useSkill = 2;
				showInfo(27);
                
            }else
            {
				KingData->alterMoney(-(200+ price_attack*(level-1)));
                KingData->alterGongJiLevel();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

				std::string _strs = "";
				JniMethodInfo methodInfo;
				bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
				if (ishave)
				{
					jint TypeInt = 16;//升级
					jint proInt = 1;
					jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
					methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
				}
#endif
				CCSprite* gongjidou = CCSprite::createWithSpriteFrameName("scxt_bs2.png");
				gongjibash->addChild(gongjidou);
				gongjidou->setPosition(ccp(1 * (KingData->getGongjiLevel()) * 15 + 7.5, 8.5));
            }
        }
    }
    else if (order == 2)
    {
        if (currToshoW == 10)
        {
            return;
        }
        if (currToshoW == 20)
        {
            return;
        }
        
        int level = KingData->getFangyuLevel();
        if (level>=10)
        {
			//计费点
			showInfo(27);
		}
		else if (money < price_fangyu*(level + 1))
        {
             //qiehuanCallback(2);   ///////////////
			 //计费点
			m_useSkill = 3;
			 showInfo(27);
            
        }else
        {
			KingData->alterMoney(-price_fangyu*(level+1));
            KingData->alterFangyuLevel();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

			std::string _strs = "";
			JniMethodInfo methodInfo;
			bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
			if (ishave)
			{
				jint TypeInt = 16;//升级
				jint proInt = 2;
				jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
				methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
			}
#endif
			CCSprite* fangyudou = CCSprite::createWithSpriteFrameName("scxt_bs3.png");
			fangyubash->addChild(fangyudou);
			fangyudou->setPosition(ccp(1 * (KingData->getFangyuLevel()) * 15 + 7.5, 8.5));
        }
    }
    else if (order == 3)
    {
        if (currToshoW == 10)
        {
            return;
        }
        if (currToshoW == 20)
        {
            return;
        }
        
        int level = KingData->getNuqiLevel();
        if (level<2) {
            return;
        }
        if (level>=10) {
			//计费点

			showInfo(27);
           
		}
		else if (money < price_nuqi*(level - 1))
        {
			//计费点
			m_useSkill = 4;
			showInfo(27);
            //qiehuanCallback(2);   ///////////////
        }else
        {
			KingData->alterMoney(-price_nuqi*(level-1));
            KingData->alterNuqiLevel();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

			std::string _strs = "";
			JniMethodInfo methodInfo;
			bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
			if (ishave)
			{
				jint TypeInt = 16;//升级
				jint proInt = 3;
				jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
				methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
			}
#endif
			CCSprite* nuqidou = CCSprite::createWithSpriteFrameName("scxt_bs4.png");
			nuqibash->addChild(nuqidou);
			nuqidou->setPosition(ccp(1 * (KingData->getNuqiLevel()) * 15 + 7.5, 8.5));
        }
    }

    char moneyChar2[10] = {0};
	sprintf(moneyChar2, "- %d", price_life*(1 + KingData->getShengmingLevel()));
    shengmingMoneylabel->setText(moneyChar2);
    if(KingData->getShengmingLevel()>=10)
    {
        //shengmingMoneylabel->setText("已经最高等级");
		shengmingMoneylabel->setText(I18N_STR(157));
		
    }
	sprintf(moneyChar2, "- %d", 200 + price_attack*(KingData->getGongjiLevel() - 1));
    gongjitiaoMoneylabel->setText(moneyChar2);
    if(KingData->getGongjiLevel()>=10)
    {
        //gongjitiaoMoneylabel->setText("已经最高等级");
		gongjitiaoMoneylabel->setText(I18N_STR(157));
		
    }
	sprintf(moneyChar2, "- %d", price_fangyu*(1 + KingData->getFangyuLevel()));
    fangyutiaoMoneylabel->setText(moneyChar2);
    
    if(KingData->getFangyuLevel()>=10)
    {
        //fangyutiaoMoneylabel->setText("已经最高等级");
		fangyutiaoMoneylabel->setText(I18N_STR(157));
		
    }
	sprintf(moneyChar2, "- %d", price_nuqi*(KingData->getNuqiLevel() + 1 - 2));
    nuqitiaoMoneylabel->setText(moneyChar2);
    if(KingData->getNuqiLevel()>=10)
    {
        //nuqitiaoMoneylabel->setText("已经最高等级");
		nuqitiaoMoneylabel->setText(I18N_STR(157));
		
    }
}

void ShopBuy::showInfo(int id)
{
	CCLOG("ShopBuy::showInfo");
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
void  Java_com_vemobi_fight_fight_backAction(JNIEnv *env, jobject thiz,jint aaaa)
{
	CCLOG("Java_com_vemobi_fight_fight_backAction");
    if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(10001))
    {
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(10001);
    }
	
    if (HUB!=NULL)
    {
        HUB->setVisible(true);
        gameLayer->setVisible(true);
    }
    
    int aaa = (int)aaaa;
	
    if (aaa == 8)
    {
    	
       
        
        
        KingData->setBazhinv(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("bazhinv",true);
        
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
		
        if (HUB!=NULL)
        {
             HUB->runSkill(2);
        }
         /*if (CCDirector::sharedDirector()->isPaused()) {
			
            CCDirector::sharedDirector()->resume();
        }*/
        CCLog("Java_com_vemobi_fight_fight_backAction-bazhinv HUB=%d",HUB);
        
    }else if(aaa == 9)
    {
    	
    	

        
      	
        KingData->setBajiubei(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("bajiubei",true);
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
		
        if (HUB!=NULL)
        {
            HUB->runSkill(3);
        }
             /* if (CCDirector::sharedDirector()->isPaused()) {
            CCDirector::sharedDirector()->resume();
        }*/
         CCLog("Java_com_vemobi_fight_fight_backAction-bajiubei HUB=%d",HUB);
    }
	else if(aaa == 23)
    {
        KingData->setJinjiDuobi(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("jinjiduobi",true);
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
        if (HUB!=NULL)
        {
            HUB->runSkill(4);
        }
        /*if (CCDirector::sharedDirector()->isPaused()) {
            CCDirector::sharedDirector()->resume();
        }*/
         CCLog("Java_com_vemobi_fight_fight_backAction-jinjiduobi HUB=%d",HUB);
    }else if(aaa == 24)
    {
        KingData->setShoushen(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("shoushen",true);
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();

		if (HUB!=NULL)
		{
			HUB->runSkill(1);
		}

        /*if (Role!=NULL)
        {
           Role->fuhuo();
        }*/
       
    }
    else if(aaa == 25)
    {
        KingData->alterMoney(1888);
    }
    else if(aaa == 26)
    {
        KingData->alterMoney(5888);
    }
    else if(aaa == 27)
    {
        KingData->alterMoney(18888);
        
    } else if(aaa == 16)
    {
        KingData->alterMoney(8888);
        KingData->setExtraNuqi(KingData->getExtraNuqi()+1800);//5000

		//SHOP->showNuqi(18);

        /*KingData->setJinjiDuobi(true);
        KingData->setShoushen(true);
        KingData->setFuhuo(true);
        if (Role!=NULL)
        {
            Role->fuhuo();
        }
        if (HUB!=NULL)
        {
            CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill4TimerTag));
            timer1->setPercentage(100);
            HUB->runSkill(4);
        }*/
        
    }
    else if(aaa == 10)
    {
        if (Role != NULL)
        {
                if (Role->isDie)
                {
                     Game::instance()->getShopLayer()->ispop = true;
                }else
                {
                     KingData->setFuhuo(true);
                }
        }else
        {
            KingData->setFuhuo(true);
        }
    }else if(aaa == 11)
    {

    }else if(aaa == 19)
    {
        if (Role != NULL)
        {
            //Game::instance()->getFourJihuo()->ispop = true;
       
        }
    }
    else if(aaa == 15)
    {
            KingData->setExtraNuqi(KingData->getExtraNuqi()+1500);//3500

			if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(55210) != NULL && SHOP != NULL)
			{
				SHOP->showNuqi(15);
			}

    }
    else if(aaa == 31)
    {
          KingData->alterMoney(16664);
    }
    else if(aaa == 32)
    {
        KingData->alterMoney(16664);
    }


    
}
}
#endif


void  ShopBuy::C_backAction(int aaaa)
{
	//return;

	CCLOG("Java_com_vemobi_fight_fight_backAction");
	if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(10001))
	{
		CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(10001);
	}

	if (HUB != NULL)
	{
		HUB->setVisible(true);
		gameLayer->setVisible(true);
	}

	int aaa = (int)aaaa;

	if (aaa == 8)
	{




		KingData->setBazhinv(true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("bazhinv", true);

		CCUserDefault::sharedUserDefault()->flush();
		CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();

		if (HUB != NULL)
		{
			HUB->runSkill(2);
		}
		/*if (CCDirector::sharedDirector()->isPaused()) {

			CCDirector::sharedDirector()->resume();
		}*/
		CCLog("Java_com_vemobi_fight_fight_backAction-bazhinv HUB=%d", HUB);

	}
	else if (aaa == 9)
	{





		KingData->setBajiubei(true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("bajiubei", true);
		CCUserDefault::sharedUserDefault()->flush();
		CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();

		if (HUB != NULL)
		{
			HUB->runSkill(3);
		}
		/*if (CCDirector::sharedDirector()->isPaused()) {
			CCDirector::sharedDirector()->resume();
		}*/
		CCLog("Java_com_vemobi_fight_fight_backAction-bajiubei HUB=%d", HUB);
	}
	else if (aaa == 23)
	{
		KingData->setJinjiDuobi(true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("jinjiduobi", true);
		CCUserDefault::sharedUserDefault()->flush();
		CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
		if (HUB != NULL)
		{
			HUB->runSkill(4);
		}
		/*if (CCDirector::sharedDirector()->isPaused()) {
			CCDirector::sharedDirector()->resume();
		}*/
		CCLog("Java_com_vemobi_fight_fight_backAction-jinjiduobi HUB=%d", HUB);
	}
	else if (aaa == 24)
	{
		KingData->setShoushen(true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("shoushen", true);
		CCUserDefault::sharedUserDefault()->flush();
		CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();

		if (HUB != NULL)
		{
			HUB->runSkill(1);
		}

		/*if (Role != NULL)
		{
			Role->fuhuo();
		}*/

	}
	else if (aaa == 25)
	{
		KingData->alterMoney(1888);
	}
	else if (aaa == 26)
	{
		KingData->alterMoney(5888);
	}
	else if (aaa == 27)
	{
		KingData->alterMoney(18888);

	}
	else if (aaa == 16)
	{
		KingData->alterMoney(8888);
		KingData->setExtraNuqi(KingData->getExtraNuqi() + 1800);//5000

	}
	else if (aaa == 10)
	{
		if (Role != NULL)
		{
			if (Role->isDie)
			{
				Game::instance()->getShopLayer()->ispop = true;
			}
			else
			{
				KingData->setFuhuo(true);
			}
		}
		else
		{
			KingData->setFuhuo(true);
		}
	}
	else if (aaa == 11)
	{

	}
	else if (aaa == 19)
	{
		if (Role != NULL)
		{
			//Game::instance()->getFourJihuo()->ispop = true;

		}
	}
	else if (aaa == 15)
	{
		KingData->setExtraNuqi(KingData->getExtraNuqi() + 1500);//3500

		if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(55210) != NULL && SHOP != NULL)
		{
			SHOP->showNuqi(15);
		}
	}
	else if (aaa == 31)
	{
		KingData->alterMoney(16664);
	}
	else if (aaa == 32)
	{
		KingData->alterMoney(16664);
	}



}

void ShopBuy::resume(CCObject* pSender)
{
    if (currToshoW == 3)
    {
        return;
    }
    
    if (currToshoW == 10)
    {
        return;
    }
    if (currToshoW == 20)
    {
        return;
    }
    
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.mp3"/*.wav*/);
    
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing&& Role->isDie)
    {
        return;
    }
    if(Role!=NULL &&Role->isDie)
    {
        Role->abDie = true;
        CCDirector::sharedDirector()->popScene();
        return;
    }
    CCDirector::sharedDirector()->popScene();
}

void ShopBuy::nengliCallback(CCObject* pSender)
{
   
    if (currToshoW == 3)
    {
        return;
    }
    if (currToshoW == 20)
    {
        return;
    }
    if (currToshoW == 21)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing)
    {
        return;
    }
    CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(pSender);
    nengliSort = nengliArr->indexOfObject(m_item);
    xuanzhongkuang->setPosition(m_item->getPosition());
    //nengliDesc->setText( nenglidescText[nengliSort]);
	nengliDesc->setText(I18N_STR(nengliSort+89));
    //nengliDescTitle->setText( nenglidescTitle[nengliSort]);
	nengliDescTitle->setText( I18N_STR(nengliSort + 85));
}


void ShopBuy::qiehuanCallback(int index)
{
	CCObject* p = menus->objectAtIndex(index);
    qiehuanCallback(p);
}

void ShopBuy::qiehuanCallback(CCObject* pSender)
{
   
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing)
    {
        return;
    }
    if (currToshoW == 3)
    {
        return;
    }
    
    if (currToshoW == 10)
    {
        return;
    }
    if (currToshoW == 21)
    {
        return;
    }
    CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(pSender);
    int sort = menus->indexOfObject(m_item);
    
    if (currToshoW == 20 && sort!=1)
    {
        return;
    }
   
    CCObject* obj;
    CCARRAY_FOREACH(menus, obj)
    {
        CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(obj);
        m_item->setEnabled(true);
        m_item->setZOrder(1000-menus->indexOfObject(obj));
    }

    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    m_item->setEnabled(false);
    m_item->setZOrder(1001);
    if(sort == 0)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		std::string _strs = "";
		JniMethodInfo methodInfo;
		bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
		if (ishave)
		{
			jint TypeInt = 4;//弹窗-----------商店技能 12 升级 13 金币 14
			jint proInt = 12;
			jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
		}
#endif


        nengliNode->setVisible(true);
        xuetogNode->setVisible(false);
        shangchengNode->setVisible(false);

    }else if (sort == 1)
    {
        
        if (currToshoW == 20)
        {
            //addTip("点击加号增强属性。本次免费");
			addTip(I18N_STR(152));
            sprite->setPosition(ccp(SIZE.width*0.78, SIZE.height*0.65));
            sprite->setScale(0.4f);
			tishi_sprite->setVisible(true);
			tishi_sprite->setPosition(ccp(SIZE.width*0.78, SIZE.height*0.58));
        }
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		std::string _strs = "";
		JniMethodInfo methodInfo;
		bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
		if (ishave)
		{
			jint TypeInt = 4;//弹窗-----------商店技能 12 升级 13 金币 14
			jint proInt = 13;
			jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
		}
#endif
        nengliNode->setVisible(false);
        xuetogNode->setVisible(true);
        shangchengNode->setVisible(false);

    }else if (sort == 2)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		std::string _strs = "";
		JniMethodInfo methodInfo;
		bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
		if (ishave)
		{
			jint TypeInt = 4;//弹窗-----------商店技能 12 升级 13 金币 14
			jint proInt = 14;
			jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
		}
#endif
        nengliNode->setVisible(false);
        xuetogNode->setVisible(false);
        shangchengNode->setVisible(true);
    }
}

void ShopBuy::shopCallback(CCObject* pSender)
{
    if (currToshoW == 21)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(pSender);
    shopSort =  shopArr->indexOfObject(m_item);
    if(shopSort == 4)
    {
        xuanzhongkuang3->setVisible(true);
        xuanzhongkuang2->setVisible(false);
    }else
    {
        xuanzhongkuang2->setPosition(m_item->getPosition());
        xuanzhongkuang3->setVisible(false);
        xuanzhongkuang2->setVisible(true);
    }
    //shopDescTitle->setText(shopdescTitle[shopSort]);
	shopDescTitle->setText(I18N_STR(shopSort+94));
    //shopDesc->setText(shopdescText[shopSort]);
    shopDesc->setText(I18N_STR(shopSort+99));
}

void ShopBuy::huodenengli(CCObject* pSender)
{
    if (currToshoW == 20)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing)
    {
        Role->fuhuo();
        gameLayer->juqingThreeEnd();
        CCDirector::sharedDirector()->popScene();
        return;
    }

    if (currToshoW == 3)
    {
     //   labelnuqi->setVisible(false);
       
        resetTip();
        //KingData->setExtraNuqi(KingData->getExtraNuqi()+1000);
        sprite->setRotation(180);
        sprite->setScale(0.5);
        sprite->setPosition(ccp(SIZE.width*0.92, SIZE.height*0.78));
		tishi_sprite->setVisible(true);
		tishi_sprite->setPosition(sprite->getPosition());
		tishi_sprite->setPositionY(tishi_sprite->getPositionY() +46);

		if (KingData->getMoney() >= 10000)
		{
			KingData->setMoney(KingData->getMoney() - 10000);
			KingData->setExtraNuqi(KingData->getExtraNuqi() + 1000);
			//计费点
			SHOP->showNuqi(10);
			showInfo(11);
		}
		else
		{
			//关闭跳转到金币界面
			//qiehuanCallback(2);   ///////////////
			//计费点
			showInfo(15);
		}


        currToshoW = 21;//21
    }

    if (currToshoW == 21)
    {
        return;
    }

    switch (nengliSort) {
        case 0:
        {
            bool isGet = KingData->getBazhinv();
            if (isGet)
            {
                
            }else
            {
				//计费点
                showInfo(8);
            }
            break;
        }
        case 1:
        {
            bool isGet = KingData->getBajiubei();
            if (isGet)
            {
                
            }else
            {
				//计费点
                showInfo(9);
            }
            break;
        }
        case 2:
        {
            bool isGet = KingData->getFuhuo();
            if (isGet)
            {
				//计费点
                showInfo(17);
               
            }else
            {
				//计费点
                showInfo(10);
            }
            break;
        }
        case 3:
        {
            if (KingData->getMoney()>=10000)
            {
                KingData->setMoney(KingData->getMoney()-10000);
				KingData->setExtraNuqi(KingData->getExtraNuqi() + 1000);

				SHOP->showNuqi(10);

				//计费点
                showInfo(11);
            }else
            {
				//关闭跳转到金币界面
                //qiehuanCallback(2);   ///////////////
				//计费点
                showInfo(15);
            }
            break;
        }
        default:
            break;
    }
}

void ShopBuy::showNuqi(int num)
{
	nuqi_num = num;
	CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(ShopBuy::showNuqi));
	this->runAction(call);
}

void ShopBuy::showNuqi(CCNode* pSender)
{
	{
		CCSprite* _nuqi = CCSprite::create("nuqi_pic.png");
		CCSprite* _add = CCSprite::create("add_hao.png");
		this->addChild(_nuqi, 9999999);
		_nuqi->setPosition(ccp(400, 240));
		_nuqi->addChild(_add);
		_add->setPosition(ccp(80, 35));

		CCSprite* _zero;
		if (nuqi_num == 10)
		{
			_zero = CCSprite::createWithSpriteFrameName("qtsz_0.png");
		}
		else if (nuqi_num == 15)
		{
			_zero = CCSprite::createWithSpriteFrameName("qtsz_5.png");
		}
		else if (nuqi_num == 18)
		{
			_zero = CCSprite::createWithSpriteFrameName("qtsz_8.png");
		}


		CCSprite* _ten = CCSprite::createWithSpriteFrameName("qtsz_1.png");


		_nuqi->addChild(_ten);
		_nuqi->addChild(_zero);
		_ten->setPosition(ccp(100, 35));
		_zero->setPosition(ccp(120, 35));
		CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(ShopBuy::DeleteSelf));
		_nuqi->runAction(
			CCSequence::create(
			CCSpawn::create(CCMoveBy::create(0.6f, ccp(0, 100)), NULL)
			, call
			, NULL));
	}
}


void ShopBuy::DeleteSelf(CCNode* pSender)
{
	pSender->removeFromParent();
}

void ShopBuy::huodeShop(CCObject* pSender)
{
    if (currToshoW == 21)
    {
        return;
    }
    if (currToshoW == 20)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    switch (shopSort) {
        case 0:
        {
				  //计费点
            showInfo(25);
            break;
        }
        case 1:
        {
				  //计费点
            showInfo(26);
            break;
        }
        case 2:
        {
				  //计费点
            showInfo(27);
            break;
        }
        case 3:
        {
				  //计费点
            showInfo(15);

            break;
        }
        case 4:
        {
				  //计费点
            showInfo(16);
            break;
        }
        default:
            break;
    }
}

CCScene* ShopBuy::scene(CCRenderTexture *sqr, bool isFlip )
{

    CCScene *scene = CCScene::create();
    ShopBuy* layer = ShopBuy::create();
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (sqr != NULL)
	{
		CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
		_spr->setPosition(ccp(size.width / 2, size.height / 2));
		_spr->setFlipY(true);  //是否翻转
		_spr->setColor(ccGRAY);  //颜色（变灰暗）
		scene->addChild(_spr);
	}

	if (isFlip)
	{
		layer->showXutong();
	}

    return scene;
}

CCScene* ShopBuy::scene()
{
    CCScene *scene = CCScene::create();
    ShopBuy* layer = ShopBuy::create();
    scene->addChild(layer,100);
   // CCSize size = CCDirector::sharedDirector()->getWinSize();
    return scene;
}

CCScene* ShopBuy::scene(CCRenderTexture *sqr, bool isFlip ,int currToshoW)
{
    CCScene *scene = CCScene::create();
    ShopBuy* layer = ShopBuy::create(currToshoW);
    scene->addChild(layer,100);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(ccp(size.width / 2, size.height / 2));
	_spr->setFlipY(true);  //是否翻转
	_spr->setColor(ccGRAY);  //颜色（变灰暗）
	scene->addChild(_spr);

    return scene;
}

ShopBuy* ShopBuy::create(int currToshoW)
{
    ShopBuy* shopBuy = new ShopBuy();
    shopBuy->autorelease();
    shopBuy->init(currToshoW);
    return shopBuy;
}

bool ShopBuy::init(int currToshoW)
{
    this->currToshoW = currToshoW;
    this->init();
    return true;
}

void ShopBuy::addGoumai(CCNode* n,CCPoint p)
{
    CCSprite* s = CCSprite::createWithSpriteFrameName("yihuode.png");
    n->addChild(s,1,1001);
    s->setPosition(p);
    s->setScale(0.5);
}

void ShopBuy::addTip(std::string text)
{
    jiaoshi->setFlipX(false);
    tip1->runAction(CCMoveTo::create(0.2f, ccp(210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.085, 2))
                                          ,NULL ));
    
    label->setPosition(ccp(220, tip1->getContentSize().height));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    label->setText(text);

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}

void ShopBuy::addTip2(std::string text)
{
    jiaoshi->setVisible(false);
    tip1->setVisible(false);
    jiaoshi->setPosition(ccp(1.15*SIZE.width,10));
    tip1->setPosition(ccp( SIZE.width+150, -120));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    jiaoshi->setFlipX(true);
    label->setPosition(ccp(100, tip1->getContentSize().height));
    tip1->runAction(CCMoveTo::create(0.2f, ccp(SIZE.width-210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width-SIZE.width*0.085, 2))
                                          ,NULL ));
    
    label->setText(text);

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}



void ShopBuy::resetTip()
{
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setText("");
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    tip1->setPosition(ccp( -150, -120));

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}




