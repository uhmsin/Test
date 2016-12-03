//
//  BeatEffect.cpp
//  King
//
//  Created by mac on 14-3-29.
//
//
#include "BeatEffect.h"
#include "Define.h"
#include "Game.h"
#include "ARPG.h"
enum
{
    befalldown = 99999
};
BeatEffect::~BeatEffect()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BeatEffect::updateAnimation), this);
}
BeatEffect::BeatEffect()
{
    m_delegate = NULL;
    m_beAttackDelay = 2;
    m_intGroundH = 0;
    m_attackType = kAttack_None;
    incrementY = 0;
    m_reduceSpeed = 0.3f;
    m_origiPos = ccp(ULONG_MAX,ULONG_MAX);
}

BeatEffect* BeatEffect::create(CCNode* delegate)
{
    BeatEffect* _beatEffect = new BeatEffect();
    if(_beatEffect)
    {
        _beatEffect->m_delegate = delegate;
        return _beatEffect;
    }else
    {
        CC_SAFE_DELETE(_beatEffect);
        return NULL;
    }
}

BeatEffect* BeatEffect::create(CCNode* delegate,int attackID,int sufferDir)
{
    BeatEffect* _beatEffect = new BeatEffect();
    if(_beatEffect)
    {
        _beatEffect->autorelease();
        _beatEffect->m_delegate = delegate;
        _beatEffect->direction = sufferDir;
        _beatEffect->executeAnimationAndAction(attackID);

        return _beatEffect;
    }else
    {
        CC_SAFE_DELETE(_beatEffect);
        return NULL;
    }
}

void BeatEffect::executeAnimationAndAction(int attackID)
{
    ARPG* delegate = dynamic_cast<ARPG*>(m_delegate);
    if(!delegate || !delegate->s)
        return;
    delegate->isBeAttack = true;
    switch (attackID) {
        case 1:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackCallFuncO1), this);
            if(delegate->getType() == 1)
            {
               this->beHitBack(funcO, 15, 0.12, 0.1,0.5,false); // 普通攻击
            }
            else
            {
               this->beHitBack(funcO, 25, 0.25, 0.2,2,false); // 普通攻击
            }
            break;
        }
        case 2:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatSky(funcO, 130, 190, 70, 0.6, 0.4, 0.35, 0.8,1.0);  //浮空中
            break;
        }
        case 3:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatScrollDwon(funcO, 280, 250, 50, 0.85, 0.3, 0.45, 0.7,4); // 浮空翻到地
            break;
        }
        case 4:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatSky(funcO, 130, 380, 70, 0.6, 0.4, 0.35, 0.8,1.0);  //击飞远
            break;
        }
        case 5:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatSky(funcO, 190, 60, 30, 0.75, 0.3, 0.5, 0.5,1.3); // 浮空高
            break;
        }
        case 6:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatSky(funcO, 90, 60, 30, 0.5, 0.3, 0.35, 0.7,1.0); // 浮空近
            break;
        }
        case 7:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackCallFuncO1), this);
            this->beHitBack(funcO, 60, 0.25, 0.5,2.8,false); // 普通攻击
            break;
        }
        case 8:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackCallFuncO1), this);
            this->beHitBack(funcO, 100, 0.25, 0.5,2.8,false); // 普通攻击
            break;
        }
        case 9:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackCallFuncO), this);
            //funcO->setTag(befalldown);
            this->beHitDown(funcO,3.5f);
            break;
        }
        case 10:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatSky(funcO, 80, 240, 70, 0.6, 0.4, 0.35, 0.8,0.0);  //浮空中
            break;
        }
            
        case 11:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackCallFuncO1), this);
            if(delegate->getType() == 1)
            {
                this->beHitBack(funcO, 15, 0.12, 0.1,0.5,false); // 普通攻击
            }
            else
            {
                this->beHitBack(funcO, 25, 0.25, 0.2,2,false); // 普通攻击
            }
            break;
        }
        case 12:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatSky(funcO, 190, 460, 30, 2.5, 0.3, 0.5, 0.5,1.3); // 浮空高
            break;
        }
        case 13:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitFloatSky(funcO, 190, 360, 30, 0.8, 0.3, 0.5, 0.5,1.3); // 浮空高
            break;
        }
            
        case 14:
        {
            CCCallFuncO* funcO = CCCallFuncO::create(m_delegate, callfuncO_selector(ARPG::beAttackFlyCallFuncO), this);
            this->beHitBack(funcO, 0.0, 0.0, 0.0,0.0,false); // 普通攻击

            break;
        }
    }
}

void BeatEffect::beHitDown(CCCallFuncO* callback,int sufferDelay)
{
    ARPG* delegate = dynamic_cast<ARPG*>(m_delegate);
    if(!delegate && delegate->s)
        return;

    delegate->stopAllActions();
    delegate->s->stopAllActions();
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BeatEffect::updateAnimation), this);
    
    if(delegate->getType() == 1)
    {
        sufferDelay /= 2;
    }
    m_attackType = kAttack_beHitDown;
    m_beAttackDelay = sufferDelay;
    CCDelayTime* delay = CCDelayTime::create(m_beAttackDelay * MINFRAMESPACE);
    CCDelayTime* delay2 = CCDelayTime::create(1.0f);
    CCCallFuncO* doStand = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::doActionsByTag),CCStringMake(ANIMATION_STAND));//站立
    CCCallFuncO* getDown = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::doActionsByTag),CCStringMake(ANIMATION_GETDOWN));
    CCCallFuncO* behit = CCCallFuncO::create(this, callfuncO_selector(BeatEffect::doShakeLeftAndRight), NULL);
    if(!delay || !doStand || !getDown || !delay2 || !behit)
        return ;
    CCSequence* seq = CCSequence::create(behit,delay,getDown,delay2,doStand,callback,NULL);
    delegate->s->runAction(seq);
    delegate->isFirstDropBack = true;
}

void BeatEffect::doShakeLeftAndRight(CCObject* pSender)
{
    ARPG* delegate = dynamic_cast<ARPG*>(m_delegate);
    if(!delegate || !delegate->s)
        return;
    if(delegate->isUnderAttack)
        return ;
    delegate->s->resumeSchedulerAndActions();
    delegate->doActionsByTag(CCStringMake(ANIMATION_BEATBACK));
    CCMoveBy* move = CCMoveBy::create(MINFRAMESPACE,ccp(-2,0));
    CCMoveBy* moveBack = (CCMoveBy*)move->reverse();
    CCActionInterval* rep = CCRepeat::create(CCSequence::create(move,moveBack,NULL),m_beAttackDelay);
    delegate->isUnderAttack = true;
    rep->setTag(befalldown);
    delegate->runAction(rep);
}

void BeatEffect::beFallDown()
{
    
}

void BeatEffect::beHitBack(CCCallFuncO* callback,int dis,float backTime,float stdTimeSpa,int sufferDelay,bool reduce)
{
    ARPG* delegate = dynamic_cast<ARPG*>(m_delegate);
    if(!delegate || !delegate->s)
        return ;
    if(delegate->getActionByTag(befalldown))
    {
        return;
    }
    delegate->stopAllActions();
    delegate->s->stopAllActions();
    delegate->s->resumeSchedulerAndActions();
//    
//    delegate->setPosition(ccpAdd(delegate->getPosition(), delegate->s->getPosition()));
//    delegate->s->setPosition(ccp(0,0));
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BeatEffect::updateAnimation), this);
    
    m_attackType = kAttack_beHitBack;
    m_distanceX += dis;
    m_beAttackDelay = sufferDelay;
    
    CCPoint pos = delegate->s->getPosition();
    CCPoint pos2 = delegate->getPosition();
    m_origiPos = m_origiPos.equals(ccp(ULONG_MAX,ULONG_MAX)) ? pos : m_origiPos;
    CCPoint movePos;//两次浮空的位置
    if(direction == DHERO_RIGHT)
    {
        movePos = ccp(pos.x + dis,m_origiPos.y);
        m_newNodePos = ccp(pos2.x + dis,pos2.y);
        delegate->s->setScaleX(-1);
    }
    else
    {
        movePos = ccp(pos.x - dis ,m_origiPos.y);
        m_newNodePos = ccp(pos2.x - dis,pos2.y);
        delegate->s->setScaleX(1);
    }
    CCAction* move = NULL;
    if(reduce)
        move = CCEaseIn::create(CCMoveBy::create(backTime, movePos), backTime * 2 / 3);
    else
        move = CCMoveBy::create(backTime, movePos);
    CCDelayTime* delay = CCDelayTime::create(m_beAttackDelay * MINFRAMESPACE);
    CCDelayTime* delay2 = CCDelayTime::create(stdTimeSpa);
    CCCallFuncO* stand = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::doActionsByTag),CCStringMake(ANIMATION_STAND));
    CCCallFuncO* behit = CCCallFuncO::create(this, callfuncO_selector(BeatEffect::doShakeLeftAndRight), NULL);
    
    
    if(move && delay && delay2 && stand && behit)
        delegate->runAction(CCSequence::create(behit,delay,move,delay2,stand,callback,NULL));
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(BeatEffect::updateAnimation), this, 0.0f,false);
}

void BeatEffect::updateAnimation(float dt)
{
    if (m_delegate && gameLayer !=NULL) {
        ARPG* delegate = dynamic_cast<ARPG*>(m_delegate);
        if(delegate && delegate->s)
        {
            CCSpeed* speed = dynamic_cast<CCSpeed*>(delegate->s->getActionByTag(kAnimation_tag_Jump));
            CCPoint curPos = delegate->s->getPosition();
            //上升减速、下落加速
            float data = curPos.y - incrementY;//Y方向的增量
            incrementY = curPos.y;
            float disY = fabsf(curPos.y - m_origiPos.y);
            if(speed && disY >= m_addedGroundH - REDUCESPEEDSPACE)
                speed->setSpeed(m_reduceSpeed);
            else if(speed && disY <= m_addedGroundH - REDUCESPEEDSPACE)
                speed->setSpeed(1.0f);
            
            if(m_attackType == kAttack_beHitFloat ||
               m_attackType == kAttack_beHitDaoDiChuo ||
               m_attackType == kAttack_beHitSkyDown ||
               m_attackType == kAttack_beHitForceHit)//被击打浮空
            {
                if(data > 0 ) //上升
                    delegate->doActionsByTag(CCStringMake(ANIMATION_UPFLOAT));
                else if(data < 0)//下落
                {
                    delegate->doActionsByTag(CCStringMake(ANIMATION_DOWNFLOAT));
                    if(disY <= MINFLOAT)//倒地
                        delegate->doActionsByTag(CCStringMake(ANIMATION_GETDOWN));
                }
            }
            else if(m_attackType == kAttack_beHitFloatScrollDown)//被击打浮空旋转落下
            {
                if(delegate->isFirstDropBack)
                {
                    if(data > 0 ) //上升
                        delegate->doActionsByTag(CCStringMake(ANIMATION_UPFLOAT));
                    else if(data < 0)//下落
                    {
                        delegate->doActionsByTag(CCStringMake(ANIMATION_DOWNFLOAT));
                        if(disY <= MINFLOAT)//倒地
                            delegate->doActionsByTag(CCStringMake(ANIMATION_GETDOWN));
                    }
                }
                else
                    delegate->doActionsByTag(CCStringMake(ANIMATION_BEATBACK));
            }
            
            if(!delegate->isUnderAttack)
            {
                CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BeatEffect::updateAnimation), this);
                delegate->doActionsByTag(CCString::create(ANIMATION_STAND));
                CCPoint p =  gameLayer->convertToNodeSpace(delegate->convertToWorldSpace( delegate->s->getPosition()));
                p.y = SIZE.height/4 - delegate->bottomH;
                delegate->setPosition(p);
                delegate->s->setPosition(ccp(0,0));
                delegate->isBeAttack = false;
                cleanMemenbers();
            }
        }

    }else
    {
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BeatEffect::updateAnimation), this);
        CCLOG("%s","monster没了");
    }
 }

void BeatEffect::beHitFloatSky(CCCallFuncO* callback,int groundH,int dis,int secDis,float firTime,float secTime,float stdSpace,float redTime,float sufferDelay)
{
    ARPG* delegate = dynamic_cast<ARPG*>(m_delegate);
    if(!delegate && delegate->s)
        return;
    delegate->stopAllActions();
    delegate->s->stopAllActions();
    delegate->s->resumeSchedulerAndActions();
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BeatEffect::updateAnimation), this);
    
    int _dis = secDis;//落地回弹的水平位移
    
    m_attackType = kAttack_beHitFloat;
    m_distanceX += dis;
    m_beAttackDelay = sufferDelay;
    m_reduceSpeed = redTime;
    
    CCPoint pos = delegate->s->getPosition();
    CCPoint pos2 = delegate->getPosition();
    m_origiPos = m_origiPos.equals(ccp(ULONG_MAX,ULONG_MAX)) ? pos : m_origiPos;
    m_intGroundH = groundH;
    m_addedGroundH += groundH;
    CCPoint firstPos,secondPos;//两次浮空的位置
    if(direction == DHERO_RIGHT)
    {
        firstPos = ccp(pos.x + (dis - _dis),m_origiPos.y);
        secondPos = ccp(firstPos.x + _dis,0);
        m_newNodePos = ccp(pos2.x + dis,pos2.y);
        delegate->s->setScaleX(-1);
    }
    else
    {
        firstPos = ccp(pos.x - (dis - _dis) ,m_origiPos.y);
        secondPos = ccp(firstPos.x - _dis,0);
        m_newNodePos = ccp(pos2.x - dis,pos2.y);
        delegate->s->setScaleX(1);
    }
    
    CCJumpTo* jump = CCJumpTo::create(firTime, firstPos,groundH,1);//第一次浮空，
    CCJumpTo* jump2;
    if(delegate->getType() == 1)
    {
        jump2 = CCJumpTo::create(secTime/2, secondPos, 0, 1);//落地回弹
    }
    else
    {
         jump2 = CCJumpTo::create(secTime/3, secondPos, 10, 1);//落地回弹
    }
    CCDelayTime* delay = CCDelayTime::create(m_beAttackDelay * MINFRAMESPACE);
    CCDelayTime* delay2 = CCDelayTime::create(stdSpace);
    CCCallFuncO* doFloatUp = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::doActionsByTag),CCStringMake(ANIMATION_UPFLOAT));
    CCCallFuncO* doStand = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::doActionsByTag), CCStringMake(ANIMATION_STAND));//站立
    CCCallFuncO* behit = CCCallFuncO::create(this, callfuncO_selector(BeatEffect::doShakeLeftAndRight), NULL);
    
    if(!jump || !delay || !doFloatUp || !jump2 || !behit)
        return ;
    CCSequence* seq = CCSequence::create(behit,delay,doFloatUp,jump,jump2,delay2,doStand,callback,NULL);

    CCSpeed* speed = CCSpeed::create(seq, 1.0f);
    speed->setTag(JumpTag);
    delegate->s->runAction(speed);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(BeatEffect::updateAnimation), this, 0.0f,false);
    delegate->isFirstDropBack = false;
}

void BeatEffect::beHitFloatScrollDwon(CCCallFuncO* callback,int groundH,int dis,int secdis,float firtime,float sectime,float stdspace,float redtime,int sufferDelay)
{
    ARPG* delegate = dynamic_cast<ARPG*>(m_delegate);
    if(!delegate && delegate->s)
        return;
    delegate->stopAllActions();
    delegate->s->stopAllActions();
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BeatEffect::updateAnimation), this);
    
    int _dis = secdis;//落地回弹的水平位移
    m_attackType = kAttack_beHitFloatScrollDown;
    m_distanceX += dis;
    m_beAttackDelay = sufferDelay;
    m_reduceSpeed = redtime;
    CCPoint pos = delegate->s->getPosition();
    CCPoint pos2 = delegate->getPosition();
    m_origiPos = m_origiPos.equals(ccp(ULONG_MAX,ULONG_MAX)) ? pos : m_origiPos;
    m_intGroundH = groundH;
    m_addedGroundH += groundH;
    CCPoint firstPos,secondPos;//两次浮空的位置
    if(direction == DHERO_RIGHT)
    {
        firstPos = ccp(pos.x + (dis - _dis),0);
        secondPos = ccp(firstPos.x + _dis,0);
        m_newNodePos = ccp(pos2.x + dis,pos2.y);
        delegate->s->setScaleX(-1);
    }
    else
    {
        firstPos = ccp(pos.x - (dis - _dis) ,0);
        secondPos = ccp(firstPos.x - _dis,0);
        m_newNodePos = ccp(pos2.x - dis,pos2.y);
        delegate->s->setScaleX(1);
    }
    CCJumpTo* jump = CCJumpTo::create(firtime, firstPos,groundH,1);//第一次浮空，
    CCJumpTo* jump2 = CCJumpTo::create(sectime, secondPos, BOUNCEHIGHT, 1);//落地回弹
    CCDelayTime* delay = CCDelayTime::create(m_beAttackDelay * MINFRAMESPACE);
    CCDelayTime* delay2 = CCDelayTime::create(stdspace);
    CCCallFuncO* doScroll = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::doScrollByVertical),NULL);
    CCCallFuncO* doStand = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::doActionsByTag), CCStringMake(ANIMATION_STAND));//站立
    CCCallFuncO* stopScroll = CCCallFuncO::create(delegate,callfuncO_selector(ARPG::stopScrollByVertical),NULL);//停止旋转
    CCCallFuncO* behit = CCCallFuncO::create(this, callfuncO_selector(BeatEffect::doShakeLeftAndRight), NULL);
    if(!jump || !delay || !doScroll || !jump2 || !doStand || !stopScroll || !behit)
        return ;
    CCSequence* seq = CCSequence::create(behit,delay,doScroll,jump,stopScroll,jump2,delay2,doStand,callback,NULL);
    CCSpeed* speed = CCSpeed::create(seq, 1.0f);
    speed->setTag(kAnimation_tag_Jump);
    speed->setTag(JumpTag);
    delegate->s->runAction(speed);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(BeatEffect::updateAnimation), this, 0.0f,false);
    delegate->isFirstDropBack = false;
}


void BeatEffect::cleanMemenbers()
{
    m_intGroundH = 0;
    m_origiPos = ccp(ULONG_MAX,ULONG_MAX);
    m_addedGroundH = 0;
    incrementY = 0;
    m_distanceX = 0;
}


