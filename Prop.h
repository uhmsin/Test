//
//  Prop.h
//  King
//
//  Created by mac on 14-3-27.
//
//

#ifndef __King__Prop__
#define __King__Prop__

#include "cocos2d.h"
USING_NS_CC;
class Prop : public CCNode
{
public:
    Prop();
    
    static Prop* create(int type ,int num);
    bool init(int type,int num);
    
    CCSprite* innerSprite;
    CCRect getBondingBox();
    
    CC_SYNTHESIZE(bool,is_hold, Is_hold);
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(int, num, Num);
};
#endif /* defined(__King__Prop__) */
