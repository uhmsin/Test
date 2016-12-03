//
//  PlayerHeadUI.h
//  King
//
//  Created by mac on 14-4-1.
//
//

#ifndef __King__PlayerHeadUI__
#define __King__PlayerHeadUI__

#include "cocos2d.h"
#include "cocos-ext.h"
#include  "ARPG.h"
using namespace cocos2d::extension;
using namespace cocos2d::gui;
class PlayerHeadUI : public cocos2d::CCLayer
{
public:
    PlayerHeadUI(void);
    ~PlayerHeadUI(void);
    void changeMoney();
    void bindPlayer(ARPG* pPlayer)
    {
        player = pPlayer;
    }
     UILoadingBar* life;
private:
    
    void initWidget();
    
    void processPlayerLife();
    
	void processPlayerHP();
    
    void setHPBarPercent(int percent);
    
    void setMPBarPercent(int percent);
    
  
    
    UILoadingBar* nuqi;
    
    UILayer* uiLayer;
    
    ImageView* shuzi;
    
    void update2(float dt);
    
	void updateNuqi(float dt);
public:
	void openNuqiUp();
private:
    ARPG* player;
    
    UILabel* moneyHead;
};
#endif /* defined(__King__PlayerHeadUI__) */
