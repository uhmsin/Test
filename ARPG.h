//
//  ARPG.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef __King__ARPG__
#define __King__ARPG__

enum
{
	 UP = 0,  	    /** 上 */       // 移动动作可分为 上下左右
	 DOWN = 1,  	/** 下 */
	 LEFT = 2,  	/** 左 */
	 RIGHT = 3,   	/** 右 */
	 HOLDER = 4   	/** 原地 */
};
/*角色动画:
 0.站立
 1.移动
 2.受击
 3.上浮空
 4.倒地
 6.攻击预警动画
 7.快速移动(动画1调整播放频率即可)
 8.攻击动画1(可变)
 9.攻击动画2(可变)
 10.攻击动画3(可变)
 11 倒地
 */
#define ANIMATION_STAND "stand"
#define ANIMATION_MOVE "move"
#define ANIMATION_BEATBACK "beatBack" //受击
#define ANIMATION_UPFLOAT "upfloat" //上浮空
#define ANIMATION_DOWNFLOAT "downfloat" //下浮空
#define ANIMATION_GETDOWN "getdown" //倒地
#define ANIMATION_ATTACKWARNING "attackwarning" //攻击预警
#define ANIMATION_MOVEFAST "movefast" ///快速移动
#include "cocos2d.h"
USING_NS_CC;
#include "BloodBar.h"
#include "BeatEffect.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;
typedef enum M_state
{
    s_stand,
    s_move,
    s_attack,
    s_skill,
}M_state;


class ARPG;
class PlaysDelegate
{
public:
    virtual bool actionDidAttack(ARPG* p)=0;
    virtual bool actionDidDie(ARPG* p)=0;
};

class ARPG : public CCNode
{
public:
    BeatEffect* m_beatEffect;//受击效果
    
    bool isUnderAttack;//当前是否被攻击
    
    bool isFirstDropBack;//是否在地上
    
    string m_animationName;//动画名称
    
	float speedMain;       /** 移动速度 */

	int ationState;    	/** 总动作状态 */
    
	int INIT;   	/** 待机动作 初始状态 人物 原地不动 */
    
	int ON_ACTION;  	/** 可以操作状态 自己能显示 和不在不可操作状态中 包括攻击和 被攻击 */
    
	int ARPG_DIE; 	/** 英雄的死亡状态npc的消失由自己设定逻辑画笔 */
    
	int accord; 	/** 可操作状态下分为 主动状态 */

	int ACCORD; 	/** 主动状态 */

	int ACCORD_ ; 	/** 被动强制状态 */

	int OFF_ACTION; 	/** 不可操作状态一般是指 暂停中 和 死亡 */
    
	int action_place;  	/** 动作方向 */

	int orientation ; 	/** 移动方向 */
    
	CCSprite* spMain; 	/** 主要移动精灵类npc 或者英雄 */

	bool isJump;       	/** 是否已经跳跃了 */

	bool offMove;     	/** 基本移动状态 不可 移动状态 */

	int onMove;   	/** 基本移动状态 可以 移动状态 */
    
	bool isDie;   	/** 是否进入死亡状态 */
    
    bool abDie;    /*英雄彻底死亡*/
    
	bool is_UndoRunState ; 	/** 该变量用判断方向键是否松开 */

	bool is_UndoAtkState; 	/** 该变量用来判断功能键是否按下 */

    CCArmature* s;
    
    CCArmature* s2;
    
    CCArmatureAnimation* animation;
    
    PlaysDelegate* delegate;  
    
    CCPoint oldPosition;   //敌人原来的位置
    
    void draw();
    
    CC_SYNTHESIZE(int, type, Type); //1是英雄  2是敌人
    
    CCArray* beatEffects;
    
    
    int safe_time;  //受击保护时间
    
    CC_SYNTHESIZE(int,attackP , AttackP); //精灵攻击力
    
    CC_SYNTHESIZE(int,attackPP , AttackPP); //精灵攻击力
    
    CC_SYNTHESIZE(int, hp, HP); //精灵血量
    
    CC_SYNTHESIZE(int, maxHp, MaxHp);
    
    CC_SYNTHESIZE(int, dp, DP);
    
    bool isInvincible;  //播放大招无敌中
    
    bool wudi;
    
    CCArmature* shadow;
    
    CCSprite* shadow2;
    
    BloodBar* bloodbar;
    
    CCRect attackRect;    //攻击矩形；
    
    float getHPPercent()
    {
         return 100*hp/maxHp;
    };
    
    float getNuqiPercent()
    {
         return 100*nuqi/maxNuqi;
    };
    
    CC_SYNTHESIZE(int, attackType, AttackType);
    CC_SYNTHESIZE(int, beAttackType, BeAttackType);
    
    int arpg_sPositionX;
    
    int nuqi;
    
    bool isqianqian;
    
    int maxNuqi;
    
    bool isScrolling;
    
    CC_SYNTHESIZE(int, nengliangdou, Nengliangdou);
    
    int maxNengliangdou;
    
    int buyNengliangdou;
    
    int bottomH;    //下边缘的高度
    
    int topH;   //上边缘的高度
    
    bool isBeAttack;
    
    int id;

    int actionID;
    
    M_state m_state;
    
    bool has_hitARPG;
    
    bool hasBati;
    
public:
     void dropProp();
    
     void updateTopAndBottom(float dt);   //更新上下边缘
    
     void collison( CCBone * bone , const char * evt, int originFrameIndex, int currentFrameIndex);
    
     virtual void removeTo();
    
     virtual void removeCallback();
    
     void updateAttackRect(float dt);
    
     void stand();
    
     void flipDir();
    
     virtual void move();
    
     ARPG();
    
     CREATE_FUNC(ARPG);
    
     CCRect getBondingBox();
    
     CCRect getBondingBox2();
    
     CCRect getZuDangBox();
    
     CCRect getAttackBox();
    
     bool isFight(ARPG* p);
    
     void delHp(int hp);   //精灵掉血逻辑
    
     virtual void die();
    
     void suffer(ARPG* attcker,int attackType);  //1攻击者，2攻击类型
 
     virtual void doActionsByTag(CCObject* pSender);//根据m_tag播放动画
    
     virtual void setAction(int actID);
    
     virtual void setAction(int actionID,int times);
    
     virtual void actionCallback(CCArmature *pArmature, MovementEventType eventType, const char *animationID);
    
     void initAni(const char* rs);
    
     void update(float dt);
    
     virtual void beAttackCallFuncO(CCObject* pSender);
    
     virtual void beAttackCallFuncO1(CCObject* pSender);
    
     virtual void beAttackFlyCallFuncO(CCObject* pSender);
    
     virtual void doScrollByVertical(CCObject* pSender);//以Y轴为轴心旋转
    
     virtual void stopScrollByVertical(CCObject* pSender);//停止沿Y轴旋转

     virtual void doUpdateScroll(float dt);//更新旋转动画
    
     void attackJiangzhi();
    
     void resumeJiangzhi(CCObject* pSender);
    
     virtual void hitEffect();
    
     void attackEffect(CCPoint p);
    
     void skillEffect(CCPoint p,int index);
    
     void stopScrollByVertical2();
    
     bool hasScheduled;//是否已经做过时间调度
    
     CCPoint origiAnchor;//最初的锚点
    
     int scheduleCount;//调度计数
    
     float origiScale;//最初的scale因数
    
     CCRect effectRect;
    
     CCRect bodyRect;

     CC_SYNTHESIZE(bool, isEffectAttack, IsEffectAttack);
    
     float wudiTime;
    
    
};

#endif /* defined(__King__ARPG__) */
