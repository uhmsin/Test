//
//  Boss.h
//  King
//
//  Created by mac on 14-3-31.
//
//

#ifndef __King__Boss__
#define __King__Boss__
#include "Monster.h"
class Boss1 : public Monster
{
public:
    static Boss1* create();
    
    bool init();
    
    virtual void attackM1();
    
    virtual void attackM2();
    
    virtual void attackM3();
    
    void attack();
    
    void SeekRole();
    
    void SeekRoleCallback();
    
    bool inAttackRange();
    
    void getUp();
    
    void getUpCallBack();
    
    int seekTime;
    
    int oldeseekTime;
    
    bool canAttack();
    
    void wander();
    
    void WanderCallback();
    
    void die();
};

class Boss2 : public Monster
{
public:
    void getUp();
    
    void getUpCallBack();
    
    static Boss2* create();
    
    bool init();
    
    virtual void attackM1();
    
    virtual void attackM2();
    
    virtual void attackM3();
    
    int seekTime;
    int oldeseekTime;
    void attackM4();
    void attack();
    void wander();
    void WanderCallback();
    bool canAttack();
    void SeekRole();
    void actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID);
    void die();
};

class Boss4 : public Monster
{
public:
    void getUp();
    
    void getUpCallBack(CCObject* pSender);
    
    static Boss4* create();
    
    bool init();
    
    virtual void attackM1();
    
    virtual void attackM2();
    
    virtual void attackM3();
    
    int seekTime;
    int oldeseekTime;

    void attack();
    void wander();
    void WanderCallback();
    bool canAttack();
    void SeekRole();
    void actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID);
    void die();
};
#endif /* defined(__King__Boss__) */
