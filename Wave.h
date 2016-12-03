//
//  Wave.h
//  King
//
//  Created by mac on 14-3-27.
//
//

#ifndef __King__Wave__
#define __King__Wave__
#include "cocos2d.h"
USING_NS_CC;
#include "Wave.h"
#include "Monster.h"
class Wave : public CCNode
{
public:
    bool init(float spawnrate);
    
	static Wave* create(float spawnrate);
    
	CC_SYNTHESIZE(float, _spawnRate, SpawnRate);
    
	CC_SYNTHESIZE(int, _redEnemys, RedEnemys);
    
	CC_SYNTHESIZE(int, _greenEnemys, GreenEnemys);
};
#endif /* defined(__King__Wave__) */
