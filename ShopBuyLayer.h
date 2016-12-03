//
//  ShopBuyLayer.h
//  King
//
//  Created by mac on 14-3-28.
//
//

#ifndef __King__ShopBuyLayer__
#define __King__ShopBuyLayer__

#include "cocos2d.h"
USING_NS_CC;

class ShopBuyLayer : public CCLayer
{
public:
    static ShopBuyLayer* create(const char* backgroundImage);
    bool init(const char* backgroundImage);
    void back(CCObject* pSender);

};

#endif /* defined(__King__ShopBuyLayer__) */