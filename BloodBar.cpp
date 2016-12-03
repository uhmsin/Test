//
//  BloodBar.cpp
//  xiyou
//
//  Created by mac on 14-3-18.
//
//

#include "BloodBar.h"
#include "ARPG.h"
BloodBar::BloodBar(void)
{
}
bool BloodBar::init()
{
    bool ret = false;
    do {
        left = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("npc_xc_1.png"));
        left->setType(kCCProgressTimerTypeBar);
        left->setMidpoint(ccp(0,0));
        left->setBarChangeRate(ccp(1, 0));
        left->setPosition(ccp(0, 0));
        left->setAnchorPoint(ccp(0,0));
        left->setPercentage(100.0);
		CCSprite *leftBg = CCSprite::createWithSpriteFrameName("npc_xc_2.png");
        leftBg->setColor(ccc3(0, 0, 0));
        leftBg->addChild(left,2);
        addChild(leftBg);
        ret = true;
    } while (0);
    return ret;
}

BloodBar::~BloodBar(void)
{
}

void BloodBar::processPlayerHP()
{
    ARPG* p = dynamic_cast<ARPG*>(player);
    int hpPercent = p->getHPPercent();
    float progressFrom = left->getPercentage();
    float progressTo = hpPercent;
    CCProgressFromTo *to2 = CCProgressFromTo::create(0.5, progressFrom, progressTo);
    left->runAction(to2);
}
