//
//  TipStory2.h
//  ooo
//
//  Created by mac on 14-6-4.
//
//

#ifndef __ooo__TipStory2__
#define __ooo__TipStory2__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
#include "Define.h"
#include "Hero.h"
#include "GameScene.h"
#include "Monster.h"
#include "Boss.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

class TipStory2 : public CCLayer
{
public:
   
    static CCScene* scene();
    static TipStory2* create();
    bool init();
    void initHero();
    void crazy();
    void initNvRole(float dt);
    void fixFocus();
    void screenMove();
    void tip1();
    void tip2();
    void tip3();
    void tip4(float dt);
    void tip5(float dt);
    void tip6(float dt);
    void tip7(float dt);
    void tip8(float dt);
    void duihua(float dt);
    void addTips();
    void addTip1();
    void addTip3();
    void resetTip1();
    void resetTip2();
    void addTip2();
    void setText1();
    void setText2();
    void qianqian(float dt);
    void fadeAllErole(float dt);
    void screenMove2();
    void resetPosition();
    void resetPosition2();
    void GameStart(float dt);
    ~TipStory2();
private:
    CCSprite* bg;
    CCLayerColor* bg2;
    CCSprite* tip11;
    CCSprite* tip01;
    UILabel* label;
    UILabel* label2;
    bool canSay;
    CCSprite* nvRoleHead;
    CCSprite* roleHead;
    CCSprite* blackRoleHead;
    Hero* hero;
    Hero* hero2;
    Monster* monster;
    CCArmature* nvRole;
    int currentduihua_index;
};
#endif /* defined(__ooo__TipStory2__) */
