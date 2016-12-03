//
//  TipStory3.h
//  ooo
//
//  Created by mac on 14-6-5.
//
//

#ifndef __ooo__TipStory3__
#define __ooo__TipStory3__

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

class TipStory3 : public BaseLayer
{
public:
    
    static CCScene* scene();
    static TipStory3* create();
    bool init();
    void initHero();
//    void crazy(CCObject* pSender);
   void initNvRole(float dt);
   void fixFocus();
//    void screenMove();
   void tip1(float dt);
   void tip2(float dt);
   void tip3(float dt);
   void tip4(float dt);
   void tip5(float dt);
//    void tip6(float dt);
//    void tip7(float dt);
//    void tip8(float dt);
//    void duihua(float dt);
      void addTips();
      void addTip1();
      void addTip2();
      void resetTip1();
      void resetTip2();
//    void addTip2();
      void setText1();
      void setText2();
//    void qianqian(float dt);
//    void fadeAllErole(float dt);
//    void screenMove2();
//    void resetPosition();
//    void resetPosition2(CCObject* pSender);
   void GameEnd(float dt);
   void GoHome();
private:
    CCSprite* bg;
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
#endif /* defined(__ooo__TipStory3__) */
