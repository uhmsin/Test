//
//  GameOverScene.h
//  King
//
//  Created by mac on 14-3-28.
//
//

#ifndef __King__GameOverScene__
#define __King__GameOverScene__
#include "cocos2d.h"
#include "BaseLayer.h"
using namespace cocos2d;
class GoldCounterLayer;
class GameOverScene : public BaseLayer
{
public:

	void ShowGift();
	float _del = 0.0f;

	void update(float dt);

    GameOverScene();
	static GameOverScene* create();
	virtual bool init();
    static CCScene* scene();
    static CCScene* scene(int lianji,int hpPercent,int remainTime,int guan,CCRenderTexture* tx,bool heroisDie = false);
    static GameOverScene* create(int lianji,int hpPercent,int remainTime,int guan,bool heroisDie = false);
    virtual bool init(int lianji,int hpPercent,int remainTime,int guan,bool heroisDie = false);
	void menuCloseCallback(cocos2d::CCObject* pSender);
	void menuCloseCallback();
    void show();
    void alertData();     //更新文件数据
    void registerWithTouchDispatcher();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void callback();
    
    CC_SYNTHESIZE(int, guan, Guan);
    CC_SYNTHESIZE(int, lianjiNum, Lianji);
    CC_SYNTHESIZE(int, hpPercent, HpPercent);
    CC_SYNTHESIZE(int, remainTime, RemainTime);
    CC_SYNTHESIZE(int, totalScore, TotalScore);
    void setNumber(int number, int ceiling=99999);
    bool HeroIsDie;
    CCMenu* menu;
    CCMenuItemSprite* jixu;
    
    GoldCounterLayer* goldLayer;
    GoldCounterLayer* goldLayer2;
    GoldCounterLayer* goldLayer3;
    GoldCounterLayer* goldLayer4;
    GoldCounterLayer* goldLayer5;
    
    int guanjiangli;
    int times;

};

#endif /* defined(__King__GameOverScene__) */
