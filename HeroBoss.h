//
//  HeroBoss.h
//  ooo
//
//  Created by mac on 14-6-4.
//
//

#ifndef __ooo__HeroBoss__
#define __ooo__HeroBoss__

#include <iostream>
#include "Monster.h"

class HeroBoss : public Monster
{
public:
    static HeroBoss* create();
    bool init();
    bool initPosition();
    void getUp();
    void getUpCallBack();
    void wander();
    void WanderCallback();
    float getDis();
    void skill1();
    void skill3o(CCObject* obj);
    void skill3();
    void skill4o(CCObject* obj);
    void skill4();
    void skill5();
    void skillJinShen();
    void skillJinShen2(CCObject* obj);
    void JinShen();
    void skilllianji();
    void actionSkill();
    void fadai();
    void fadaio();
    HeroBoss();
    void qianxiaqian(const char* name);
    int decide;
};
#endif /* defined(__ooo__HeroBoss__) */
