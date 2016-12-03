//
//  Hero.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef __King__Hero__
#define __King__Hero__

#include "ARPG.h"
class Ef;
class Hero : public ARPG
{
public:
    int hasCollisionNum;
    
    void zadiShengyin(float dt);
    
    CREATE_FUNC(Hero);
    bool init();
    void update(float dt);
	int skill_time = 0;

	int m_useSkill = 0;

    void commanAttack();
    int state;
    void autoNormalAttact(); //当前攻击时间  － 上次攻击的时间 > 安全时间    coding
    void setIsARPG_Acion(int ARPG_Acion); 	/** 设置功能键 改变当前的功能键状态 设置为-1取消功能键 */
    
    void move();

	void showInfo(int id);
	bool m_canSkill = false;
    void skill1(CCObject* pSender);
	void skill1();
    void skill2(CCObject* pSender);
	void skill2();
    void skill3(CCObject* pSender);
	void skill3();
    void skill4(CCObject* pSender);
	void skill4();
	void skill_ss(CCObject* pSender);

    void skill1Animation(float dt);
    
    void skill2Animation(float dt);

    void skill2Action(CCObject* pSender);
    
    void skill1Action();
    
    void skill3Action(CCObject* pSender);
    
    void skill4Action(CCObject* pSender);
    
    void jumpRise(int height,float time,CCPoint p,int jumpTimes);
   
    void jumpCallback();
    
    CCArmature* addMotion(CCAction* act,float time);
    
    void removeMotion(CCObject* pSender);
    
    void moveTo(CCNode* node,float dt ,float x);
    
    void zadi2();
    
    void zadi();
    
    void yanmu();
    
    void shandianqiou();
    
    void shandian(int skill3AnimationId);
    
    Ef* skill1end(const char* name,CCPoint p);
    
    void qianxiaqian(const char* name);
    
    void shop(CCObject* pSender);
    
public:
    bool isJinjiDuobi;
    
    bool isZudang;
    
    int qianqianNum;
    
    void qianqian(int dir);
    
    void qianqianCallback();
    
    void fuhuo();
    
    bool isCanDirect;
    
    Hero();
    
    ~Hero();
    
    bool isSkill1;
    
    bool isJiXuSkill1;
    
    bool isSkill2;
    
    bool isJiXuSkill2;
    
    bool isSkill3;
    
    bool isSkill4;
    
    int skill3Scale;
    
    bool isCommanAttack;
    
    bool startNormalAttact;
    
    int lastNormalAttactTime;
    
    int downCount; //方向键第几次按下了
    
    int downAtk;  //功能键第几次按下
    
    bool isOnlyHandNow; //当前是空手
    
    bool isFly;  //是否被击飞。击飞中不能
    
    int doubleHit_Type; //区分当前的连击动作类型
	
    bool isActionEnding; /** 测试当拳头攻击之后并不忙上接受而是产生一个boolan 值 */
    
    int doubleHit_Save; //保存动作结束前按下的攻击方式
    
    int atkCount; //当前点了几下，用于播放连击计算
    
    int lianjiNum;
    int lianjiTime;
    
    int skillAnimationId;
    
    int skill2AnimationId;
    
    int skill3AnimationId;
    
    int skill4AnimationId;
    
    int commanAttackIndex;
    
    void actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID);
    
    void setAction(int actionID,int times);
    
    void setAction(int actionID);
    
    void commanAttackResume(float dt);
    
    int commanAttackResumeNum;
    
    void die();
    
    void shanbi();
    
    bool isHaveFuhuo;
    
    bool isCollision;
    
    void daodiqishen();
    
    void daodiqishenCallback(CCObject* pSender);
    
    bool isdaodiqishen;
    
    int daodiqishenID;
    
    int daodiTime;
};

#endif /* defined(__King__Hero__) */
