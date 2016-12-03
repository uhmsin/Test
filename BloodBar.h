//
//  BloodBar.h
//  xiyou
//
//  Created by mac on 14-3-18.
//
//

#ifndef __xiyou__BloodBar__
#define __xiyou__BloodBar__
#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;

class BloodBar : public CCNode
{
    CCProgressTimer* blood;
public:
    CREATE_FUNC(BloodBar);
    bool init();
    BloodBar(void);
    ~BloodBar(void);
	void bindPlayer(CCNode* pPlayer)
    {
        player = pPlayer;
    }
    void processPlayerHP();
public:
    void initWidget();
	void setHPBarPercent(int percent);
    CCNode* player;
	int playerLifeRecorder;
	int playerHPRecorder;
    CCProgressTimer* left;
};

#endif /* defined(__xiyou__BloodBar__) */
