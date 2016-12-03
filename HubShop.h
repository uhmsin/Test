//
//  HubShop.h
//  king04
//
//  Created by mac on 14-5-15.
//
//

#ifndef __king04__HubShop__
#define __king04__HubShop__
#include "HubLayer.h"
#include "cocos2d.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyButton.h"
USING_NS_CC;
class HubShop : public CCLayer
{
public:
    
    HubShop();
    int type;
    CREATE_FUNC(HubShop);
    bool init();
    CCSprite* zuo;
    CCSprite* you;
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    bool LeftisTouched;
    bool RightisTouched;
    void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    void registerWithTouchDispatcher();
    void  addJoy();
    void addButton();
    SneakyButton* commonAttackButton;
    PlayerHeadUI* headUI;
    void update(float dt);
    void dalibao(CCObject* pSender);
    void pause(CCObject* pSender);
    void onlineLibaoMenu(CCObject* pSender);
};

#endif /* defined(__king04__HubShop__) */


