//
//  ShopBuy2.h
//  king04
//
//  Created by mac on 14-5-12.
//
//

#ifndef __king04__ShopBuy2__
#define __king04__ShopBuy2__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class ShopBuy2 : public CCLayer
{
public:
    ShopBuy2();
    CREATE_FUNC(ShopBuy2);
    bool init();
    static CCScene* scene(CCRenderTexture *sqr, bool isFlip );
    void resume(CCObject* pSender);
    void buy(CCObject* pSender);
    void showInfo(int id);
    CCSprite* bg;
    CCMenuItem* xiaocha;
    CCMenuItem* goumai;
    CCSprite* background;
    void buy2( float dt);
};
#endif /* defined(__king04__ShopBuy2__) */
