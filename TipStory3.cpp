//
//  TipStory3.cpp
//  ooo
//
//  Created by mac on 14-6-5.
//
//

#include "TipStory3.h"
#include "ShopScene.h"

CCScene* TipStory3::scene()
{
    CCScene* scene = CCScene::create();
    TipStory3* tipsLayer = TipStory3::create();
    scene->addChild(tipsLayer);
    return scene;
}

TipStory3* TipStory3::create()
{
    TipStory3* layer = new TipStory3();
    layer->init();
    layer->autorelease();
    return layer;
}

bool TipStory3::init()
{
    currentduihua_index = 0;
    nvRoleHead = CCSprite::create("duihuakuang/xiaowu.png");
    this->addChild(nvRoleHead,100);
    nvRoleHead->setPosition(ccp(-0.2*SIZE.width,10));
    nvRoleHead->setAnchorPoint(ccp(1, 0));
    nvRoleHead->setVisible(false);
    
    roleHead = CCSprite::create("duihuakuang/bashen.png");
    this->addChild(roleHead,100);
    roleHead->setPosition(ccp(1.2*SIZE.width,10));
    roleHead->setAnchorPoint(ccp(1, 0));
    roleHead->setVisible(false);
    roleHead->setScaleX(-1);
    
    
    bg = CCSprite::create("maps/map01.jpg");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    
    addTips();
    initHero();
    this->scheduleOnce(schedule_selector(TipStory3::tip1), 1.5f);
    this->scheduleOnce(schedule_selector(TipStory3::initNvRole), 3.5f);
    return true;
}


void TipStory3::addTip2()
{
    tip01->setVisible(true);
    roleHead->setVisible(true);
    tip01->runAction(CCMoveTo::create(0.2f, ccp(SIZE.width-280,80)));
    roleHead->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.70, 10))
                                           ,CCCallFunc::create(this, callfunc_selector(TipStory3::setText2)),NULL ));
}

void TipStory3::setText1()
{
    canSay = true;
    //label->setText(wordssss[currentduihua_index]);
    label->setText(I18N_STR(currentduihua_index+112));
    label->setVisible(true);

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}

void TipStory3::setText2()
{
    canSay = true;
    //label2->setText(wordssss[currentduihua_index]);
	label->setText(I18N_STR(currentduihua_index+112));
    label2->setVisible(true);

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(200, 100));
}



void TipStory3::initHero()
{
    hero = Hero::create();
    this->addChild(hero,10);
    hero->setPosition(SIZE.width/2, SIZE.height/4 + hero->bottomH);
    hero->stand();
    hero->shadow2 = CCSprite::createWithSpriteFrameName("yingzi.png");
    this->addChild(hero->shadow2);
    hero->s->setScaleX(-1);
}

void TipStory3::resetTip2()
{
    roleHead->setVisible(false);
    roleHead->setPosition(ccp(1.2*SIZE.width,10));
    tip01->setPosition(ccp(SIZE.width+150,-120));
    label2->setVisible(false);
}

void TipStory3::tip1(float dt)
{
    addTip2();
}

void TipStory3::tip2(float dt)
{
    currentduihua_index++;
    resetTip1();
    addTip2();
}

void TipStory3::tip3(float dt)
{
    currentduihua_index++;
    nvRole->setScaleX(-1);
    resetTip2();
    addTip1();
}

void TipStory3::tip4(float dt)
{
    currentduihua_index++;
    resetTip1();
    addTip2();
}

void TipStory3::tip5(float dt)
{
    currentduihua_index++;
    nvRole->setScaleX(1);
    resetTip2();
    addTip1();
    
    hero->s->setScaleX(1);
    nvRole->setPosition(hero->getPosition());
    nvRole->setZOrder(hero->getZOrder() + 1);
    hero->runAction(CCMoveBy::create(2.2, ccp(450, 0)));
    nvRole->runAction(CCMoveBy::create(2.2, ccp(450, 0)));
    hero->s->getAnimation()->playWithIndex(1);
    nvRole->getAnimation()->playWithIndex(1);
}

void TipStory3::GameEnd(float dt)
{
    CCLayerColor* black = CCLayerColor::create(ccc4(0, 0, 0,255), SIZE.width, SIZE.height);
    this->addChild(black,999999);
    UILabel* label = UILabel::create();
    label->setText("The End");
    label->setColor(ccc3(0xff, 0xae, 0x00));
    label->setFontSize(32);
    label->setFontName("CarterOne");
    label->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    black->addChild(label);
    
    CCFadeOut* fade = CCFadeOut::create(2);
    CCCallFunc* call = CCCallFunc::create(this,callfunc_selector(TipStory3::GoHome));
    CCSequence* seq = CCSequence::create(fade,call,NULL);
    this->runAction(seq);
}

void TipStory3::GoHome()
{
    CCDirector::sharedDirector()->replaceScene(ShopScene::scene());
}
void TipStory3::initNvRole(float dt)
{
    resetTip2();
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"nvzhujiao","nvzhujiao");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    nvRole = CCArmature::create("nvzhujiao");
    nvRole->setPosition(ccp(SIZE.width*(-0.1), SIZE.height/4));
    nvRole->getAnimation()->playWithIndex(1);
    this->addChild(nvRole);
    CCMoveBy* by = CCMoveBy::create(3,ccp(400.0f, 0.0f) );
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( TipStory3::fixFocus));
    CCSequence* seq = CCSequence::create(by,call,NULL);
    nvRole->runAction(seq);
}

void TipStory3::fixFocus()
{
    nvRole->getAnimation()->playWithIndex(0);
    currentduihua_index++;
    addTip1();
    this->scheduleOnce(schedule_selector( TipStory3::tip2), 2.0f );
    this->scheduleOnce(schedule_selector( TipStory3::tip3), 4.5f );
    this->scheduleOnce(schedule_selector( TipStory3::tip4), 7.0f );
    this->scheduleOnce(schedule_selector( TipStory3::tip5), 9.5f );
    
    this->scheduleOnce(schedule_selector( TipStory3::GameEnd), 12.5f );
}

void TipStory3::addTip1()
{
    tip11->setVisible(true);
    nvRoleHead->setVisible(true);
    tip11->runAction(CCMoveTo::create(0.2f, ccp(280,80)));
    nvRoleHead->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.22, 10))
                                             ,CCCallFunc::create(this, callfunc_selector(TipStory3::setText1)),NULL ));
}

void TipStory3::resetTip1()
{

    nvRoleHead->setVisible(false);
    nvRoleHead->setPosition(ccp(-0.2*SIZE.width,10));
    tip11->setPosition(ccp( -150, -120));
    label->setVisible(false);
}

void TipStory3::addTips()
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