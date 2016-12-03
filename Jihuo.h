//
//  Jihuo.h
//  king04
//
//  Created by mac on 14-5-13.
//
//

#ifndef __king04__Jihuo__
#define __king04__Jihuo__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


class Jihuo : public CCLayer
{
public:
	bool m_isEnterNext = false;
	int guan = 1;

	int moshiID = 0;


    Jihuo();
    CREATE_FUNC(Jihuo);
    bool init();
	void onEnterTransitionDidFinish();
    static CCScene* scene(CCRenderTexture *sqr, bool isFlip );
    void resume(CCObject* pSender);
    void buy(CCObject* pSender);
    void showInfo(int id);
    void update(float dt);
    void jihuo();
    CCSprite* bg;
    CCMenuItem* xiaocha;
    CCMenuItem* goumai;
    CCSprite* background;
    bool ispop;
    void buy2(float dt);
};

#endif /* defined(__king04__Jihuo__) */
