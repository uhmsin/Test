//
//  TipStory2.cpp
//  ooo
//
//  Created by mac on 14-6-4.
//
//

#include "TipStory2.h"
#include "GameData.h"

CCScene* TipStory2::scene()
{
    CCScene* scene = CCScene::create();
    TipStory2* tipsLayer = TipStory2::create();
    scene->addChild(tipsLayer);
    return scene;
}

TipStory2* TipStory2::create()
{
    TipStory2* layer = new TipStory2();
    layer->init();
    layer->autorelease();
    return layer;
}

bool TipStory2::init()
{
    currentduihua_index = 0;
    nvRoleHead = CCSprite::create("duihuakuang/xiaowu.png");
    this->addChild(nvRoleHead,100);
    nvRoleHead->setPosition(ccp(-0.2*SIZE.width,10));
    nvRoleHead->setAnchorPoint(ccp(1, 0));
    nvRoleHead->setVisible(false);
    
    roleHead = CCSprite::create("duihuakuang/fengkbasheng.png");
    this->addChild(roleHead,100);
    roleHead->setPosition(ccp(-0.2*SIZE.width,10));
    roleHead->setAnchorPoint(ccp(1, 0));
    roleHead->setVisible(false);
    
    blackRoleHead =  CCSprite::create("duihuakuang/heisebasheng.png");
    this->addChild(blackRoleHead,100);
    blackRoleHead->setPosition(ccp(1.2*SIZE.width,10));
    blackRoleHead->setAnchorPoint(ccp(0, 0));
    blackRoleHead->setVisible(false);
    
    addTips();
    
    bg = CCSprite::create("maps/map01.jpg");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    bg2 = CCLayerColor::create(ccc4(94, 11, 7, 255*0.8),1500,480);
    this->addChild(bg2,-1);
    bg2->setPosition(-500, 0);
    
    
    this->initHero();
    return true;
}

void TipStory2::initHero()
{
    hero = Hero::create();
    this->addChild(hero,10);
    hero->setPosition(SIZE.width/2, SIZE.height/4 + hero->bottomH);
    hero->stand();
    hero->shadow2 = CCSprite::createWithSpriteFrameName("yingzi.png");
    this->addChild(hero->shadow2);

    
    hero2 = Hero::create();
    this->addChild(hero2,10);
    hero2->setPosition(SIZE.width*1.06, SIZE.height/4 + hero->bottomH);
    hero2->setVisible(false);
    hero2->s->setColor(ccc3(0,100,100));
    hero2->s->getAnimation()->playWithIndex(0);
    hero2->s->setScaleX(-1.0f);
    hero2->setScale(1.2);
    
    monster = Monster::create(12, 0);
    monster->unscheduleAllSelectors();
    monster->s->getAnimation()->playWithIndex(4);
    this->addChild(monster);
    monster->setPosition(ccpAdd(hero->getPosition(), ccp(150, 0)) );
    monster->bloodbar->setVisible(false);
    monster->shadow->setPosition(monster->getPosition());
    
    hero->s->getAnimation()->playWithIndex(13);
    CCMoveBy* by = CCMoveBy::create(1.2,ccp(50.0f, 0.0f) );
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( TipStory2::crazy));
    CCSequence* seq = CCSequence::create(by,call,NULL);
    hero->runAction(seq);
}

void TipStory2::crazy()
{
    hero->s->getAnimation()->playWithIndex(18);
    hero->s->getAnimation()->setSpeedScale(0.8f);
    this->scheduleOnce(schedule_selector(TipStory2::initNvRole ), 0.6f);
    
}

void TipStory2::initNvRole(float dt)
{
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"nvzhujiao","nvzhujiao");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    nvRole = CCArmature::create("nvzhujiao");
    nvRole->setPosition(ccp(SIZE.width*(-0.1), SIZE.height/4));
    nvRole->getAnimation()->playWithIndex(1);
    this->addChild(nvRole);
    CCMoveBy* by = CCMoveBy::create(2,ccp(100.0f, 0.0f) );
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( TipStory2::fixFocus));
    CCSequence* seq = CCSequence::create(by,call,NULL);

    nvRole->runAction(seq);
}

void TipStory2::fixFocus()
{
    bg->setVisible(false);
    nvRole->getAnimation()->playWithIndex(0);
    hero->s->getAnimation()->setSpeedScale(0.6f);
    hero->s->getAnimation()->pause();
    screenMove();
}

void TipStory2::screenMove()
{
    CCPoint pp = CCPoint((hero->getPositionX() - nvRole->getPositionX())/2 ,0);
    float ppx = SIZE.width/2 - pp.x;
    CCMoveBy* by =    CCMoveBy::create(0.1f, ccp(ppx/2, 0) );
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( TipStory2::tip1));
    CCSequence* seq = CCSequence::create(by,call,NULL);
    this->runAction(seq);
}

void TipStory2::screenMove2()
{
    CCMoveTo* to = CCMoveTo::create(0.1f, ccp(-200, 0));
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory2::resetPosition2 ));
    CCSequence* seq = CCSequence::create(to,call,NULL );
    this->runAction(seq);
}

void TipStory2::resetPosition2()
{
    resetPosition();
}

void TipStory2::resetPosition()
{
    CCObject* obj;
    CCArray* arrs = this->getChildren();
    CCARRAY_FOREACH(arrs, obj)
    {
        CCNode* node =dynamic_cast<CCNode*>(obj);
        node->setPosition(ccp(node->getPositionX() + this->getPositionX(), node->getPositionY()));
    }
    this->setPosition(0, 0);
}

void TipStory2::tip1()
{
    resetPosition();
    addTip1();
    this->scheduleOnce(schedule_selector(TipStory2::qianqian  ) , 1.5f);
    this->scheduleOnce(schedule_selector(TipStory2::fadeAllErole  ) , 3.0f);
}

void TipStory2::tip2()
{
    currentduihua_index++;
    addTip1();
   // this->scheduleOnce(schedule_selector(TipStory2::qianqian  ) , 1.0f);
}

void TipStory2::fadeAllErole(float dt)
{
    hero->s->getAnimation()->playWithIndex( 12);
    resetTip1();
    CCObject* obj;
    CCArray* arrs = this->getChildren();
    CCARRAY_FOREACH(arrs, obj)
    {
        CCNode* node =dynamic_cast<CCNode*>(obj);
        if (node != hero && node != bg2)
        {
            node->runAction(CCFadeOut::create(1.0f));
        }
    }
    CCFadeOut* fade =  CCFadeOut::create(1.0f);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( TipStory2::tip3));
    CCSequence* seq = CCSequence::create(fade,call,NULL);
    monster->s->runAction(seq);
}

void TipStory2::tip3()
{
    currentduihua_index++;
    roleHead->setOpacity(255);
    tip11->setOpacity(255);
    addTip3();
    this->scheduleOnce(schedule_selector(TipStory2::tip4), 2.5f);
    this->scheduleOnce(schedule_selector(TipStory2::tip5), 5.0f);
    this->scheduleOnce(schedule_selector(TipStory2::duihua), 7.5f);
    this->scheduleOnce(schedule_selector(TipStory2::tip6), 10.0f);
    this->scheduleOnce(schedule_selector(TipStory2::tip7), 12.5f);
    this->scheduleOnce(schedule_selector(TipStory2::tip8), 15.0f);
    this->scheduleOnce(schedule_selector(TipStory2::GameStart), 17.5f);
}

void TipStory2::GameStart(float dt)
{
    CCScene* scene = GameScene::scene(100,5);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, scene)  );
}

void TipStory2::duihua(float dt)
{
    screenMove2();
    resetTip1();
    hero->s->getAnimation()->playWithIndex(0);
    hero->s->setScaleX(1.0f);
    hero2->setVisible(true);
}

TipStory2::~TipStory2()
{
    
}

void TipStory2::tip4(float dt)
{
    resetTip1();
    currentduihua_index++;
    addTip2();
}

void TipStory2::tip5(float dt)
{
    resetTip2();
    currentduihua_index++;
    addTip3();
}

void TipStory2::tip6(float dt)
{
    resetTip2();
    currentduihua_index++;
    addTip3();
}

void TipStory2::tip7(float dt)
{
    resetTip1();
    currentduihua_index++;
    addTip2();
}

void TipStory2::tip8(float dt)
{
    resetTip2();
    currentduihua_index++;
    addTip3();
}

void TipStory2::qianqian(float dt)
{
    resetTip1();
    hero->s->getAnimation()->setSpeedScale(1.0f);
    hero->s->setScaleX(-1.0f);
    hero->s->getAnimation()->playWithIndex(23,-1,-1,0);
    CCMoveBy* by =    CCMoveBy::create(0.1f, ccp(-250, 0) );
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( TipStory2::tip2));
    CCSequence* seq = CCSequence::create(by,call,NULL);
    hero->runAction(seq);
}


void TipStory2::addTip3()
{
    tip11->setVisible(true);
    roleHead->setVisible(true);
    tip11->runAction(CCMoveTo::create(0.2f, ccp(280,80)));
    roleHead->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.22, 10))
                                             ,CCCallFunc::create(this, callfunc_selector(TipStory2::setText1)),NULL ));
}

void TipStory2::addTip1()
{
    tip11->setVisible(true);
    nvRoleHead->setVisible(true);
    tip11->runAction(CCMoveTo::create(0.2f, ccp(280,80)));
    nvRoleHead->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.22, 10))
                                   ,CCCallFunc::create(this, callfunc_selector(TipStory2::setText1)),NULL ));
}


void TipStory2::resetTip1()
{
    roleHead->setVisible(false);
    roleHead->setPosition(ccp(-0.2*SIZE.width,10));
    nvRoleHead->setVisible(false);
    nvRoleHead->setPosition(ccp(-0.2*SIZE.width,10));
    tip11->setPosition(ccp( -150, -120));
    label->setVisible(false);
}

void TipStory2::resetTip2()
{
    blackRoleHead->setVisible(false);
    blackRoleHead->setPosition(ccp(1.2*SIZE.width,10));
    tip01->setPosition(ccp(SIZE.width+150,-120));
    label2->setVisible(false);
}

void TipStory2::addTip2()
{
    tip01->setVisible(true);
    blackRoleHead->setVisible(true);
    blackRoleHead->setOpacity(255);
    tip01->setOpacity(255);
    tip01->runAction(CCMoveTo::create(0.2f, ccp(SIZE.width-280,80)));
    blackRoleHead->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.70, 10))
                                                    ,CCCallFunc::create(this, callfunc_selector(TipStory2::setText2)),NULL ));
}

void TipStory2::setText1()
{
    canSay = true;
    //label->setText(wordsss[currentduihua_index]);
	label->setText(I18N_STR(currentduihua_index+104));
    label->setVisible(true);

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}

void TipStory2::setText2()
{
    canSay = true;
    //label2->setText(wordsss[currentduihua_index]);
	label->setText(I18N_STR(currentduihua_index+104));
    label2->setVisible(true);

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(200, 100));
}


void TipStory2::addTips()
{

    tip11 = CCSprite::create("duihuakuang/UI80.png");
    tip11->setPosition(ccp( -150, -120));
    this->addChild(tip11,1);
    label = UILabel::create();
    tip11->addChild(label);
    label->setFontName("CarterOne");
    label->setFontSize(20);
    label->setPosition(ccp(170, tip11->getContentSize().height));
    label->setAnchorPoint(ccp(0, 1));
    label->setColor(ccc3(241, 191, 194));
    label->setTextAreaSize(CCSize(200,150));
    label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);

    tip01 = CCSprite::create("duihuakuang/UI80.png");
    tip01->setPosition(ccp(SIZE.width+150,-120));
    this->addChild(tip01,1);
    label2 = UILabel::create();
    tip01->addChild(label2);
    label2->setFontName("CarterOne");
    label2->setFontSize(20);
    label2->setPosition(ccp(80, tip01->getContentSize().height));
    label2->setAnchorPoint(ccp(0, 1));
    label2->setColor(ccc3(241, 191, 194));
    label2->setTextAreaSize(CCSize(190,150));
    label2->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
}








