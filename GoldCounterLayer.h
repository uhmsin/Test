//
//  GoldCounterLayer.h
//  King
//
//  Created by mac on 14-4-20.
//
//

#ifndef __King__GoldCounterLayer__
#define __King__GoldCounterLayer__

#include "cocos2d.h"
USING_NS_CC;
class GoldCounterLayer : public cocos2d::CCNode
{
public:
    static GoldCounterLayer* create(int number = 0);
    bool init(int number = 0);
    void setNumber(int number,int ceiling = 999999);
    void setNumbet2(int number,int ceiling = 999999);
    CC_SYNTHESIZE_READONLY(int, _number, Number);
protected:
    void getNumAtPos(int pos);
    CCArray* arraysCounter;
    
    ~GoldCounterLayer();
    GoldCounterLayer();
    
    int weishu;
};

#endif /* defined(__King__GoldCounterLayer__) */
