//
//  GameData.h
//  King
//
//  Created by mac on 14-3-28.
//
//

#ifndef __King__GameData__
#define __King__GameData__

#include "cocos2d.h"
USING_NS_CC;

class GameData : public CCObject
{
public:
    static GameData* sharedGameData();
   
    CC_SYNTHESIZE(int, money, Money);   //英雄的金钱
    
    CC_SYNTHESIZE(int, mapIndex, MapIndex); //存储当前的关卡数
   
    CC_SYNTHESIZE(bool, isBeginer, Isbeginer);
    
    CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
    
    CC_SYNTHESIZE(float, _musicVolume, MusicVolume);
    
    CC_SYNTHESIZE(CCDictionary*, chengjiu,ChengJiu);
    
    CC_SYNTHESIZE(int, shengmingLevel, ShengmingLevel);
    
    CC_SYNTHESIZE(int, gongjiLevel, GongjiLevel);
    
    CC_SYNTHESIZE(int, fangyuLevel, FangyuLevel);
    
    CC_SYNTHESIZE(int, nuqiLevel, NuqiLevel);
    
    CC_SYNTHESIZE(bool, jinjiDuobi, JinjiDuobi);
    
    CC_SYNTHESIZE(bool, shoushen, Shoushen);
    
    CC_SYNTHESIZE(bool, fuhuo,Fuhuo);
    
    CC_SYNTHESIZE(bool, nuqibao, Nuqibao);
    
    CC_SYNTHESIZE(bool, firstTishiShuxing, FirstTishiShuxing);
    
    CC_SYNTHESIZE(bool, firstTishiNuqi, FirstTishiNuqi);
    
    CC_SYNTHESIZE(bool, isJihuo, IsJihuo);
    
    CC_SYNTHESIZE(bool, isShenmi, IsShenmi);
    
    CC_SYNTHESIZE(int, lastNuqi, LastNuqi);
    
    CC_SYNTHESIZE(bool, bazhinv, Bazhinv);
    
    CC_SYNTHESIZE(bool, bajiubei, Bajiubei);
    
    CCDictionary*  descriptions;
    
    void alterShengMingLevel();
    
    void alterGongJiLevel();
    
    void alterFangyuLevel();
    
    void alterNuqiLevel();
    
    void alterMoney(int delta);

    void alertMapIndex(int delta = 1);
    
    void alterHEROATK();
    
    void alterHEROHP();
    
    void alterHERODEFINE();
    
    void alterHERONUQI();
    
    void reset();
    
    void flush();   //将数据保存到外部文件中

    void buyHeroATK(int heroATK);  //购买英雄攻击力
    
    void buyHeroHp(int incHp);   //购买英雄血量
    
    void buyHeroDefine(int incD); //购买英雄防御力
    
    void buyHeroNuqi(int incN);  //购买英雄怒气
    
    void buyHeroShanbi();   //购买闪避
    
    void buyHeroShoushen();  //购买瘦身
    
    int extraNuqi;
    
    int getExtraNuqi();
    
    void setExtraNuqi(int nuqi);
    
	static int HEROATK;  	//基本攻击力

	static int HEROHP;     	//最大血量

	static int HEROPOM;    	//必杀攻击力

	static int HEROUPPOM; 	//必杀能量满

	static int HEROBOM;    	//英雄暴击率
	
    static int HeroDefine;  //英雄防御力
    
    static int HeroNuqi;    //英雄怒气
    
    static bool HeroCanShanbi;  //英雄是否可以闪避
    
    static bool HeroCanShoushen;  //英雄是否可以瘦身
    
    bool getJuqing(int index);
    
public:
    GameData();
    
    ~GameData();
    
    bool init();
};

#endif /* defined(__King__GameData__) */
