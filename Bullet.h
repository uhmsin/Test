//
//  Bullet.h
//  king04
//
//  Created by mac on 14-5-7.
//
//

#ifndef __king04__Bullet__
#define __king04__Bullet__

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;
#include "ARPG.h"

class Bullet : public CCNode
{
public:
    
    ARPG* owner;
    
    static Bullet* create( ARPG* owner);
    
    bool init( ARPG* owner);
    
    CCArmature* s;
    
    void removeBullet();
    
    void update(float dt);
    
    CCRect getBondingBox();
    
    void remove();
};

#endif /* defined(__king04__Bullet__) */
