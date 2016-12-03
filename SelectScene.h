//
//  SelectScene.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef __King__SelectScene__
#define __King__SelectScene__

#include "BaseLayer.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace gui;

using namespace std;

/*const string title[21] =
{
"1-1.堕落街1",
"1-1.堕落街1",
"1-2.堕落街2",
"1-3.堕落街3",
"1-4.堕落街4",
"2-1.废弃都市1",
"2-2.废弃都市2",
"2-3.废弃都市3",
"2-4.废弃都市4",
"3-1.礼拜堂1",
"3-2.礼拜堂2",
"3-3.礼拜堂3",
"3-4.礼拜堂4",
"4-1.华尔街大道1",
"4-2.华尔街大道2",
"4-3.华尔街大道3",
"4-4.华尔街大道4",
"5-1.喋血码头1",
"5-2.喋血码头2",
"5-3.喋血码头3",
"5-4.喋血码头4"
};

const string descr[21] =
{
"第一次进入游戏",
"这是一片法律无法触及的地方，只有一个流传很久的名字—堕落街。",
"毫无疑问这是一个极其危险的地方，但是救出小舞是你唯一的目标",
"无穷无尽的敌人，难道你已经陷入了一个巨大的阴谋之中?",
"代号“鬣狗”,这是堕落街的幕后黑手么？",
"堕落街原来只是一个入口，这背后居然隐藏着如此巨大的都市。",
"残破不堪的废弃都市中隐藏着各种犯罪分子，既然如此就惩奸除恶吧。",
"这些人都是亡命之徒你必须小心，再小心！",
"终于安奈不住了? 分部首领出现!",
"分部首领说小舞被抓到了礼拜堂里，礼拜堂？",
"这隐藏在黑暗中的礼拜堂如此雄伟，为什么在这种地方还有礼拜堂。",
"看看你发现了什么？一个邪教组织！",
"邪恶教主, ”鬣狗“组织的又一条狗",
"这堕落都市居然是在市中心的下面，华尔街大道才是他们的老巢",
"再现! 传说中的古武术!都去死吧！",
"觉醒吧！我的终极能力",
"教主再现?! 打不死的邪恶教主?",
"最终决战之地! 喋血码头!",
"死拼! 狂暴下的黯月之血!",
"让我在疯狂一次吧",
"既然想伤害我最爱的人，就让你们所有人陪葬"
};

const string moshiStr[21] =
{
    "",
	"杀死任意10个敌人",
	"杀死任意15个敌人",
	"限时一分钟，必须杀死15个怪",
	"杀死BOSS后过关",
    "杀死任意30个敌人",
    "限时一分钟，必须杀死20个怪",
    "向前行走600米过关",
    "杀死BOSS后过关",
    "向前行走800米过关",
    "存活2分钟过关",
    "杀死任意40个敌人",
    "杀死BOSS后过关",
    "杀死任意45个敌人",
    "存活2分钟过关",
    "向前行走1200米过关",
    "杀死BOSS后过关",
    "杀死任意60个敌人",
    "向前行走1500米过关",
    "存活3分钟过关",
    "杀死BOSS后过关"
};*/

const int moshiID[21] =
{
    0,  0,0,1,  0,     2,1,  3,0,     3 ,4,0,0,     0,4,3,  0,     0,3,  4,0
};
/*const int moshiID[21] =
{
	0, 
	0, 3, 1,0, 
	2, 1, 3, 0,
	3, 4, 0, 0, 
	0, 4, 3, 0,
	0, 3, 4, 0
};*/


class SelectScene : public BaseLayer
{
public:
	virtual void keyBackClicked();


    SelectScene();
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(SelectScene);
    
    void Back(CCObject* pSender);
    
    CCArray* selectGuan;

    static int xuanguan;
    
    bool jiesuo[15];
    
    void clickButtonCallback(CCObject* pSender,TouchEventType type);
    
    void shopButtonCallback(CCObject* pSender,TouchEventType type);
    
    void shopButtonCallback(CCObject* pSender);
    
	void shopButtonCallbackAuto();

	void shopButtonCallback();

    void start_game(CCObject* pSender, TouchEventType type);
    
    void onExit();
    
    void addTips();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    void registerWithTouchDispatcher();
    
    void backScene(CCObject* pSender);
    
    void fudong(CCObject* pSender);
    
    void fudong1(CCObject* pSender);
    
	void showLvup();

	void ShowGift();

    void onlineLibaoMenu(CCObject* pSender);
    
	void onlineLibaoMenu();

    CCSprite* selectS;
    
    int current_Select;
    
    void onEnter();
    
    UILabel* font1;
    
    UILabel* font2;
    
    UILayer* ul;
    
    CCSprite* aniSprite;
    
    bool canClick;
    
    int biaozhi;
    
    CCSprite* sprite;
	CCSprite* tishi_sprite;

    bool drag;
    
    CCPoint beginP;
    
    CCPoint endP;
    
    CCMenu* menu;
    
    CCMenuItemSprite* back;
    
	CCMenuItemSprite* jiantou1;
    
	CCMenuItemSprite* jiantou2;
    
    CCSprite* new2;
    
    UIButton* curr_button ;
    
    void addTip(std::string text);
    
    void addTip2(std::string text);
    
    void resetTip();
    
    CCSprite* tip1;
    
    CCSprite* jiaoshi;
    
    UILabel* label;
    
};
#endif /* defined(__King__SelectScene__) */
