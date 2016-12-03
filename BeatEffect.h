//
//  BeatEffect.h
//  King
//
//  Created by mac on 14-3-29.
//
//

#ifndef __King__BeatEffect__
#define __King__BeatEffect__

#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;
using namespace std;

#define REDUCESPEEDSPACE 5 //减速点
#define BOUNCEHIGHT 10 //下落后回弹高度
#define MINFRAMESPACE 0.08f //最小的播放帧间隔
#define MINFLOAT 0.00001 //可以当0处理的最小浮点值
enum
{
    kAttack_None,
    kAttack_beHitBack,//击退
    kAttack_beHitFloat, //浮空
    kAttack_beHitDaoDiChuo, //倒地磋
    kAttack_beHitFloatScrollDown, //浮空旋转落下
    kAttack_beHitDown, //被击倒
    kAttack_beHitScrollDown, //被击倒
    kAttack_beHitSkyDown, //空下劈
    kAttack_beHitForceHit //破防攻击
};//受击类型

enum{
    kAnimation_tag_Jump,
};//动画的tag

class BeatEffect:public CCNode
{
    CCNode* m_delegate;
    
    float m_beAttackDelay;//受击僵直时间
    
    int m_intGroundH;//受击的离地值
    
    int m_addedGroundH;//当前离地值，在变动
    
    int m_attackType;//当前的受击类型
    
    int m_distanceX;//受击时水平击退距离
    
    CCPoint m_origiPos;//当前delegate 的最初位置
    
    CCPoint m_newNodePos;//m_delegate 在Node级别的位置
    
    float incrementY;//y方向的增量
    
    float m_reduceSpeed;//减速
    
public:
    int direction;//受击方向
    
    BeatEffect();
    
    virtual ~BeatEffect();
    
    static BeatEffect* create(CCNode* delegate);
    
    static BeatEffect* create(CCNode* delegate,int attackID,int sufferDir);
    
    void executeAnimationAndAction(int attackID);
    
    void setAttackDirection(int dir)
    {
        this->direction = dir;
    };
    
    void doShakeLeftAndRight(CCObject* pSender);//左右震动,@param 僵直时间
    
    /*//被击退，dis 击退距离，backTime 整个击退过程的赶时间，stdTimeSpa 间隔多久站立 ，sufferdelay 震动僵直时间*/
    void beHitBack(CCCallFuncO* callback,int dis,float backTime,float stdTimeSpa,int sufferDelay = 1,bool reduce = true);
    
    /*被击浮空, groundH 离地值，dis 水平总位移，secDis 落地回弹水平位移, firTime 第一段浮空时间，secTime 回弹时间，stdspace 间隔多久站立，
     redtime 速度减多少倍，sufferdelay 震动僵直时间*/
    void beHitFloatSky(CCCallFuncO* callback,int groundH,int dis,int secDis,float firTime,float secTime,float stdSpace,float redTime,float sufferDelay = 1.0);
    
    /*//被击，倒地磋 groundH 离地值，dis 水平总位移，secDis 落地回弹水平位移, firTime 第一段浮空时间，secTime 回弹时间，thtime 整个倒地搓总时间，stdspace 间隔多久站立，
     redtime 速度减多少倍，sufferdelay 震动僵直时间*/
    void beHitDwonAndMove(CCCallFuncO* callback,int groundH,int dis,int secDis,float firtime,float sectime,float thtime,float stdspace,float redtime,int sufferDelay = 1);
    
    /*//翻倒地 dis 水平总位移，firTime 第一段浮空时间，secTime 回弹时间，stdspace 间隔多久站立，sufferdelay 震动僵直时间*/
    void beHitScrollDwon(CCCallFuncO* callback,int dis,float firtime,float sectime,float stdtime,int sufferDelay = 1);
    
    /*//浮空旋转 groundH 离地值，dis 水平总位移，secDis 落地回弹水平位移, firTime 第一段浮空时间，secTime 回弹时间,stdspace 间隔多久站立，
     redtime 速度减多少倍，sufferdelay 震动僵直时间*/
    void beHitFloatScrollDwon(CCCallFuncO* callback,int groundH,int dis,int secdis,float firtime,float sectime,float stdspace,float redtime,int sufferDelay = 1);
    
    /*/空下劈 dis 水平总位移，secDis 落地回弹水平位移, firTime 被打到地上的时间，secTime 回弹时间,stdspace 间隔多久站立，sufferdelay 震动僵直时间*/
    void beHitSkyHitDwon(CCCallFuncO* callback,int dis,int secdis,float firtime,float sectime,float stdspace,float sufferDelay = 1);
    
    void beHitDown(CCCallFuncO* callback,int sufferDelay = 1);//击倒 sufferDelay 受击僵直时间
    
    /*//破防攻击 groundH 离地值，dis 水平总位移，secDis 落地回弹水平位移, firTime 第一段浮空时间，secTime 回弹时间,stdspace 间隔多久站立，sufferdelay 震动僵直时间*/
    void beHitPowerful(CCCallFuncO* callback,int groundH,int dis,int secdis,float firtime,float sectime,float stdspace,int sufferDelay = 10);
    
    void updateAnimation(float dt);//更新当前播放的动画
    
    void cleanMemenbers();//清除成员数据
    
    void beFallDown();
};
#endif /* defined(__King__BeatEffect__) */
