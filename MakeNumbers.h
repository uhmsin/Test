//
//  MakeNumbers.h
//  xiyou
//
//  Created by mac on 14-3-16.
//
//

#ifndef __xiyou__MakeNumbers__
#define __xiyou__MakeNumbers__
#include "cocos2d.h"
USING_NS_CC;

class MakeNumbers : public cocos2d::CCSprite{
public:
    CCSprite* numbers;
	MakeNumbers(int attckmun);
	~MakeNumbers(void);
    MakeNumbers(int attckmun,const char* name);
    
};
#endif /* defined(__xiyou__MakeNumbers__) */
