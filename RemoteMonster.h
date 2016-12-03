//
//  RemoteMonster.h
//  king04
//
//  Created by mac on 14-5-7.
//
//

#ifndef __king04__RemoteMonster__
#define __king04__RemoteMonster__

#include "Monster.h"
#include "Define.h"
class RemoteMonster : public Monster
{
public:
    static RemoteMonster* create();
    
    bool init();
    
    virtual void attackM1();
    
    virtual void attackM2();
    
    virtual void attackM3();
    
    void wander();
    
    void WanderCallback();
    
    float getNextPosx();  //获取要冲的x
    
    bool canAttack();
    
    int gongjiJianGE;
    
    int gongjiJianGeSHU;
};

#endif /* defined(__king04__RemoteMonster__) */
