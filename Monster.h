//
//  Monster.h
//  King
//
//  Created by mac on 14-3-27.
//
//

#ifndef __King__Monster__
#define __King__Monster__

#include "ARPG.h"
#include "State.h"
#include "StateMachine.h"
#include "Prop.h"
#include "BloodBar.h"


class Monster :public ARPG
{
protected:
    StateMachine<Monster>*  m_pStateMachine;
public:
    Monster();
    
    virtual ~Monster();

    static Monster* create(int id,int mapIndex);
    
    bool init(int id,int mapIndex);
    
    bool initAttr();
    
    virtual bool initPosition();
    
    bool initBloodBar();
    
    void stand();
    
    void move();
    
    void moveCallback(CCObject* pSender);
    
    bool isToWander();   //是否可以徘徊巡逻 小怪重写，大怪重写
    
    virtual void attack();
    
    bool isAttack();
    
    bool inAIRange();
    
    void atkNpc(int Direction);	/** 攻击 */
    
    virtual void wander();
    
    virtual void WanderCallback();
    
    virtual float getNextPosx();
    
    virtual bool canAttack();
    
    bool inAttackRange();
    
    virtual void attackM1();
    
    virtual void attackM2();
    
    virtual void attackM3();
    
    virtual void SeekRole();
    
    void SeekRoleCallback(CCObject* pSender);
    
    StateMachine<Monster>*  GetFSM()const{return m_pStateMachine;} //获取当前的状态机

    virtual void update(float dt);
    
    void setSpeed(const float sp);
        
    void setInit();/** 把npc的所有特性至为初始状态 */
    
    void beAttackCallFuncO(CCObject* pSender);
    
    virtual void getUp();
    
    bool isSeekRole;
public:
   
    int delayAttackTime;
    float aiRange;  //怪物激活ai
    float attackRange;  //怪物攻击范围

    /** 判断是否换攻击状态 */
	bool isChange;
    bool isChangeATK;
    
    
    /** NPC4与NPC7的强制移动锁 */
    bool isEnforceMove;
    bool isEnforceLeft;
    bool isEnforceRight;
    
    /** 2个远程攻击的NPC 不是从中线算攻击矩阵的 所以加个远程攻击矩阵的偏移量 */
    float Atk_remote;
    
    // -----------------------npc的个性数值
	/** 数值一攻击成功英雄次数用于当攻击次数达到一定次数的时候躲避英雄的攻击一段时间 */
	int atkHeroCount;
	/** 数值二被攻击次数用于当被攻击次数达到一定的次数的时候怒气攻击 用于boss攻击特殊技能 无敌 ,以及npc的击飞 */
	int byAtkHeroCount;
 
    CCArray* prop;
    
	bool isDrive;
    /** 已经自己随机判断多少次了当达到一定次数就开始自主移动 */
	int onCount;
	/** 被攻击后npc血量小于一定数后有一定几率逃跑 */
	bool isRun;
    
    /** 当前npc是否是当前npc中的精英怪 */
	bool isElite;
    
    /** 强制攻击 */
	bool isForce;
	/** npc的画笔透明度 */
	int NpcAphla ;
	/** 是否播放死亡音效 */
	bool isPlayDie;
    
    /** boss是否出现在屏幕上 */
	bool isBoss;
	/** 怪物是否出场了 */
	bool isShow;
	/** 当前boss是否需要画血条 */
	bool isShowHead;
    
    /** 远程怪物的强制移动当怪物攻击两次后进入一段时间的移动走动状态 */
	bool isOnMove;
    int PassTime;
    int passCount;
    
    /**火枪手的特点会跟英雄碰撞后穿越过英雄的身体*/
    bool isPass;
    
    /** NPC种类 */
	int name;
    /** 杀死npc恢复能量值 */
	int NPCPOM;

    float getX();
    float getY();
    
    virtual void die();

public:
    int mapIndex;
    
    int modeID;

    float starttime;
    
    int canAttackTimes;

};


#endif /* defined(__King__Monster__) */
