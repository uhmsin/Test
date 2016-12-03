//
//  BeginLayer.h
//  king04
//
//  Created by mac on 14-5-21.
//
//

#ifndef __king04__BeginLayer__
#define __king04__BeginLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace gui;

class BeginLayer : public CCLayer
{
public:
    static BeginLayer* create(int id);
    bool init(int id);
    void start_game(CCObject* pSender);
    void resume(CCObject* pSender);
    void resumeCall(CCObject* pSender);
    
    UILabel* label1;
    UILabel* lable2;
    UILabel* font1;
    UILabel* font2;
    UILabel* font3;
    
    CCSprite* bg;
    CCMenuItem* xiaocha;
    CCMenuItemSprite* startGame;
    
    
    CCSprite* guankajishao;
    CCSprite* moshiSprite;
    
    CCSprite* benguandefen;
    
    int id;
};

#endif /* defined(__king04__BeginLayer__) */
