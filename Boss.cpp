//
//  Boss.cpp
//  King
//
//  Created by mac on 14-3-31.
//
//

#include "Boss.h"
#include "Define.h"
#include "Hero.h"
#include "MonsterAIState.h"

Boss1* Boss1::create()
{
    Boss1* boss = new Boss1();
    boss->init();
    boss->autorelease();
    return NULL;
}
bool Boss1::init()
{
    oldeseekTime = 15;     //冲肚子的频率。 这个值越大，冲的频率越低
    attackRange = 160;    //近身攻击范围
    return true;
}

void Boss1::attackM1()
{
    setAction(5,1);
}

void Boss1::attackM2()
{
    setAction(5,1);
}

void Boss1::attackM3()
{
    setAction(5,1);
}

bool Boss1::inAttackRange()
{
    this->attackRange = 110;
    int distance = this->getPositionX() - Role->getPositionX();
    if( abs(distance)  < this->attackRange)
        return true;
    return false;
}

void Boss1::attack()
{
    if(Role->isDie)
    {
        stand();
        return;
    }
    if(this->isBeAttack)
    {
        return;
    }
    int ran =  CCRANDOM_0_1()*100;
    if (!this->inAttackRange())
    {
        this->SeekRole();
    }else
    {
        attackRange = 60;
        if(Role->getPositionX()>this->getPositionX()){
            this->s->setScaleX(1);
        }else{
            this->s->setScaleX(-1);
        }
        if (ran<33&&ran>0)
        {
            attackM1();
        }else if (ran>33&&ran<66)
        {
            attackM2();
        }else
        {
            attackM3();
        }
    }
}

void Boss1::SeekRole()
{
    if(Role->isDie)
    {
        stand();
        return;
    }
    if(this->getActionByTag(SeekRoleTag))
    {
        return;
    }
    
    if(seekTime > 0)
    {
        seekTime --;
        setAction(1);
        return;
    }
    seekTime = 8;
    
    if(this->actionID != 6)
    {
        this->stopAllActions();
    }
    isSeekRole = true;
    CCPoint target =  Role->getPosition();
    target.y = this->getPositionY();
    CCPoint curr_pos = this->getPosition();
    int s_s = 32;
    if(this->s!=NULL && this->s->getAnimation()!=NULL)
    {
      //  s_s = this->s->getAnimation()->m_pMovementData->duration;   //bug
    }
    float value= target.x-this->getPositionX();
    CCMoveBy* moveBy;
    CCEaseOut* out;
    if (value>0)
    {
        target = ccpSub(target,ccp(this->attackRange,0));
        this->s->setScaleX(1);
        moveBy = CCMoveBy::create((s_s-5)* 0.032,ccp(600,0));
        out = CCEaseOut::create(moveBy, 4);
    }
    else
    {
        target = ccpAdd(target,ccp(this->attackRange,0));
        this->s->setScaleX(-1);
        moveBy = CCMoveBy::create((s_s-5)* 0.032 ,ccp(-600,0));
        out =  CCEaseOut::create(moveBy, 4);
    }
    CCDelayTime* delay = CCDelayTime::create(5 * 0.032);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Boss1::SeekRoleCallback));
    CCSequence* seq = CCSequence::create(call,delay,out,NULL);
    seq->setTag(SeekRoleTag);
    this->runAction(seq );
}

void Boss1::SeekRoleCallback()
{
     this->setAction(6,1);
}

void Boss1::getUp()
{
    this->wudi = true;
    this->setAction(7,1);
    CCDelayTime* delay = CCDelayTime::create(40*0.032);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Boss1::getUpCallBack));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    this->runAction(seq);
}

void Boss1::getUpCallBack()
{
    
    this->isBeAttack = false;
    this->GetFSM()->ChangeState(MonsterInitState::Instance());
    this->wudi = false;
 
}

bool Boss1::canAttack()
{
    if(Role->wudi){
        return false;
    }
    if( CCRANDOM_0_1() * 100 > 55)
    {
        return true;
    }else
    {
    return false;
    }
}

void Boss1::wander()
{
    if(Role->isDie)
    {
        stand();
        return;
    }
    if(this->isBeAttack)
    {
        return;
    }
    if (this->canAttack())
    {
        this->attack();
    }
    if(this->getActionByTag(WanderTag) || this->getActionByTag(SeekRoleTag))
    {
        return;
    }
    int random = 100 * CCRANDOM_0_1();
    if(random > 70)
    {
        delayAttackTime = 40;
    }
    if(this->actionID != 6){
        this->stopAllActions();
        s->stopAllActions();
    }
    setAction(1);
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(Boss1::WanderCallback));
    this->runAction(flipx);
}

void Boss1::WanderCallback()
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
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(Boss1::WanderCallback));
    CCSequence* sequence = CCSequence::create(moveTo,flipx,NULL);
    sequence->setTag(WanderTag);
    runAction(sequence);
}

void Boss1::die()
{
    gameLayer->monsterNum = 0;
    gameLayer->unschedule(schedule_selector(GameScene::gameLogic));
    CCObject* obj;
    CCARRAY_FOREACH(gameLayer->npc, obj)
    {
        Monster* m = dynamic_cast<Monster*>(obj);
        if (m->isDie == false &&  m->id != this->id)
        {
            m->setHP(0);
            bloodbar->processPlayerHP();
            m->die();
        }
    }
    Monster::die();

}

Boss2* Boss2::create()
{
    Boss2* boss = new Boss2();
    boss->init();
    return boss;
}

bool Boss2::init()
{
    attackRange = 280;    //近身攻击范围
    return true;
}

void Boss2::SeekRole()
{
    if(this->getActionByTag(SeekRoleTag) )
    {
        return;
    }
    
    if(seekTime > 0)
    {
        seekTime --;
        setAction(1);
        return;
    }
    seekTime = 8;
    
    if(this->actionID != 6)
    {
        this->stopAllActions();
    }
    isSeekRole = true;
    CCPoint target =  Role->getPosition();
    target.y = this->getPositionY();
    CCPoint curr_pos = this->getPosition();
    int s_s = 32;
    if(this->s!=NULL && this->s->getAnimation()!=NULL)
    {
        //  s_s = this->s->getAnimation()->m_pMovementData->duration;   //bug
    }
    float value= target.x-this->getPositionX();
    CCMoveBy* moveBy;
    CCEaseOut* out;
    if (value>0)
    {
        target = ccpSub(target,ccp(this->attackRange,0));
        this->s->setScaleX(1);
        moveBy = CCMoveBy::create((s_s-5)* 0.032,ccp(400,0));
        out = CCEaseOut::create(moveBy, 4);
    }
    else
    {
        target = ccpAdd(target,ccp(this->attackRange,0));
        this->s->setScaleX(-1);
        moveBy = CCMoveBy::create((s_s-5)* 0.032 ,ccp(-400,0));
        out =  CCEaseOut::create(moveBy, 4);
    }
    CCDelayTime* delay = CCDelayTime::create(5 * 0.032);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Boss1::SeekRoleCallback));
    CCSequence* seq = CCSequence::create(call,delay,out,NULL);
    seq->setTag(SeekRoleTag);
    this->runAction(seq );
}

void Boss2::attackM1()
{
    this->stopActionByTag(WanderTag);
    setAction(5,1);
}

void Boss2::attackM2()
{
     this->stopActionByTag(WanderTag);
     setAction(6,1);
}

void Boss2::attackM3()
{
    this->stopActionByTag(WanderTag);
    setAction(7,1);
}

void Boss2::attackM4()
{
    this->stopActionByTag(WanderTag);
    setAction(8,1);
}

bool Boss2::canAttack()
{
    if(Role->wudi){
        return false;
    }
    if( CCRANDOM_0_1() * 100 > 40)
    {
        return true;
    }else
    {
        return false;
    }
}

void Boss2::actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID)
{
    if (eventType == START) {
        this->setZOrder(10000);
    }else if (eventType == COMPLETE)
    {
        this->setZOrder(0);
        if(delegate)
        {
            delegate->actionDidAttack(this);
        }
    
        if(this->actionID !=0)
        {
            if (this->actionID == 5)
            {
                this->setAction(6, 1);
            }else
            {
                this->setAction(0);
                m_state = s_stand;
                isBeAttack =false;
            }
        }
    }
}

void Boss2::getUp()
{
    CCDelayTime* move  =  CCDelayTime::create(0.5f);
    CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Boss2::getUpCallBack));
    CCSequence* seq =  CCSequence::create(move, callfunc, NULL);
    setAction(7,1);
    this->wudi = true;
    this->runAction(seq);

}

void Boss2::getUpCallBack()
{
    
    this->isBeAttack = false;
    this->GetFSM()->ChangeState(MonsterInitState::Instance());
    this->wudi = false;
}

void Boss2::attack()
{
    if(this->isBeAttack)
    {
        return;
    }
    int ran =  CCRANDOM_0_1()*100;
    if (!this->inAttackRange())
    {
         if(ran>80)
         {
             this->SeekRole();
         }
    }else
    {
        if(this->actionID >= 5 &&this->actionID <= 8)
        {
            return;
        }
  
        if(Role->getPositionX()>this->getPositionX()){
            this->s->setScaleX(1);
        }else{
            this->s->setScaleX(-1);
        }
        if (ran<20&&ran>0)
        {
            attackM1();
        }else if (ran>40&&ran<20)
        {
            attackM2();
        }else if (ran>60&&ran<65)
        {
            attackM3();
        }else if (ran>60&&ran<80)
        {
            attackM4();
        }
    }
}

void Boss2::wander()
{
    if (this->canAttack())
    {
        this->attack();
       // return;
    }
    if(this->actionID!=0)
    {
        return;
    }
    setAction(1);
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(Boss2::WanderCallback));
    this->runAction(flipx);
}

void Boss2::WanderCallback()
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

void Boss2::die()
{
    gameLayer->monsterNum = 0;
    gameLayer->unschedule(schedule_selector(GameScene::gameLogic));
    CCObject* obj;
    CCARRAY_FOREACH(gameLayer->npc, obj)
    {
        Monster* m = dynamic_cast<Monster*>(obj);
        if (m->isDie == false &&  m->id != this->id)
        {
            m->setHP(0);
            bloodbar->processPlayerHP();
            m->die();
        }
    }
    Monster::die();
}

Boss4* Boss4::create()
{
    Boss4* boss = new Boss4();
    boss->init();
    return boss;
}

void Boss4::getUp()
{
    CCDelayTime* move  =  CCDelayTime::create(0.5f);
    CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Boss2::getUpCallBack));
    CCSequence* seq =  CCSequence::create(move, callfunc, NULL);
    setAction(7,1);
    this->wudi = true;
    this->runAction(seq);
    
}

void Boss4::getUpCallBack(CCObject* pSender)
{
    
    this->isBeAttack = false;
    this->GetFSM()->ChangeState(MonsterInitState::Instance());
    this->wudi = false;
}


bool Boss4::init()
{
    attackRange = 280;    //近身攻击范围
    return true;
}

void Boss4::SeekRole()
{
    if(this->getActionByTag(SeekRoleTag) )
    {
        return;
    }
    
    if(seekTime > 0)
    {
        seekTime --;
        setAction(1);
        return;
    }
    seekTime = 8;
    
    if(this->actionID != 6)
    {
        this->stopAllActions();
    }
    isSeekRole = true;
    CCPoint target =  Role->getPosition();
    target.y = this->getPositionY();
    CCPoint curr_pos = this->getPosition();
    int s_s = 32;
    if(this->s!=NULL && this->s->getAnimation()!=NULL)
    {
        //  s_s = this->s->getAnimation()->m_pMovementData->duration;   //bug
    }
    float value= target.x-this->getPositionX();
    CCMoveBy* moveBy;
    CCEaseOut* out;
    if (value>0)
    {
        target = ccpSub(target,ccp(this->attackRange,0));
        this->s->setScaleX(1);
        moveBy = CCMoveBy::create((s_s-5)* 0.032,ccp(400,0));
        out = CCEaseOut::create(moveBy, 4);
    }
    else
    {
        target = ccpAdd(target,ccp(this->attackRange,0));
        this->s->setScaleX(-1);
        moveBy = CCMoveBy::create((s_s-5)* 0.032 ,ccp(-400,0));
        out =  CCEaseOut::create(moveBy, 4);
    }
    CCDelayTime* delay = CCDelayTime::create(5 * 0.032);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Boss1::SeekRoleCallback));
    CCSequence* seq = CCSequence::create(call,delay,out,NULL);
    seq->setTag(SeekRoleTag);
    this->runAction(seq );
}

void Boss4::attackM1()
{
    this->stopActionByTag(WanderTag);
    setAction(5,1);
}

void Boss4::attackM2()
{
    this->stopActionByTag(WanderTag);
    setAction(6,1);
}

void Boss4::attackM3()
{
    this->stopActionByTag(WanderTag);
    setAction(7,1);
}

bool Boss4::canAttack()
{
    if(Role->wudi){
        return false;
    }
    if( CCRANDOM_0_1() * 100 > 40)
    {
        return true;
    }else
    {
        return false;
    }
}

void Boss4::actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID)
{
    if (eventType == START) {
        this->setZOrder(10000);
    }else if (eventType == COMPLETE)
    {
        this->setZOrder(0);
        if(delegate)
        {
            delegate->actionDidAttack(this);
        }
        
        if(this->actionID !=0)
        {
            if (this->actionID == 5)
            {
                this->setAction(6, 1);
            }else
            {
                this->setAction(0);
                m_state = s_stand;
                isBeAttack =false;
            }
        }
    }
}

void Boss4::attack()
{
    if(this->isBeAttack)
    {
        return;
    }
    int ran =  CCRANDOM_0_1()*100;
    if (!this->inAttackRange())
    {
        if(ran>80)
        {
            this->SeekRole();
        }
    }else
    {
        if(this->actionID >= 5 &&this->actionID <= 8)
        {
            return;
        }
        if(Role->getPositionX()>this->getPositionX()){
            this->s->setScaleX(1);
        }else{
            this->s->setScaleX(-1);
        }
        if (ran<33&&ran>0)
        {
            attackM1();
        }else if (ran>33&&ran<66)
        {
            attackM2();
        }else if (ran>66&&ran<100)
        {
            attackM3();
        }
    }
}

void Boss4::wander()
{
    if (this->canAttack())
    {
        this->attack();
        // return;
    }
    if(this->actionID!=0)
    {
        return;
    }
    setAction(1);
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(Boss4::WanderCallback));
    this->runAction(flipx);
}

void Boss4::WanderCallback()
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

void Boss4::die()
{
    gameLayer->monsterNum = 0;
    gameLayer->unschedule(schedule_selector(GameScene::gameLogic));
    CCObject* obj;
    CCARRAY_FOREACH(gameLayer->npc, obj)
    {
        Monster* m = dynamic_cast<Monster*>(obj);
        if (m->isDie == false &&  m->id != this->id)
        {
            m->setHP(0);
            bloodbar->processPlayerHP();
            m->die();
        }
    }
    Monster::die();
}