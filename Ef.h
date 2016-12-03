//
//  Ef.h
//  King
//
//  Created by mac on 14-4-13.
//
//

#ifndef __King__Ef__
#define __King__Ef__

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;

class Ef : public CCNode
{
public:
    Ef();
    static Ef* create(const char* name);
    bool init(const char* name);
    void actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID);
    CCSize getSize();
    CCArmature* armature;
    static Ef* create(const char* name,int index);
    bool init(const char* name,int index);
    void setSpeed(float rate);
    bool isRemove;
    
    static Ef* create(const char* name,int index,int loopTimes);
    bool init(const char* name,int index,int loopTimes);
};


#endif /* defined(__King__Ef__) */
