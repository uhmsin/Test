//
//  ShopScene.h
//  king04
//
//  Created by mac on 14-5-15.
//
//

#ifndef __king04__ShopScene__
#define __king04__ShopScene__

#include "BaseLayer.h"
#include "cocos2d.h"
#include "Hero.h"
#include "Define.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;
#include "Hero.h"

enum dalibaotag
{
    dalibaotag = 5001,
    dalibaozorder = 9999999
};
class ShopScene : public BaseLayer
{
public:
	virtual void keyBackClicked();

    CCSprite* bg;
    CCSprite* nvrole;
    CCArmature* baoxiang;
    CCArmature* texiao;
    CCArmature* xuanguan;
    CCArmature* duboji;
    CCSprite* jinbi;
    CCSprite* jiantou;
	void ShowGift();
    void dalibao();
	void item_0(CCObject* _sender);
	void item_1(CCObject* _sender);
	void item_2(CCObject* _sender);
	void EnterGame(CCObject* _sender);

	void onEnterTransitionDidFinish();

    Hero* hero;
    int goumaiweizhi;
    int oldgoumaiweizhi;
    
    void update(float dt);
    void updatePosition(float dt);
    
    CREATE_FUNC(ShopScene);
    static CCScene* scene();
    bool init();
};

#endif /* defined(__king04__ShopScene__) */




