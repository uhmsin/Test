//
//  RemoteMonster.cpp
//  king04
//
//  Created by mac on 14-5-7.
//
//

#include "RemoteMonster.h"
#include "Bullet.h"
RemoteMonster* RemoteMonster::create()
{
    RemoteMonster* monster = new RemoteMonster();
    monster->init();
    monster->autorelease();
    return monster;
}

bool RemoteMonster::init()
{
     attackRange = 560;    //近身攻击范围
     gongjiJianGeSHU = 0;
     return true;
}

void RemoteMonster::attackM1()
{
    Bullet* bullet = Bullet::create(this);
    gameLayer->addChild(bullet,this->getZOrder());
    bullet->setPosition(ccp(this->getPositionX() + this->s->getScaleX()* this->s->getContentSize().width/2 ,  this->getPositionY()  + 150) );
    this->stopAllActions();
    this->setAction(5,1);
    CCMoveBy* moveBy = CCMoveBy::create(2.0f, ccp(this->s->getScaleX()*1200, 0));
    CCCallFunc* call = CCCallFunc::create(bullet, callfunc_selector(Bullet::removeBullet));
    CCSequence* seq = CCSequence::create(moveBy,call,NULL);
    bullet->runAction(seq);
}

void RemoteMonster::attackM2()
{
    Bullet* bullet = Bullet::create(this);
    gameLayer->addChild(bullet,this->getZOrder());
    bullet->setPosition(ccp(this->getPositionX() + this->s->getScaleX()* this->s->getContentSize().width/2 ,  this->getPositionY()  + 150) );
    this->stopAllActions();
    this->setAction(5,1);
    CCMoveBy* moveBy = CCMoveBy::create(1.0f, ccp(this->s->getScaleX()*600, 0));
    CCCallFunc* call = CCCallFunc::create(bullet, callfunc_selector(Bullet::removeBullet));
    CCSequence* seq = CCSequence::create(moveBy,call,NULL);
    bullet->runAction(seq);
}

void RemoteMonster::attackM3()
{
    Bullet* bullet = Bullet::create(this);
    gameLayer->addChild(bullet,this->getZOrder());
    bullet->setPosition(ccp(this->getPositionX() + this->s->getScaleX()* this->s->getContentSize().width/2 ,  this->getPositionY()  + 150) );
    this->stopAllActions();
    this->setAction(5,1);
    CCMoveBy* moveBy = CCMoveBy::create(1.0f, ccp(this->s->getScaleX()*600, 0));
    CCCallFunc* call = CCCallFunc::create(bullet, callfunc_selector(Bullet::removeBullet));
    CCSequence* seq = CCSequence::create(moveBy,call,NULL);
    bullet->runAction(seq);
}

void RemoteMonster::wander()
{
    if (this->canAttack())
    {
        this->attack();
        return;
    }
    if(this->actionID!=0)
    {
        return;
    }
    setAction(1);
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(RemoteMonster::WanderCallback));
    this->runAction(flipx);
}

bool RemoteMonster::canAttack()
{
    gongjiJianGE = 300;
    gongjiJianGeSHU++;
    if(!this->inAttackRange())
    {
        return false;
    }
    else if( CCRANDOM_0_1() * 100 > (80 - 3*gameLayer->id) )
    {
        if(gongjiJianGeSHU - gongjiJianGE > 0)
        {
              gongjiJianGeSHU = 0;
              return true;
        }else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void RemoteMonster::WanderCallback()
{
    float x = getNextPosx();
    float y = this->getPositionY();
    CCPoint curr_pos = this->getPosition();
    CCPoint next_pos = ccp(x,y);
    float distance = ccpDistance(curr_pos, next_pos);
    float duration = distance/speedMain;
    CCMoveTo*  moveTo = CCMoveTo::create(duration, next_pos);
    float value= next_pos.x-this->getPositionX();
    if (value>0)
    {
        this->s->setScaleX(1);   //提供一个转身方法，，需要修复血条的方向
        this->bloodbar->setScaleX(-1);
    }
    else
    {
        this->s->setScaleX(-1);   //提供一个转身方法
        this->bloodbar->setScaleX(1);
    }
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(Monster::WanderCallback));
    CCSequence* sequence = CCSequence::create(moveTo,flipx,NULL);
    sequence->setTag(WanderTag);
    runAction(sequence);
}

float RemoteMonster::getNextPosx()  //获取要冲的x
{
    float role_x = Role->getPositionX();
    float x = CCRANDOM_0_1()*SIZE.width/2;
    x = MAX(x,SIZE.width/3 );
    float target_x;
    if (this->getPositionX() > role_x)
    {
        target_x = role_x + x ;
    }else{
        target_x = role_x - x ;
    }
    return target_x;
}
