//
//  Define.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef King_Define_h
#define King_Define_h

#ifndef SIZE
#define SIZE CCDirector::sharedDirector()->getWinSize()
#endif

#ifndef Role_Height
#define Role_Height SIZE.height/4
#endif


#include "Game.h"

#define random_range(low,high) ((arc4random()%(high-low+1))+low)

#ifndef DHERO_RIGHT
#define DHERO_RIGHT 1 // 主角面朝方向 右
#endif

#ifndef DHERO_LEFT
#define DHERO_LEFT -1 // 主角面朝方向 左
#endif

#ifndef dirOfani
#define dirOfani "res"
#endif

#ifndef Role
#define Role Game::instance()->getHero()
#endif

#ifndef ShopRole
#define ShopRole Game::instance()->getShopRole()
#endif


#ifndef gameLayer
#define gameLayer Game::instance()->getGameLayer()
#endif

#ifndef HUB
#define HUB Game::instance()->getHubLayer()
#endif

#ifndef MENU
#define MENU Game::instance()->getMenuLayer()
#endif

#ifndef SHOP
#define SHOP Game::instance()->getShopLayer()
#endif


#ifndef KingData
#define KingData GameData::sharedGameData()
#endif

static const float AttackFrame = 0.032f;

static int shengmingLevelMoney[10] =
{
    200, 240,250,300,400,340,340,340,340,340
};

static int gongjiLevelMoney[10] =
{
    200, 240,250,300,400,340,340,340,340,340
};
static int fangyuLevelMoney[10] =
{
    200, 240,250,300,400,340,340,340,340,340
};

static int nuqiLevelMoney[10] =
{
    200, 240,250,300,400,340,340,340,340,340
};

#ifndef NA_SLEEP_TIME
#define NA_SLEEP_TIME 80
#endif

#ifndef SAFE_TIME
#define SAFE_TIME 4
#endif
inline long millisecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now,NULL);
    return (now.tv_sec *1000 + now.tv_usec /1000);
}

enum
{
    WanderTag = 99,
    SeekRoleTag =100,
    JumpTag = 101
};

enum
{
    tituiEffectTag = 1001,
    zadiEffectTag = 1002,
    yanmuEffectTag = 1003,
    shandianEffectTag = 1004,
    shandianqiuEffectTag = 1004,
    qianxiaqianEffectTag = 1005,
    juqiEffectTag = 1006,
    blackTag = 100007,
    techTag = 100008,
    duobiEffectTag = 100009,
    readygoTagZorder = 999999999
};

/*static std::string juqingMapTitle[21] =
{
  "",
  "",
  "琼",
  "混混",
  "混混",
  "混混",
  "女混混",
  "琼",
  "混混首领",
  "琼",
  "琼",
  "邪恶教主",
  "邪恶教主",
  "琼",
  "琼",
  "琼",
  "琼",
  "琼",
  "琼",
  "琼",
  "琼",
};

static std::string juqingMapText[21] =
{
    "",
	"",
	" 别浪费时间了,你们一起上吧!杀光了你们我还要赶路呢!",
	"还真敢追过来？给我干死他！", 
	"组织会为我报仇的！！！",
	" 兄弟们上啊!妈的竟然敢追到这里！",
	"真帅呢! 让我来配他你玩儿一会儿吧~!",
	"你们这帮恶棍，把小舞还给我！",
	"没想到你能走到这里，但是！也就到此为止了！今日就是你的死期了。",
	"混混也有礼拜堂?让我直接超度你们吧！",
	"还有谁?! 都死完了么?! ",
	"总有些不知死活的送上门来",
	"竟敢亵渎我们神圣的组织…不可饶恕！",
	"我是黯月之血继承者，去后悔你们惹火了我吧!",
	"如果将一切都烧尽的话, 不就干净了么?",
	"我的能力是时候完全释放了。",
	"你还没有被干掉吗?",
	"这就是最后的总部? 想放抗么? 真无聊!",
	"哭吧,叫吧,然后就死吧! 到此为止了!",
	"啊啊啊啊啊啊！谁也无法阻挡我",
	"你们成功的为了自己挖好了坟墓，让我来结束这一切。"
};

static std::string loadingTips[] =
{
    "小提示: 怪物太强打不过？还不快快强化属性。",
    "小提示: 怒气不够用快去商店购买怒气包吧。",
    "小提示: 多多使用必杀技虐杀BOSS吧。",
    "小提示: 你知道么？在商店可以购买两个超强的隐藏技能。",
    "小提示: 出现隐藏礼包一定要把握机会，下次就不会再来了。"
};*/


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#endif
