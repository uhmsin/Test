//
//  HeroBoss.cpp
//  ooo
//
//  Created by mac on 14-6-4.
//
//

#include "HeroBoss.h"
#include "Hero.h"
#include "Define.h"
#include "MonsterAIState.h"
#include "Ef.h"
#define skillTag 1001
HeroBoss* HeroBoss::create()
{
    HeroBoss* boss = new HeroBoss();
    boss->autorelease();
    boss->init();
    return boss;
}

HeroBoss::HeroBoss()
{
    decide = -1;
}

bool HeroBoss::init()
{
    initBloodBar();
    scheduleUpdate();
    return true;
}

bool HeroBoss::initPosition()
{
    s->setColor(ccc3(0,100,100));
    s->getAnimation()->playWithIndex(0);
    s->setScaleX(-1.0f);
    setScale(1.2);
    this->setPosition(1200, Role->getPositionY());
    return true;
}

void HeroBoss::getUp()
{
    CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(HeroBoss::getUpCallBack));
    CCSequence* seq =  CCSequence::create(CCJumpBy::create(0.032*44, ccp(20,0),130 , 1),callfunc,NULL);    setAction(7,1);
    this->wudi = true;
    this->qianxiaqian("tx_qianxiaqian");
    this->s->runAction(seq);
    this->setAttackType(2);
    this->runAction(seq);
}

void HeroBoss::qianxiaqian(const char* name)
{
    Ef* effect = Ef::create(name);
    this->addChild(effect,10000,qianxiaqianEffectTag);
    CCSize size = this->s->getContentSize();
    effect->setScaleX(0.8*this->s->getScaleX());
    effect->setPositionY(-size.height/3);
    effect->setPositionX(size.width*0.1*this->s->getScaleX());
}


void HeroBoss::getUpCallBack()
{
    this->isBeAttack = false;
    this->GetFSM()->ChangeState(MonsterInitState::Instance());
    this->wudi = false;
}


void HeroBoss::wander()
{
    if(this->isBeAttack)
    {
        return;
    }
    if (this->getActionByTag(skillTag))
    {
        return;
    }
    CCCallFunc* call = CCCallFunc::create(this ,callfunc_selector( HeroBoss::WanderCallback) );
    this->runAction(call);
}

void HeroBoss::WanderCallback()
{
    float ran = CCRANDOM_0_1();
    if (ran <0.2 && decide != 1 && decide!=4 )
    {
        fadai();
    }
    else if (ran > 0.2 && ran < 0.55 && decide!=2 )
    {
        this->skill1();
    }
    else if (ran >0.55 && ran < 0.8  && decide!=3)
    {
        this->JinShen();
    }
    else if( ran>0.8 && decide!=4)
    {
        this->skilllianji();
    }
}

void HeroBoss::fadaio()
{
    this->wudi = false;
    float time = CCRANDOM_0_1()*1.2 + 1.0f;
    CCDelayTime* delay = CCDelayTime::create(time);
    delay->setTag(skillTag);
    this->runAction(delay);
    setAction(0);
}

void HeroBoss::fadai()
{
    decide = 1;
    this->wudi = false;
    float time = CCRANDOM_0_1()*1.2 + 1.0f;
    CCDelayTime* delay = CCDelayTime::create(time);
    delay->setTag(skillTag);
    this->runAction(delay);
    setAction(0);
}

void HeroBoss::skilllianji()
{
    this->setAttackType(4);
    decide = 4;
    this->wudi = false;
    CCMoveBy* to;
    if (this->getPositionX() > Role->getPositionX())
    {
        this->s->setScaleX(-1);
        to = CCMoveBy::create(0.5, ccp(-70 , 0));
    }else
    {
        this->s->setScaleX(1);
        to = CCMoveBy::create(0.5, ccp(70 , 0));
    }
    this->wudi = true;
    
    setAction(25,1);
    if(this->getChildByTag(tituiEffectTag) == NULL)
    {
        Ef* ef = Ef::create("tx_ti");
        this->setZOrder(100000);
        this->addChild(ef,this->getZOrder()+1000,tituiEffectTag);
        CCSize size = this->s->getContentSize();
        int direction = this->s->getScaleX();
        ef->setPosition(ccp(direction*size.width*5/10,size.height/2));
        ef->setScaleX(direction);
    }
    
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( HeroBoss::fadaio ));
    CCSequence* seq = CCSequence::create(  to, call,NULL );
    seq->setTag(skillTag);
    this->runAction( seq );
}

void HeroBoss::skillJinShen2(CCObject* obj)
{
    //skill5();
}

void HeroBoss::skill5()
{
     this->wudi = false;
    if (this->getPositionX() > Role->getPositionX())
    {
        this->s->setScaleX(-1 );
    }else
    {
        this->s->setScaleX(1 );
    }
    setAttackType(1);
    CCDelayTime* delay = CCDelayTime::create(0.4f);
    CCCallFunc* call = CCCallFunc::create(this ,callfunc_selector( HeroBoss::skill3 ) );
    CCSequence* seq = CCSequence::create(  delay, call,NULL );
    seq->setTag(skillTag);
    this->runAction(seq);
    this->skillEffect(ccp(0,0),2);
    setAction(16);
}



void HeroBoss::actionSkill()
{
    
}

void HeroBoss::skill1()
{
    decide = 2;
    setAttackType(1);
    CCMoveTo* to;
    if (this->getPositionX() > Role->getPositionX())
    {
        this->s->setScaleX(-1);
        to = CCMoveTo::create(0.5, ccpAdd(Role->getPosition(), ccp(-100, 0)) );
    }else
    {
        this->s->setScaleX(1);
        to = CCMoveTo::create(0.5,ccpAdd(Role->getPosition(), ccp(100, 0)) );
    }
    this->wudi = true;
    setAction(23,1);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector( HeroBoss::skillJinShen  ));
    CCSequence* seq = CCSequence::create(  to, call,NULL );
    seq->setTag(skillTag);
    this->runAction( seq );
}

void HeroBoss::skillJinShen()
{
    JinShen();
}

void HeroBoss::JinShen()
{
    decide = 3;
    this->wudi = false;
    float ran = CCRANDOM_0_1();
    if (ran < 0.3)
    {
        CCDelayTime* delay = CCDelayTime::create(0.4f);
        delay->setTag(skillTag);
        this->runAction(delay);
        setAction(13);
    }else if(ran<0.6 && ran >= 0.3 )
    {
        if (this->getPositionX() > Role->getPositionX())
        {
            this->s->setScaleX(-1 );
        }else
        {
            this->s->setScaleX(1 );
        }
        setAttackType(1);
        CCDelayTime* delay = CCDelayTime::create(0.4f);
        CCCallFunc* call = CCCallFunc::create(this ,callfunc_selector( HeroBoss::skill3 ) );
        CCSequence* seq = CCSequence::create(  delay, call,NULL );
        seq->setTag(skillTag);
        this->runAction(seq);
        this->skillEffect(ccp(0,0),2);
        setAction(16);
        //this->s->getAnimation()->setSpeedScale(0.5f);
    }else
    {
        
    }
}

void HeroBoss::skill3o(CCObject* obj)
{
    skill3();
}

void HeroBoss::skill3()
{

    setAttackType(1);
    this->skillEffect(ccp(0,0),1);
    CCDelayTime* delay = CCDelayTime::create(0.38f);
    CCCallFunc* call = CCCallFunc::create(this ,callfunc_selector( HeroBoss::skill4 ) );
    CCSequence* seq = CCSequence::create(  delay, call,NULL );
    seq->setTag(skillTag);
    this->runAction(seq);
    delay->setTag(skillTag);
    setAction(14);
}

void HeroBoss::skill4o(CCObject* obj)
{
    skill4();
}

void HeroBoss::skill4()
{
    setAttackType(4);
    CCDelayTime* delay = CCDelayTime::create(0.6f);
    this->skillEffect(ccp(0,0),0);

    
    CCCallFunc* call = CCCallFunc::create(this ,callfunc_selector( HeroBoss::fadaio) );
    CCSequence* seq = CCSequence::create(  delay, call,NULL );
    seq->setTag(skillTag);
    this->runAction(seq);

    setAction(20, 1);
}

float HeroBoss::getDis()
{
    return ccpDistance(Role->getPosition(), this->getPosition());
}


