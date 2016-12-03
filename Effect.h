//
//  Effect.h
//  King
//
//  Created by mac on 14-4-11.
//
//

#ifndef __King__Effect__
#define __King__Effect__
#include "cocos2d.h"
USING_NS_CC;

class Effect : public CCNode
{
public:
    static Effect* create(const char* name,float ,unsigned int isLoop);
    CCAnimation* createAnimation(const char* name,float ,unsigned int isLoop);
    bool init(const char* name,float ,unsigned int isLoop);
    CCSprite* m_sprite;
    void remove();
    
};
#endif /* defined(__King__Effect__) */
