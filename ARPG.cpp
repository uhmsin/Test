//
//  ARPG.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//
#include "ARPG.h"
#include "Define.h"
#include "HubLayer.h"
#include "ShopBuy.h"
#include "Monster.h"
#include "MonsterAIState.h"
#include "PersonalAudioEngine.h"
#include "GameData.h"
#include "Prop.h"
#include "Ef.h"
ARPG::ARPG()
{
    isScrolling = false;
    isqianqian = false;
    isEffectAttack = false;
    actionID = -1;
    delegate = NULL;
    wudi = false;
    maxNuqi = 100;   //1.	上限100. 满100增加一个能量豆, 可以释放技能.
    nuqi = 0;  //2怒气
    nengliangdou = 0;
    maxNengliangdou = KingData->getNuqiLevel();  //英雄怒气
    buyNengliangdou = 0;   // 从商店购买的英雄怒气
    isBeAttack = false;
    type = 0;   //初始化类型0
    s = NULL;
    animation = NULL;
    this->topH = 54;
    this->bottomH = 28;
    isUnderAttack = false;
    attackType  = 1;
    safe_time = SAFE_TIME;
    oldPosition = CCPoint(0,SIZE.height/4);
    INIT = 0;
    ON_ACTION =1;
    ARPG_DIE = 99;
    ACCORD = 10;
    ACCORD_ = 11;
    OFF_ACTION = 2;
    action_place = HOLDER;
    orientation = RIGHT;
    offMove = 0;
    onMove = 1;
    abDie = false;
    isDie = false;
    is_UndoRunState = false;
    is_UndoAtkState = false;
    ationState = 0;
    shadow = NULL;
    attackRect = CCRectMake(0, 0, 0, 0);
    bodyRect = CCRectMake(0, 0, 0, 0);
    offMove = false;
    effectRect = CCRectMake(0, 0, 0, 0);
    dp = 0;
    has_hitARPG = false;
    shadow2 = NULL;
}

void ARPG::initAni(const char* rs)
{
    beatEffects = CCArray::create();
    beatEffects->retain();
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,rs,rs);
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    s = CCArmature::create(rs);
    s->setAnchorPoint(ccp(0.5,0));
    addChild(s,1000);
    animation = s->getAnimation();
    schedule(schedule_selector(ARPG::updateAttackRect), 0.016f);
    if(this->type==1)
    {
        s2 = CCArmature::create(rs);
        s2->setAnchorPoint(ccp(0.4,0));
        this->addChild(s2,1000);
        s2->setVisible(false);
    }
}

void ARPG::stand()
{
    if(isqianqian)
    {
        return;
    }
    if(this->isBeAttack)
    {
        return;
    }
    s->stopAllActions();
    m_state = s_stand;
    setAction(0);
    if(is_UndoAtkState == false)
    {
    
    }
}

void ARPG::flipDir()
{
    switch (this->orientation)
    {
        case LEFT:
            this->s->setScaleX(-1);
            break;
        case RIGHT:
            this->s->setScaleX(1);
            break;
        default:
            break;
    }
}

void ARPG::move()
{
    if(this->isBeAttack)
    {
        return;
    }
    s->stopAllActions();
    setAction(1);
    flipDir();
}

CCRect ARPG::getBondingBox()
{
    CCRect rect;
    rect.origin =  gameLayer->convertToNodeSpace(this->convertToWorldSpace(this->bodyRect.origin));
    rect.size = CCSize( this->bodyRect.size.width,  this->bodyRect.size.height);
    return rect;
}

CCRect ARPG::getBondingBox2()
{
    CCRect rect;
    rect.origin =  this->convertToWorldSpace(this->bodyRect.origin);
    rect.size = CCSize( this->bodyRect.size.width,  this->bodyRect.size.height);
    return rect;
}

CCRect ARPG::getZuDangBox()
{
    CCRect rect;
    rect.origin =  gameLayer->convertToNodeSpace(this->convertToWorldSpace(ccpAdd( this->getPosition(), ccp(0.98*this->s->getPositionX(),0))));
    rect.size = this->attackRect.size;
    rect.origin = ccpSub(rect.origin,ccp(rect.size.width/2,rect.size.height/2));
    
    
  
    return rect;
}

CCRect ARPG::getAttackBox()
{
    CCRect rect;
    rect.origin =  gameLayer->convertToNodeSpace(this->convertToWorldSpace(this->attackRect.origin));
    rect.size = this->attackRect.size;
    
   // ccDrawRect(rect.origin, ccpAdd(rect.origin, ccp(rect.size.width, rect.size.height)) );

    return rect;
}

void ARPG::draw()
{

}

void ARPG::suffer(ARPG* attcker,int attackType)
{
    if (this->type == 2)
    {
        int ran = CCRANDOM_0_1()*100;
        if (this->s->getPositionY() < 10.0f&& ran < 40 && this->id == 11 && Role->commanAttackIndex == 3 && Role->isCommanAttack)
        {
            this->stopAllActions();
            this->s->stopAllActions();
            this->s->setPosition(ccp(0, 0));
            this->beAttackCallFuncO(this);
            this->isBeAttack = false;
            return;
        }
    }
    
    if(this->actionID == 4 && attcker->getAttackType() != 9)
    {
        return;
    }
    if(this->getBeAttackType() == 4 && this->s->getPositionY()>1)
    {
        return;
    }
    m_state = s_stand;
    if (this->isDie)
    {
        return;
    }
   
    int ran = CCRANDOM_0_1()*3;
    
    if (Role->m_state != s_skill ) {
        
        switch (ran)
        {
            case 0:
            {
					  PersonalAudioEngine::sharedEngine()->playEffect("music/quan-mingzhong-zhong.mp3"/*.wav*/);
                break;
                
            }
            case 1:
            {
					  PersonalAudioEngine::sharedEngine()->playEffect("music/quan-mingzhong-qing.mp3"/*.wav*/);
                break;
            }
            case 2:
            {
					  PersonalAudioEngine::sharedEngine()->playEffect("music/quan-mingzhong-qing.mp3"/*.wav*/);
                break;
            }
            default:
                break;
        }
    }

    if(this->type == 1)
    {
        Role->daodiTime = 20;
        if (Role->isqianqian)
        {
            Role->isqianqian = false;
            Role->stopAllActions();
        }
        if(Role->getChildByTag(qianxiaqianEffectTag))
        {
            Role->removeChildByTag(qianxiaqianEffectTag);
        }
        if(this->isBeAttack && this->s->getPositionY()>0)
        {
            return;   //主角受到攻击，并且主角得浮空值大于0，主角无敌
        }
        this->safe_time = 6*SAFE_TIME;
        if(this->nuqi + KingData->getExtraNuqi() >(this->maxNengliangdou)*100 + 99)
        {
            
        }else
        {
			//被攻击
            this->nuqi +=5;  //3.受到一次攻击伤害 增加怒气5.
        }
        float randx = CCRANDOM_0_1();
        if(randx<0.2)
        {
           PersonalAudioEngine::sharedEngine()->playEffect("music/zhushouji.mp3");
        }
        this->hitEffect();
    }
    else       
    {
        
        HUB->AddLianJi();
        if(attcker->m_state == s_attack)
        {
             if(attcker->nuqi + KingData->getExtraNuqi() >(attcker->maxNengliangdou)*100 + 99)
             {
                 
             }else
             {
				 //攻击
                  attcker->nuqi +=2; //4.攻击敌人一次  增加怒气10.(技能攻击不算)
             }
        }
        this->safe_time  = 20;
        if(attcker->actionID == 7 ||attcker->actionID == 25)
        {
            this->safe_time  = 25;
        }
        if(attcker->getAttackType() > 6 && attcker->getAttackType() < 9)
        {
            this->safe_time = 0;
        }
        if(attcker->getAttackType() == 10)
        {
            this->safe_time = 0;
        }
        
        Monster* monster = dynamic_cast<Monster*>(this);
        monster->GetFSM()->ChangeState(MonsterBeAttackState::Instance());
    }
    
    
    if (this->type == 1)
    {
        BeatEffect* beat;
        
        int ran = CCRANDOM_0_1()*100;
        
        if (attackType == 11)
        {
            
        }else if(ran < 3 && (attcker->getAttackType() ==1 ||attcker->getAttackType() ==7||attcker->getAttackType() ==8 ))
        {
            attcker->setAttackType(2);
        }
        if(attcker->getPositionX() > this->getPositionX())
        {
            beat = BeatEffect::create(this,attcker->getAttackType(),DHERO_LEFT);
        }
        else
        {
            beat = BeatEffect::create(this,attcker->getAttackType(),DHERO_RIGHT);
        }
  
    }else
    {
        bool hasBati_true = false;
        Monster* monster = dynamic_cast<Monster*>(this);
        if(monster->hasBati)
        {
            if (CCRANDOM_0_1() < 0.3)
            {
                hasBati_true = true;
            }
        }
        
        if (hasBati_true)
        {
            if( this->actionID >= 5  &&Role->m_state!= s_skill &&   this->isBeAttack == false  && this->s->getPositionX() < 0.01 && this->s->getPositionY() < 0.01)
            {
                
                monster->GetFSM()->ChangeState(MonsterInitState::Instance());
            }else
            {
                BeatEffect* beat;
                if (attackType == 11)
                {
                    
                }else if(this->s->getPositionY() > 0.5 && (attcker->getAttackType() ==1 ||attcker->getAttackType() ==7||attcker->getAttackType() ==8 ))
                {
                    attcker->setAttackType(2);
                }
                if(attcker->getPositionX() > this->getPositionX())
                {
                    beat = BeatEffect::create(this,attcker->getAttackType(),DHERO_LEFT);
                }
                else
                {
                    beat = BeatEffect::create(this,attcker->getAttackType(),DHERO_RIGHT);
                }
                if(this->actionID!=4)
                {
                    hitEffect();
                }
            }
            
        }else
        {
            BeatEffect* beat;
            if (attackType == 11)
            {
                
            }else if(this->s->getPositionY() > 0.5 && (attcker->getAttackType() ==1 ||attcker->getAttackType() ==7||attcker->getAttackType() ==8 ))
            {
                attcker->setAttackType(2);
            }
            if(attcker->getPositionX() > this->getPositionX())
            {
                beat = BeatEffect::create(this,attcker->getAttackType(),DHERO_LEFT);
            }
            else
            {
                beat = BeatEffect::create(this,attcker->getAttackType(),DHERO_RIGHT);
            }
            if(this->actionID!=4)
            {
                hitEffect();
            }
            
       
            
        }
//        this->removeFromParent();
    }
    
    if(this->type == 1)
    {
        int attackpp =   attcker->attackP*(1-0.06*this->getDP());
        this->delHp(attackpp);
    }else
    {
        if (Role->skill3AnimationId > 0 && this->getIsEffectAttack())
        {
            this->delHp(2*CCUserDefault::sharedUserDefault()->getIntegerForKey("heroAtk"));
            
          //  this->delHp(100);
            
        }else
        {
            
          //   this->delHp(100);
            if (Role->skill2AnimationId >101 &&Role->isSkill2 ) {
                this->delHp(2*Role->getAttackP());

            }else if (Role->skillAnimationId >11 && Role->isSkill1)
            {
                 this->delHp(2*Role->getAttackP());
            }else
            {
                 this->delHp(Role->getAttackP());
            }
        }
    }

    this->setBeAttackType(attcker->getAttackType());
}

void ARPG::hitEffect()
{
    Ef* ef;
    if(Role->isCommanAttack)
    {
         ef = Ef::create("tx_shouji3");
    }else
    {
         ef = Ef::create("tx_shouji2");
    }
    ef->setPositionY(this->s->getContentSize().height/2+this->bottomH);
    this->addChild(ef,10000);
    ef->setScaleX(Role->s->getScaleX());
}

void ARPG::attackEffect(CCPoint p)
{
    Ef* ef = Ef::create("tx_shouji1");
    ef->setPositionY(this->s->getContentSize().height/2+this->bottomH+ p.y);
    ef->setPositionX(this->s->getScaleX()*p.x + this->s->getScaleX()* this->s->getContentSize().width*0.4);
    if(this->actionID == 4)
    {
        ef->setRotation(90);
        ef->setPositionY(this->bottomH + p.y);
    }
    this->addChild(ef,10000);
    ef->setScaleX(Role->s->getScaleX());
}

void ARPG::skillEffect(CCPoint p,int index)
{
    Ef* ef = Ef::create("tx_xiazhua",index);
    ef->setPositionY(this->s->getContentSize().height/2+this->bottomH+ p.y);
    ef->setPositionX(this->s->getScaleX()*p.x + this->s->getScaleX()* this->s->getContentSize().width*0.4);
    if(this->actionID == 4)
    {
        ef->setRotation(90);
        ef->setPositionY(this->bottomH + p.y);
    }
    this->addChild(ef,10000);
    ef->setScaleX(this->s->getScaleX());
}

void ARPG::attackJiangzhi()
{
    Role->s->pauseSchedulerAndActions();
    Role->s->getAnimation()->pause();
    Role->pauseSchedulerAndActions();
    CCDelayTime* delay = CCDelayTime::create(0.032*6);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameScene::resumeJiangzhi));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    this->runAction(seq);
}

void ARPG::resumeJiangzhi(CCObject* pSender)
{
    Role->s->resumeSchedulerAndActions();
    Role->s->getAnimation()->resume();
    Role->resumeSchedulerAndActions();
}

void ARPG::delHp(int shp)   //精灵掉血逻辑
{
    int shhp = shp + CCRANDOM_MINUS1_1()*10;
 
    HUB->addDamageNum(shhp, gameLayer->convertToWorldSpace(ccpAdd(this->getPosition(), ccp(0, this->s->getContentSize().height*0.75)) ) , -1*this->s->getScaleX());
    this->hp -= shhp;
    if (this->type == 1)
    {
        HUB->showHP(this->maxHp, this->hp);//血条显示掉血逻辑
    }
    
    if (this->type != 1 && bloodbar !=NULL)
    {
        bloodbar->processPlayerHP();
    }
    if(this->hp <= 0)
    {
        this->die();
    }
  
    
}

void ARPG::die()
{
}

bool ARPG::isFight(ARPG* p)
{
    if(p->wudi)
    {
        return false;
    }
    if(p->s->getPositionY() > p->s->getContentSize().height )
    {
        return false;
    }
    
    if (p->safe_time>0 )
    {
        return false;
    }
    return true;
}

void ARPG::setAction(int actID)
{
    int animationNum =  animation->getMovementCount();
    if (animation == NULL ||animationNum ==0 )
        return;
    if (actID <0 || actID > animationNum)
    {
        actID = 0;
    }
    if (this->actionID!=actID)
    {
        this->actionID = actID;
        animation->playWithIndex(actionID);
    }
}

void ARPG::setAction(int actionID,int times)
{
    int animationNum =  animation->getMovementCount(); //动画数
    if (animation == NULL ||animationNum ==0 )
        return;
    if (actionID <0 || actionID > animationNum)
    {
        actionID = 0;
    }
    if (this->actionID!=actionID)
    {
        this->actionID = actionID;
        this->animation->setMovementEventCallFunc(this, SEL_MovementEventCallFunc(&ARPG::actionCallback));    //动画完成后的回调
        animation->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&ARPG::collison));
        if(times == 1 ||times == 0)
        {
            animation->playWithIndex(actionID,-1,-1,0);    //攻击一次不循环
        }
        else
        {
            animation->playWithIndex(actionID,-1,-1,times);    //攻击一次不循环
        }
    }
}

void ARPG::collison( CCBone * bone , const char * evt, int originFrameIndex, int currentFrameIndex )
{
    if(strcmp(evt, "-1")   == 0)
    {
        if (delegate !=NULL)
        {
            Role->hasCollisionNum = 0;
            this->delegate->actionDidAttack(this);
        }
    }
}

void ARPG::actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID)
{
    if (eventType == START) {
        this->setZOrder(10000);
    }
    if (eventType == COMPLETE)
    {
        this->setZOrder(0);
        if(delegate)
        {
            delegate->actionDidAttack(this);
        }
        if(this->type!= 1)
        {
            if(this->actionID !=1)
            {
                this->setAction(1);
            }
        }else
        {
            if(this->actionID !=0)
            {
                this->setAction(0);
                m_state = s_stand;
                isBeAttack =false;
            }
        }
        this->setAction(0);
        this->setZOrder(0);

    }
    if (eventType == LOOP_COMPLETE)
    {
       
    }
}

void ARPG::doActionsByTag(CCObject* pSender)//根据m_tag播放动画
{
    if (this->type == 2 && this->actionID == 7) {
        return;
    }
    
    
    CCString* str = dynamic_cast<CCString*>(pSender);
    const char* name = ANIMATION_STAND;
    if(str)
        name = str->getCString();
  
    if(strcmp(name,ANIMATION_BEATBACK) == 0 && strcmp(name,m_animationName.c_str()) != 0)
    {
        m_animationName = ANIMATION_BEATBACK;
        setAction(2);
    }
    else if( strcmp(name,ANIMATION_ATTACKWARNING) == 0 && strcmp(name,m_animationName.c_str()) != 0)
    {
        m_animationName = ANIMATION_ATTACKWARNING;
    }
    else if(strcmp(name,ANIMATION_UPFLOAT) == 0 && strcmp(name,m_animationName.c_str()) != 0)
    {
        m_animationName = ANIMATION_UPFLOAT;
        setAction(3);
    }
    else if(strcmp(name,ANIMATION_DOWNFLOAT) == 0 && strcmp(name,m_animationName.c_str()) != 0)
    {
        m_animationName = ANIMATION_DOWNFLOAT;
        setAction(4);
    }
    else if(strcmp(name,ANIMATION_GETDOWN) == 0 && strcmp(name,m_animationName.c_str()) != 0)
    {
        m_animationName = ANIMATION_GETDOWN;
        setAction(4);
    }
    else if(strcmp(name,ANIMATION_STAND) == 0 && strcmp(name,m_animationName.c_str()) != 0)
    {
        m_animationName = ANIMATION_STAND;
        isBeAttack = false;
        if(this->isDie)
        {
            this->removeTo();
        }else
        {
            if (this->getBeAttackType() == 1 ||this->getBeAttackType() == 7|| this->getBeAttackType() == 8 ) {
                this->beAttackCallFuncO1(this);
                setAction(0);
            }else{
                this->beAttackCallFuncO(this);
            }
        }
        isUnderAttack = false;
    }
}

void ARPG::removeTo()
{
    if(this->type != 1)
    {
        setAction(4);
        Monster* arpg = dynamic_cast<Monster*>(this);
        arpg->GetFSM()->ChangeState(MonsterDeadState::Instance());
        this->s->getAnimation()->playWithIndex(4);
        this->unscheduleAllSelectors();
        this->stopAllActions();
        this->s->stopAllActions();
        CCFadeIn* fade = CCFadeIn::create(2.0f);
        CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(ARPG::removeCallback));
        CCSequence* seq = CCSequence::create(fade,func,NULL);
        this->runAction(seq);
        this->s->runAction(fade);
        this->dropProp();
    }
}

void ARPG::removeCallback()
{
    this->removeFromParentAndCleanup(true);
    gameLayer->npc->removeObject(this);
}

void ARPG::dropProp()
{
    int Random = CCRANDOM_0_1()* 16 ;
    
    if (Random <  gameLayer->id)
    {
        return;
    }
    float Random1  = CCRANDOM_0_1();
    float Random2  = CCRANDOM_0_1();
    float Random3  = CCRANDOM_0_1();
    
    if (Random1 < 0.15)
    {
		//血瓶道具回复
        //Prop* prop = Prop::create(1, Role->getMaxHp()/4);
		Prop* prop = Prop::create(1, Role->getMaxHp() / 10);
        gameLayer->addChild(prop,90000000);
        gameLayer->props->addObject(prop);
        prop->setPosition(ccpAdd(this->getPosition(), this->s->getPosition()) );
        prop->setPositionY(SIZE.height/4 );
        prop->setPositionX(prop->getPositionX() + CCRANDOM_MINUS1_1() * 40);
    }
    if(Random2 < 0.5)
    {
		//怒气道具
        Prop* prop= Prop::create(2,10);//50
        gameLayer->addChild(prop,900000000);
        gameLayer->props->addObject(prop);
        prop->setPosition(ccpAdd(this->getPosition(), this->s->getPosition()) );
        prop->setPositionY(SIZE.height/4 );
        prop->setPositionX(prop->getPositionX() + CCRANDOM_MINUS1_1() * 40);
    }
    
    if(Random3 < 0.15)
    {
        int moneyNum =  CCRANDOM_0_1()*49 + 50;
        Prop* prop= Prop::create(3,moneyNum);
        gameLayer->addChild(prop,900000000);
        gameLayer->props->addObject(prop);
        prop->setPosition(ccpAdd(this->getPosition(), this->s->getPosition()) );
        prop->setPositionY(SIZE.height/4 );
        prop->setPositionX(prop->getPositionX() + CCRANDOM_MINUS1_1() * 40);
    }
}

void ARPG::update(float dt)
{
    
    //如果这个
}

void ARPG::updateAttackRect(float dt)
{
    CCDictionary* dic = s->getBoneDic();
    CCDictElement *element = NULL;
    CCDICT_FOREACH(dic, element)
    {
        CCBone *bone = static_cast<CCBone*>(element->getObject());
        CCArray *bodyList = bone->getColliderBodyList();
        CCObject *object = NULL;
        CCARRAY_FOREACH(bodyList, object)
        {
            ColliderBody *body = static_cast<ColliderBody*>(object);
            CCArray *vertexList = body->getCalculatedVertexList();
            float minx, miny, maxx, maxy = 0;
            int length = vertexList->count();
            for (int i = 0; i<length; i++)
            {
                CCContourVertex2 *vertex = static_cast < CCContourVertex2*>(vertexList->objectAtIndex(i));
                if (i == 0)
                {
                    minx = maxx = vertex->x;
                    miny = maxy = vertex->y;
                }else
                {
                    minx = vertex->x < minx ? vertex->x : minx;
                    miny = vertex->y < miny ? vertex->y : miny;
                    maxx = vertex->x > maxx ? vertex->x : maxx;
                    maxy = vertex->y > maxy ? vertex->y : maxy;
                    if (minx!=0||maxx!=0)
                    {
                        CCPoint orgin = ccp(minx,miny);
                        attackRect.origin = orgin;
                        attackRect.size = CCSize(maxx-minx,maxy-miny);
                        if(this->s->getAnimation()->getCurrentFrameIndex()==0)
                        {
                            bodyRect.origin = orgin;
                            bodyRect.size = CCSize(maxx-minx,maxy-miny);
                        }
                    }
                }
            }
        }
    }
}

void ARPG::updateTopAndBottom(float dt)   //更新上下边缘
{
    
}

void ARPG::beAttackCallFuncO(CCObject* pSender)
{
    if( this->getType()!= 1)
    {
        setAction(0);
        Monster* monster = dynamic_cast<Monster*>(this);
        monster->GetFSM()->ChangeState(MonsterInitState::Instance());
    }else
    {
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::daodiqishen));
        this->runAction(call);
    }
}

void ARPG::beAttackCallFuncO1(CCObject* pSender)
{
    if( this->getType()!= 1)
    {
        Monster* monster = dynamic_cast<Monster*>(this);
        monster->GetFSM()->ChangeState(MonsterInitState::Instance());
    }
}

void ARPG::beAttackFlyCallFuncO(CCObject* pSender)
{
    
}

void ARPG::doScrollByVertical(CCObject* pSender)
{
//    if(hasScheduled)
//        return;
    isScrolling = true;
    s->setRotationX(180);
    origiAnchor = origiAnchor.equals(ccp(ULONG_MAX,ULONG_MAX)) ? s->getAnchorPoint() : origiAnchor;
    if(orientation == DHERO_LEFT)
        s->setAnchorPoint(ccp(0.5f,1.0f));
    else
        s->setAnchorPoint(ccp(0.5f,1.0f));
    schedule(schedule_selector(ARPG::doUpdateScroll),0.04f);
}

void ARPG::stopScrollByVertical(CCObject* pSender)
{
    isScrolling = false;
    isFirstDropBack = true;
    s->setAnchorPoint(ccp(0.5,0));
    s->setRotation(0);
    unschedule(schedule_selector(ARPG::doUpdateScroll));
}

void ARPG::stopScrollByVertical2()
{
    isScrolling = false;
    isFirstDropBack = true;
    s->setAnchorPoint(ccp(0.5,0));
    s->setRotation(0);
    unschedule(schedule_selector(ARPG::doUpdateScroll));
}

void ARPG::doUpdateScroll(float dt)
{
    if(s)
    {
        isScrolling = true;
        int tem = scheduleCount % 2;
        float scale1 = s->getScaleX();
        origiScale = origiScale != ULONG_MAX ? origiScale : scale1;
        if(tem == 1)
        {
            s->setRotationY(180);
        }
        else
        {
            s->setRotationY(0);
        }
        scheduleCount ++;
    }
}