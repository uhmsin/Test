//
//  Game.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef __King__Game__
#define __King__Game__

#include "cocos2d.h"
#include "GameScene.h"
#include "HubLayer.h"
#include "Hero.h"
#include "MenuLayer.h"
#include "ShopBuy.h"
#include "Jihuo.h"
//#include "FourJihuo.h" 
#include "Tools/Tools.h"
USING_NS_CC;
class Game : public CCObject{
public:
    static Game* instance();
    CC_SYNTHESIZE(Hero*, hero, Hero);
    CC_SYNTHESIZE(GameScene*,gameLayer,GameLayer);
    CC_SYNTHESIZE(HubLayer*,hubLayer,HubLayer);
    CC_SYNTHESIZE(MenuLayer*,menuLayer,MenuLayer);
    CC_SYNTHESIZE(ShopBuy*,shopLayer,ShopLayer);
    CC_SYNTHESIZE(Jihuo*,jihuo,Jihuolayer);
    CC_SYNTHESIZE(Hero*,shopRole,ShopRole);
    //CC_SYNTHESIZE(FourJihuo*,fourJihuo,FourJihuo);
    Game();
    bool init();
};
#endif /* defined(__King__Game__) */
