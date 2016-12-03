//
//  TipStory.h
//  King
//
//  Created by mac on 14-4-21.
//
//

#ifndef __King__TipStory__
#define __King__TipStory__


#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
USING_NS_CC;
using namespace cocos2d::gui;
class TipStorySprite : public CCSprite
{
public:
    static TipStorySprite* create(int width,int height);
    bool init(int width,int height);
    void draw();
    int width;
    int height;
};


class TipStory : public CCLayer
{
public:
    ~TipStory();
    static CCScene* scene();
    CREATE_FUNC(TipStory);
    bool init();
    Hero* hero;
    Monster* monster;
    CCSprite* back;
    
    void nextTips();
    void addTip1(int index , int roleid);
    void addTip01(int index ,int monsterID);
    CCMenuItem* item;
    
    UILabel* label;
    UILabel* label1;
    UILabel* label2;
    
    CCLabelTTF* label02;
    
    
    int juqingIndex;
    
    void monsterSay();
    
    void blackScreen(CCObject* pSender);
    
    void pop();
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    void actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID);

    CCSprite* tip3;
    CCSprite* tip1;
    CCSprite* tip2;
    CCSprite* tip01;
    
    CCSprite* hunhuntouxiang;
    CCSprite* bosstouxiang;
    CCSprite* roletouxiang;
    CCSprite* nvroletouxiang;
    
    void addTips();
    
    void resumeTip();
    
    CCMenu* menu;
    
    bool canSay;
    
    CCLayerColor* black;
    
    CCNode* node2;
    
    void moon(CCObject* pSender);
    
    CCSprite* moonsprite;
    
    void resumeTip2();
    
    void bashenan();
    
    void bashenan2();
    
    void fade();
    
    void fade2();
    
    void bashenan1();
    
    void tiaoguo(CCObject* o);
    
    void tiaoxi();
    
    void tiaoxi2();
    
    void newblackScreen();

    void xiechi();
    
    void zhuiji();
    
    void zhuiji2();
    
    void zhuiji3();
    
    void heiping();
    CCArmature* nvRole;
    CCArmature* boss;
    CCArmature* g1;
    CCArmature* g2;
    
    
    void setText();
    void setText1();
    
    int currentduihua_index;
    int currentword_index;
};

#endif /* defined(__King__TipStory__) */
