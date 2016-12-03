//
//  GameData.cpp
//  King
//
//  Created by mac on 14-3-28.
//
//
#include "GameData.h"
#include "Define.h"
#include "Hero.h"

int GameData::HEROATK=50; //英雄的基本属性
int GameData::HEROHP=3000; //最大血量
int GameData::HEROPOM=100; //必杀攻击力
int GameData::HEROUPPOM=1000; //必杀能量满
int GameData::HEROBOM=15;    //英雄暴击率
int GameData::HeroDefine = 0; //英雄防御力
int GameData::HeroNuqi = 2;    //英雄怒气
bool GameData::HeroCanShoushen = false;  //英雄是否可以瘦身
bool GameData::HeroCanShanbi = false;  //英雄是否可以闪避
static GameData* _sharedGameData = NULL;

bool GameData::getJuqing(int index)
{
    char juqing[10] = {0};
    sprintf(juqing, "juqing%d",index);
    bool isJuqing = CCUserDefault::sharedUserDefault()->getBoolForKey(juqing, true);
    if(isJuqing)
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey(juqing, false);
    }
    return isJuqing;
}

GameData * GameData::sharedGameData()
{
    if (_sharedGameData == NULL)
    {
        _sharedGameData = new GameData();
        _sharedGameData->init();
    }
    return _sharedGameData;
}

void GameData::alterMoney(int delta)
{
    this->setMoney(this->getMoney() + delta);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("money", money);
}

void GameData::alertMapIndex(int delta)
{
    if (this->getMapIndex() > 20) {
        return;
    }
    this->setMapIndex(this->getMapIndex() + delta);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("mapIndex", mapIndex);
}

void GameData::alterShengMingLevel()
{
    if (shengmingLevel>=10) {
        return;
    }
    this->setShengmingLevel(this->getShengmingLevel() + 1);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("shengmingLevel", shengmingLevel);
    this->alterHEROHP();
}

void GameData::alterGongJiLevel()
{
    if (gongjiLevel >= 10) {
        return;
    }
    this->setGongjiLevel(this->getGongjiLevel()+1);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gongjiLevel", gongjiLevel);
    this->alterHEROATK();
}

void GameData::alterFangyuLevel()
{
    if (fangyuLevel >= 10) {
        return;
    }
    this->setFangyuLevel(this->getFangyuLevel()+1);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("fangyuLevel", fangyuLevel);
    this->alterHERODEFINE();
}

void GameData::alterNuqiLevel()
{
    if (nuqiLevel >= 10)
    {
        return;
    }
    this->setNuqiLevel(this->getNuqiLevel()+1);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("nuqiLevel", nuqiLevel);
    this->alterHERONUQI();
}

int GameData::getExtraNuqi()
{
    return extraNuqi;
}

void GameData::setExtraNuqi(int nuqi)
{
    this->extraNuqi = nuqi;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("ExtraNuqi", extraNuqi);
}

GameData::GameData()
{
    isJihuo = false;
    shengmingLevel = 1;
    gongjiLevel = 1;
    fangyuLevel = 1;
    nuqiLevel = 2;
    jinjiDuobi = false;
    shoushen = false;
    fuhuo = false;
    nuqibao = false;
    extraNuqi  = 0;   //额外购买的怒气
    firstTishiShuxing = false;
    firstTishiNuqi = false;
    bazhinv = false;
    bajiubei = false;

}

void GameData::alterHEROATK()
{
    HEROATK = 50 + (this->getGongjiLevel()-1)*this->getGongjiLevel()*30;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("heroAtk",HEROATK);
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    if (Role!=NULL)
    {
        Role->setAttackP(HEROATK);
        Role->setAttackPP(HEROATK);
    }
}

void GameData::alterHEROHP()
{
    HEROHP = 2000 + (this->getShengmingLevel()-1)*500;

    CCUserDefault::sharedUserDefault()->setIntegerForKey("HEROHP", HEROHP);
   
    if (Role!=NULL)
    {
        Role->setMaxHp(HEROHP);
        Role->setHP(Role->getHP()+1000);
    }
}

void GameData::alterHERODEFINE()
{
    if (Role!=NULL)
    {
        Role->setDP(this->getFangyuLevel());
    }
    HeroDefine = 0 + (this->getFangyuLevel()-1)*30;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("HeroDefine", HeroDefine);  //英雄防御力

}

void GameData::alterHERONUQI()
{
    if (Role!=NULL)
    {
        Role->nuqi = 100* KingData->getNuqiLevel() + 99;
        Role->maxNengliangdou = KingData->getNuqiLevel();
    }
}

void GameData::reset()
{
    
}

GameData::~GameData()
{
    this->flush();
}

bool GameData::init()
{
    isBeginer = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner", true);
    if (isBeginer == true)
    {
        this->setMapIndex(1); //如果是第一次玩游戏，不需要从文件中读取数据
        this->setMoney(0);//关卡为第一关

    }else
    {
        isBeginer = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner");
        mapIndex = CCUserDefault::sharedUserDefault()->getIntegerForKey("mapIndex");
        if (mapIndex<=0)
        {
            mapIndex = 1;
        }
        money =  CCUserDefault::sharedUserDefault()->getIntegerForKey("money");
        HEROATK = CCUserDefault::sharedUserDefault()->getIntegerForKey("heroAtk",GameData::HEROATK);
        HEROHP = CCUserDefault::sharedUserDefault()->getIntegerForKey("HEROHP",GameData::HEROHP);
        HeroDefine = CCUserDefault::sharedUserDefault()->getIntegerForKey("HeroDefine",GameData::HeroDefine);
        HeroNuqi = CCUserDefault::sharedUserDefault()->getIntegerForKey("HeroNuqi",GameData::HeroNuqi);
        HeroCanShanbi = CCUserDefault::sharedUserDefault()->getBoolForKey("HeroCanShanbi",GameData::HeroCanShanbi);
        HeroCanShoushen = CCUserDefault::sharedUserDefault()->getBoolForKey("HeroCanShoushen",GameData::HeroCanShoushen);
        
        shengmingLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("shengmingLevel",shengmingLevel);
        gongjiLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("gongjiLevel",gongjiLevel);
        fangyuLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("fangyuLevel",fangyuLevel);
        nuqiLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("nuqiLevel",nuqiLevel);
        
        jinjiDuobi = CCUserDefault::sharedUserDefault()->getBoolForKey("jinjiduobi");
        shoushen = CCUserDefault::sharedUserDefault()->getBoolForKey("shoushen");
        fuhuo = CCUserDefault::sharedUserDefault()->getBoolForKey("fuhuo");
        nuqibao = CCUserDefault::sharedUserDefault()->getBoolForKey("nuqibao");
        extraNuqi =  CCUserDefault::sharedUserDefault()->getIntegerForKey("ExtraNuqi");
        firstTishiShuxing = CCUserDefault::sharedUserDefault()->getBoolForKey("firstTishiShuxing");
        firstTishiNuqi = CCUserDefault::sharedUserDefault()->getBoolForKey("firstTishiNuqi");
        isJihuo = CCUserDefault::sharedUserDefault()->getBoolForKey("isJihuo");
        isShenmi  = CCUserDefault::sharedUserDefault()->getBoolForKey("isShenmi");
        lastNuqi = CCUserDefault::sharedUserDefault()->getBoolForKey("lastNuqi");
        bazhinv = CCUserDefault::sharedUserDefault()->getBoolForKey("bazhinv");
        bajiubei = CCUserDefault::sharedUserDefault()->getBoolForKey("bajiubei");
    }
    return true;
}

void GameData::flush()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("HEROHP", HEROHP);  //英雄血量
    CCUserDefault::sharedUserDefault()->setIntegerForKey("HeroDefine", HeroDefine);  //英雄防御力
    CCUserDefault::sharedUserDefault()->setIntegerForKey("HeroNuqi", HeroNuqi); //英雄怒气
    CCUserDefault::sharedUserDefault()->setBoolForKey("HeroCanShanbi", HeroCanShanbi);//英雄是否可以闪避
    CCUserDefault::sharedUserDefault()->setBoolForKey("HeroCanShoushen", HeroCanShoushen);//英雄是否可以瘦身
    CCUserDefault::sharedUserDefault()->setIntegerForKey("heroAtk",HEROATK);
    CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", false);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("money", money);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("mapIndex", mapIndex);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("shengmingLevel", shengmingLevel);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gongjiLevel", gongjiLevel);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("fangyuLevel", fangyuLevel);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("nuqiLevel", nuqiLevel);
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("jinjiduobi", jinjiDuobi);
    CCUserDefault::sharedUserDefault()->setBoolForKey("shoushen", shoushen);
    CCUserDefault::sharedUserDefault()->setBoolForKey("fuhuo", fuhuo);
    CCUserDefault::sharedUserDefault()->setBoolForKey("nuqibao", nuqibao);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("ExtraNuqi", extraNuqi);
    CCUserDefault::sharedUserDefault()->setBoolForKey("firstTishiShuxing", firstTishiShuxing);
    CCUserDefault::sharedUserDefault()->setBoolForKey("firstTishiNuqi", firstTishiNuqi);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isJihuo", isJihuo);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isShenmi",isShenmi);
    CCUserDefault::sharedUserDefault()->setBoolForKey("lastNuqi",lastNuqi);
    CCUserDefault::sharedUserDefault()->setBoolForKey("bazhinv",bazhinv);
    CCUserDefault::sharedUserDefault()->setBoolForKey("bajiubei",bajiubei);
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
}

void GameData::buyHeroATK(int heroATK)  //购买英雄攻击力
{
    HEROATK = HEROATK + heroATK;
}

void GameData::buyHeroHp(int incHp)
{
    HEROHP = HEROHP + incHp;         //购买英雄血量
}

void GameData::buyHeroDefine(int incD) //购买英雄防御力
{
    HeroDefine  = HeroDefine + incD;
}

void GameData::buyHeroNuqi(int incN)  //购买英雄怒气
{
    HeroNuqi = HeroNuqi + incN;
}

void GameData::buyHeroShanbi()   //购买闪避
{
    HeroCanShanbi = true;
}

void GameData::buyHeroShoushen()  //购买瘦身
{
    HeroCanShoushen = true;
}