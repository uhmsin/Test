//
//  Dalibao.h
//  king04
//
//  Created by mac on 14-5-18.
//
//

#ifndef __king04__Dalibao__
#define __king04__Dalibao__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class Dalibao : public CCLayer
{
public:
	bool m_isEnterNext = false;
	int guan = 1;
	int moshiID = 0;

    static Dalibao* create(int id);
    bool init(int id);
    CCSprite* bg;
    CCMenuItem* xiaocha;
    CCMenuItem* goumai;
    CCMenuItem* duobi;
    CCMenuItem* shoushen;
    CCSprite* touming;
    CCSprite* touming2;
    CCSprite* xuanzekuang;
    void showInfo(int id);
    void buy(CCObject* pSender);
    void resume(CCObject* pSender);
    void duobiMenu(CCObject* pSender);
    void shoushenMenu(CCObject* pSender);
    void jinbi(CCObject* pSender);
    CCScene* scene(int id);
    int id;
    int libaoid;
    CCMenuItemSprite* menu5888;
	CCMenuItemSprite* menu2888;
	CCMenuItemSprite* menu1888;
    
    CCSprite* yihuode;
    CCSprite* yihuode2;
    
    CCSprite* title;
    CCSprite* titleMoney;
    
    void buy2(float dt);
};

#endif /* defined(__king04__Dalibao__) */
