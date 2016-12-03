//
//  Monster.cpp
//  King
//
//  Created by mac on 14-3-27.
//
//
int bottomHs[] = {28,28,/*1*/24,/*2*/36,/*3*/12,/*4*/12,/*5*/24,/*6*/30,/*7*/38,/*8*/18,/*9*/8,/*10*/25/*boss1*/,16,48,90,16};
int topHs[] = {54,54,/*1*/34,/*2*/36,/*3*/100,/*4*/28,/*5*/34,/*6*/74,/*7*/96,/*8*/16,/*9*/75,/*10*/54/*boss1*/,64,146,54,64};
//每个怪物移动速度bili
float speedRate[] = {0,1,/*1*/1,/*2*/1,/*3*/1.8/*4*/,1.8,/*5*/1.5,/*6*/1.3,/*7*/1.2,/*8*/1,/*9*/1.8,/*10*/1/*boss1*/,1,1,1,1,1};
//每一个怪的名字
//static const char* NpcName[16] = {"g0","g1","g2","g3","g4","g5","g6","g7","g8","g9","g10","boss1","boss2","boss3","boss4","boss5"};
float anchor[] = {0.5,0.35,0.35,0.35,0.35,0.4,0.5,0.4,0.35,0.35,0.35,0.35,0.35,0.45,0.35,0.35,0.5,0.35};

int hiddenLibaoIndex[] = { 2 , 7 , 11 , 15 ,19  };

#include "Monster.h"
#include "MonsterAIState.h"
#include "GameScene.h"
#include "Define.h"
#include "BeatEffect.h"
#include "Boss.h"
#include "NpcMap.h"
#include "HeroBoss.h"
#include "RemoteMonster.h"
#include "GameData.h"
Monster::Monster()
:ARPG()
{
    hasBati = false;
    canAttackTimes = 4;
    modeID = 1;
    shadow = NULL;
    isSeekRole = false;
    isDie = false;
    bloodbar = NULL;
    isBoss = false;
    isChange = false;
    atkHeroCount = 0;
    isChangeATK = false;
    isEnforceMove = false;
    isEnforceLeft = false;
    isEnforceRight = false;
    Atk_remote = 0;
    isElite = false;
    NPCPOM = 50;
    shadow2 = NULL;
    m_pStateMachine = new StateMachine<Monster>(this);
    m_pStateMachine->SetCurrentState(MonsterInitState::Instance());
    starttime = 2.8f;

}

Monster::~Monster()
{
    this->unscheduleAllSelectors();
    this->stopAllActions();
    this->s->stopAllActions();
    this->s->unscheduleAllSelectors();
    delete m_pStateMachine;
}

Monster* Monster::create(int id,int mapIndex)
{
    Monster* m ;
    switch (id) {
        case 2:
        {
            m = new RemoteMonster();
            break;
        }
        case 11:
        {
            m = new Boss1();
            break;
        }
        case 12:
        {
            m = new Boss2();
            break;
        }
        case 13:
        {
            m = new Boss1();
            break;
        }
        case 14:
        {
            m = new Boss4();
            break;
        }
        case 15:
        {
            m = new Boss2();
            break;
        }
        case 16:
        {
            m = new HeroBoss();
            break;
        }
            
        default:
        {
            m = new Monster();
            break;
        }
    }
    m->init(id,mapIndex);
    m->autorelease();
    return m;
}
bool Monster::init(int id,int mapIndex)
{
    this->id = id;
    if (mapIndex <= 2)     //前两关怪物攻击模式  普通。  难度容易
    {
        modeID = 0;
    }

    if (mapIndex >= 4 && mapIndex <= 7)
    {
        if (CCRANDOM_0_1() < mapIndex*0.05)
        {
            modeID = 1;
        }else
        {
            modeID = 0;
        }
    }
    hasBati = true;
    if (modeID == 1)
    {
        starttime = 1.5f;
        hasBati = false;
    }
    
    this->mapIndex = mapIndex;
    initAttr();
    char monsterChar[5] = {0};
    
    if (id == 16)
    {
        sprintf(monsterChar, "role1");
    }
    
    else if(id>10&&id<=14)
    {
        sprintf(monsterChar, "boss%d",id-10);
    }
    else if(id>14&&id<=15)
    {
        sprintf(monsterChar, "boss%d",id-13);
    }
    else
    {
        sprintf(monsterChar, "g%d",id);
    }
    initAni(monsterChar);
    
    if (this->modeID == 1) {
        if (this->id < 10 && this->id != 2)
        {
            //出现霸体怪物的几率
            float jilv = 0.05;
            //及时模式
            if (gameLayer->modeID == 1)
            {
                if (gameLayer->getRemainTime() < 30)
                {
                    jilv = 0.7f;
                }
            }else if (gameLayer->modeID == 3)
            {
                if (gameLayer->targetKilometer < 200)
                {
                    jilv = 0.5f;
                }else if (gameLayer->targetKilometer < 400)
                {
                    jilv = 0.3f;
                }
            }else if (gameLayer->modeID == 4)
            {
                if (gameLayer->getRemainTime() < 30)
                {
                    jilv = 0.5f;
                }else if (gameLayer->getRemainTime() < 60)
                {
                    jilv = 0.2f;
                }
            }else if (gameLayer->modeID == 2)
            {
                if (gameLayer->killMonsterNum >6) {
                    jilv = 0.4f;
                }else if (gameLayer->killMonsterNum > 10)
                {
                    jilv = 0.7f;
                }
            }
            
            if (CCRANDOM_0_1() < jilv)
            {
                hasBati = true;
                
                if (CCRANDOM_0_1() < 0.5) {
                    this->s->setColor(ccc3(233, 177, 0));
                }else
                {
                    this->s->setColor( ccc3(99, 255, 128));
                }
                this->speedMain = 1.5*this->speedMain;
                this->setHP(this->getHP()*1.5);
                this->attackRange = 1.2*this->attackRange;
            }
        }

    }
    maxHp = hp;           //最大血量
    initBloodBar();
    initPosition();
    this->scheduleUpdate();
    this->type = 2;

    
    if(this->id>10)
    {
        CCArmatureDataManager::sharedArmatureDataManager()->purge();
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("effect/tx_jiaodi/tx_jiaodi.ExportJson");
        shadow = CCArmature::create("tx_jiaodi");
        shadow->getAnimation()->playWithIndex(0);
        
        if (gameLayer !=NULL)
        {
             gameLayer->addChild(shadow);
        }
        shadow->setPosition(this->getPosition());
        shadow->setAnchorPoint(ccp(0.5 + this->s->getScaleX()*0.3,0));
        shadow->getAnimation()->setSpeedScale(0.6f);
    }else
    {
        shadow2 = CCSprite::createWithSpriteFrameName("yingzi.png");
        
        if (gameLayer !=NULL)
        {
            gameLayer->addChild(shadow2);
        }
        
        shadow2->setPosition(this->getPosition());
    }
    if(this->id ==1)
    {
        this->s->setAnchorPoint(ccp(0.35,0));
    }
    return true;
}

bool Monster::initAttr()
{
	int m_mapIndex = mapIndex;
	if (m_mapIndex!= 0 && gameLayer->m_isTwo)
	{
		m_mapIndex = 2;
	}

    this->speedMain = 100;
    this->speedMain = speedRate[id] * this->speedMain;
    this->isDie = false;
    if (this->id == 16)
    {
        this->topH = 50;
    }else
    {
        this->topH = topHs[id];
    }

    if (id == 16) {
        this->bottomH = 10;
    }else
    {
        this->bottomH = bottomHs[id];
    }

    if(this->id<=10)
    {
		hp = mapMonsterHP[m_mapIndex - 1];
    }else
    {
		hp = 5 * mapMonsterHP[m_mapIndex - 1];
    }

    maxHp = hp;           //最大血量
	attackP = mapMonsterAttackP[m_mapIndex - 1];
    if (this->id > 10)
    {
		attackP = 1.5*mapMonsterAttackP[m_mapIndex - 1];
    }
    
    this->attackPP = this->attackP;
    this->aiRange = 300;
    this->attackRange = 150;
    
    if (id == 9)
    {
       this->attackRange = 80;
    }
    else if(this->id==2)
    {
		this->attackRange = 500;
    }
    
    if (this->id == 16)
    {
        hp = 400000;
        attackP = 1200;
        attackRange = 100;
        hasBati = true;
    }
    return  true;
}

bool Monster::initPosition()
{
    int ranf = CCRANDOM_0_1()*100; //左右随机
    float x=0;    //初始化x的位置
    if (Role !=NULL)
    {
        float role_x = Role->getPositionX();
        if(gameLayer->modeID == 3)
        {
            if (ranf > 80)
            {
                x = role_x - 0.8*SIZE.width;
                
            }else
            {
                x = role_x + 0.6*SIZE.width;
            }
        }else
        {
            if (ranf > 50)
            {
                if (this->id == 2) {
                    x = role_x - 0.75*SIZE.width;
                }else
                {
                    x = role_x - 0.6*SIZE.width;
                    if (gameLayer->modeID != 3)
                    {
                        if (role_x > 2.5* SIZE.width)
                        {
                            x = 1.9* SIZE.width;
                        }
                    }
                }
                
            }else
            {
                if (this->id == 2) {
                    x = role_x - 0.75*SIZE.width;
                }else
                {
                    x = role_x + 0.6*SIZE.width;
                    if(role_x < SIZE.width/2)
                    {
                        x = 1.1*SIZE.width;
                    }
                }
            }
        }
    }
    this->setPositionY(SIZE.height/4 - bottomH);
    this->setPositionX(x);
    this->stand();
    return true;
}

bool Monster::initBloodBar()
{
    bloodbar = BloodBar::create();
    s->addChild(bloodbar);
    bloodbar->setPosition(ccp(0,s->getContentSize().height+10 - topH));
    bloodbar->bindPlayer(this);
    return true;
}

void Monster::update(float dt)
{
	
    if(this->id == 11)
    {
       if(this->actionID != 7)
       {
           this->wudi = false;
       }else
       {
           this->wudi  = true;
       }
        
       if (this->actionID == 7)
       {
          this->setAttackType(2);
       }
    }
    
    if(this->inAttackRange())
    {
        if (starttime > -0.1f)
        {
            starttime = starttime - dt;
        }
    }
    if(!this->s->getActionByTag(JumpTag) && s!=NULL)
    {
        this->s->setPositionY(0);
        this->setPositionY( SIZE.height/4 - this->bottomH );
        isFirstDropBack = true;
        s->setAnchorPoint(ccp(anchor[id],0));
        s->setRotation(0);
        if(this->id==1)
        {
            s->setAnchorPoint(ccp(0.35,0));
        }
        unschedule(schedule_selector(ARPG::doUpdateScroll));
    }
    if(!isScrolling)
    {
        s->setAnchorPoint(ccp(anchor[id],0));
    }
    this->bloodbar->setScaleX(this->s->getScaleX());
    if(shadow!=NULL)
    {
        shadow->setPositionX(this->getPositionX() + this->s->getPositionX());
        shadow->setAnchorPoint(ccp(0.5 ,0.5));
        shadow->setPositionY(this->getPositionY() + 1.2*this->bottomH);
    }else if(shadow2!=NULL)
    {
        shadow2->setPositionX(this->getPositionX() + this->s->getPositionX() );
        shadow2->setAnchorPoint(ccp(0.5 ,0.5));
        shadow2->setPositionY(this->getPositionY() + 1.2*this->bottomH);
    }
    delayAttackTime --;
    if(m_pStateMachine)
    {
        if (HUB->isTeach)
        {
            
        }else
        {
            m_pStateMachine->Update();  //状态机执行，也就是运行CurrentState的excute方法
        }
    }
    if (safe_time > 0)
    {
        safe_time--;
    }
	
}

void Monster::die()
{
    this->stopScrollByVertical2();
    this->bloodbar->removeFromParent();
    gameLayer->killMonsterNum++;
    if(shadow!=NULL)
    {
        shadow->removeFromParentAndCleanup(true);
        
    }else if(shadow2!=NULL)
    {
        shadow2->removeFromParentAndCleanup(true);
    }
    this->stopAllActions();
    this->unscheduleAllSelectors();
    if(this->isDie == false)
    {
        this->isDie = true;
        if (HUB->isTeach) {
            
        }else
        {
           gameLayer->monsterNum -- ;
        }
        
        //coding
		bool  isHiddenLibaoTanchu = true;
        /*for (int i =0 ;i< sizeof(hiddenLibaoIndex)/sizeof(int) ;i++) {
            if ( gameLayer->id ==  hiddenLibaoIndex[i] ) {
                isHiddenLibaoTanchu = true;
            }
        }*/
        
        /*if (isHiddenLibaoTanchu &&  gameLayer->killMonsterNum == 3)
        {
            gameLayer->shop2();
            KingData->setIsShenmi(true);
            CCUserDefault::sharedUserDefault()->setBoolForKey("isShenmi",true);
            CCUserDefault::sharedUserDefault()->flush();
            CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
        }*/

        if(gameLayer->monsterNum <0)
        {
            
        }else if(gameLayer->monsterNum >0)
        {
            if (gameLayer->modeID ==1 || gameLayer->modeID ==0 )
            {
                HUB->showNpcNum(gameLayer->monsterNum);
            }
            else if (gameLayer->modeID == 2)
            {
                HUB->showKillMonster();
            }
        }else
        {
            if (gameLayer->modeID == 1)
            {
                HUB->showNpcNum(gameLayer->monsterNum);
            }
            else if (gameLayer->modeID == 2)
            {
                HUB->showKillMonster();
            }
            this->scheduleOnce(schedule_selector(GameScene::Gameover),10.0f);
        }
        if(Role->getPositionX() > this->getPositionX())
        {
            if (this->id > 10)
            {
                 BeatEffect::create(this, 12, -1);
            }else
            {
                 BeatEffect::create(this, 13, -1);
            }
        }
        else
        {
            if (this->id > 10)
            {
                BeatEffect::create(this, 12, 1);
            }else
            {
                BeatEffect::create(this, 13, 1);
            }
        }
    }
}

void Monster::stand()
{
    m_state = s_stand;
    s->stopAllActions();
    setAction(0);
}

bool Monster::isToWander()   //小怪重写，大怪重写
{
    int ran =  CCRANDOM_0_1()*100;
    if (ran>80)
    {
        return true;
    }
    return false;
}

void Monster::move()
{
}

void Monster::moveCallback(CCObject* pSender)
{
    m_state = s_stand;
}

void Monster::SeekRole()
{
    if(isSeekRole == true)
    {
        return;
    }
    this->stopAllActions();
    isSeekRole = true;
    this->setAction(1);
    CCPoint target =  Role->getPosition();
    target.y = this->getPositionY();
    CCPoint curr_pos = this->getPosition();
    float value= target.x-this->getPositionX();
    if (value>0)
    {
        target = ccpSub(target,ccp(this->attackRange,0));
        this->s->setScaleX(1);   //提供一个转身方法，，需要修复血条的方向
        //  monster->bloodbar->setScaleX(-1);
    }
    else
    {
        target = ccpAdd(target,ccp(this->attackRange,0));
        this->s->setScaleX(-1);   //提供一个转身方法
        //   monster->bloodbar->setScaleX(1);
    }
    float distance = ccpDistance(curr_pos, target);
    float duration = distance/speedMain;
    CCMoveTo*  moveTo = CCMoveTo::create(duration, target);
    this->runAction(moveTo);
}

void Monster::SeekRoleCallback(CCObject* pSender)
{
    this->attackM1();
    isSeekRole = false;
}

void Monster::attack()
{
    if(Role->isDie)
    {
        return;
    }
    if(Role->wudi || gameLayer->isGameOver)
    {
        return;
    }
    int ran =  CCRANDOM_0_1()*100;
    if (!this->inAttackRange())
    {
        this->SeekRole();
    }else
    {
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

void Monster::attackM1()
{
    this->stopAllActions();
    this->setAction(5,1);
}

void Monster::attackM2()
{
    this->stopAllActions();
    this->setAction(5,1);
}

void Monster::attackM3()
{
    this->stopAllActions();
    this->setAction(5,1);
}

bool Monster::inAttackRange()
{
    int distance = this->getPositionX()+this->s->getPositionX() - Role->getPositionX()-Role->s->getPositionX();
   
    if( abs(distance)  > this->attackRange)
    {
         return false;
    }
    return true;
}

bool Monster::isAttack()
{
    int ran =  CCRANDOM_0_1()*100;
    if (ran>10)
    {
        return false;
    }
    return true;
}

bool Monster::inAIRange()
{
    return true;
}

void Monster::atkNpc(int Direction)	/** 攻击 */
{
    s->stopAllActions();
    m_state = s_attack;
}

void Monster::wander()        //在随机的移动路径里来回徘徊
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
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(Monster::WanderCallback));
    this->runAction(flipx);
}

void Monster::WanderCallback()
{
    float x = getNextPosx();
    float y = this->getPositionY();
    CCPoint curr_pos = this->getPosition();
    CCPoint next_pos = ccp(x,y);
    float distance = ccpDistance(curr_pos, next_pos);
    float duration = distance/speedMain;
    
    if (gameLayer->modeID == 3 && this->getPositionX() < Role->getPositionX() - SIZE.width/2 )
    {
        duration = duration/2;
    }
    
    duration = CCRANDOM_0_1()*0.3*duration + 0.7*duration;
    
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
    
    float delayTime = CCRANDOM_0_1()*0.2f;
    CCDelayTime* delay = CCDelayTime::create(delayTime);
    CCCallFunc* flipx = CCCallFunc::create(this,  callfunc_selector(Monster::WanderCallback));
    CCSequence* sequence = CCSequence::create(moveTo,delay,flipx,NULL);
    sequence->setTag(WanderTag);
  
    runAction(sequence);
}

float Monster::getNextPosx()  //获取要冲的x
{
    float role_x = Role->getPositionX();
    float x = CCRANDOM_0_1()*SIZE.width*0.5;

    float target_x;
    if (this->getPositionX() > role_x) {
        target_x = role_x + x ;
    }else{
        target_x = role_x - x ;
    }
  //  target_x = MIN(MAX(target_x, 50) , gameLayer->bg1->getContentSize().width);
    return target_x;
}


bool Monster::canAttack()
{
    if (Role->wudi) {
        return false;
    }
    
    if(!this->inAttackRange())
    {
        return false;
    }
    if (modeID == 0)          //第一种模式
    {
        if (starttime > 0)
        {
            return false;
            
        }else
        {
            starttime = 2.8f;
            return true;
        }
    }else if (modeID == 1)
    {
//        if (starttime > 0)
//        {
//            return false;
//            
//        }else
//        {
//            CCLOG("攻击");
//            
//            if (canAttackTimes > 0) {
//                canAttackTimes--;
//            }else
//            {
//                canAttackTimes = 4;
//                starttime = 1.5f;
//            }
//            return true;
//        }
        
        if( CCRANDOM_0_1() * 100 > (60 - 3*gameLayer->id) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}


float Monster::getX()
{
    return this->getPositionX();
}

float Monster::getY()
{
    return this->getPositionY();
}

void Monster::setInit()/** 把npc的所有特性至为初始状态 */
{
    
}

void Monster::setSpeed(const float sp) /** 设置npc的移动 */
{
    this->speedMain = sp;
}

void Monster::beAttackCallFuncO(CCObject* pSender)
{
    Monster* monster = dynamic_cast<Monster*>(this);
    if(this->id == 11)
    {
        if (CCRANDOM_0_1()>0.8) {
            this->wudi = true;
            monster->GetFSM()->ChangeState(MonserFallUpState::Instance());
        }else
        {
            monster->GetFSM()->ChangeState(MonsterInitState::Instance());
        }
    }else if (this->id > 11)
    {
        this->wudi = true;
        monster->GetFSM()->ChangeState(MonserFallUpState::Instance());
    }
    
    else
    {
        monster->GetFSM()->ChangeState(MonsterInitState::Instance());
    }
}

void Monster::getUp()
{
    
}

