//
//  Hero.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//
#include "Hero.h"
#include "Game.h"
#include "Define.h"
#include "Hero_Help.h"
#include "PersonalAudioEngine.h"
#include "GameData.h"
#include "Effect.h"
#include "Ef.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define ANDROID_CLASS_NAME1 "com/vemobi/fight/fight"
//"gedou/mofeng/cn/ooo"
#define ANDROID_FUNCTION_NAME1 "addXueTong"
//#define ANDROID_FUNCTION_NAME "charge"
#define ANDROID_PARAM_TYPE "(Ljava/lang/String;Ljava/lang/String;)V"

Hero::Hero()
:ARPG()
{
    hasCollisionNum = 0;
    isHaveFuhuo = false;
    isSkill1 = false;
    isSkill2 = false;
    isSkill3 = false;
    isSkill4 = false;
    isBeAttack = false;
    bottomH = 3;
    isCanDirect = true;
    shadow2 = NULL;
    isZudang = false;
}
bool Hero::init()
{
    isJiXuSkill1 = true;
	isJiXuSkill2 = true;
    daodiTime = 20;
    daodiqishenID = 0;
    isdaodiqishen = false;
    isJinjiDuobi = false;
    qianqianNum = 0;
    isqianqian = false;
    this->isCollision = true;
    this->setDP(KingData->getFangyuLevel());
    isCommanAttack = false;
    commanAttackIndex = 0;
    skillAnimationId = 0;
    skill2AnimationId = 0;
    skill3AnimationId = 0;
    skill4AnimationId = 0;
    maxHp = KingData->HEROHP;   //初始化英雄的最大血量
    hp = maxHp;             //初始化的时候当前血量为最大血量
    this->setAttackP(KingData->HEROATK);  //初始化英雄的攻击力
    this->setAttackPP(attackP);


    safe_time = 0;   //开始的时候可以被攻击
    lianjiNum = 0;
    lianjiTime = 50;
    type = 1;
    downAtk =0;
    doubleHit_Type = 0;
    isActionEnding = true;
    doubleHit_Save = 0;
    atkCount = 0;
    orientation = HOLDER;
    speedMain = 300;
    initAni("role1");
    commanAttackResumeNum = 4;
    nuqi = maxNengliangdou*100 + 99;
    this->stand();
    this->s->setScaleX(1);
    this->schedule(schedule_selector(Hero::commanAttackResume),0.032f);
    this->scheduleUpdate();
    return true;
}

void Hero::update(float dt)
{
	if (m_canSkill && m_useSkill != 0)
	{
		skill_time += dt;
		if (skill_time >= 1)
		{
			skill_time = 0;
			m_useSkill = 0;
		}
	}

	if (m_canSkill)
	{
		if (m_useSkill != 0 && this->nuqi + KingData->getExtraNuqi() >= 300)
		{
			switch (m_useSkill)
			{
			case 1:
				skill1();
				break;
			case 2:
				skill2();
				break;
			case 3:
				skill3();
				break;
			case 4:
				skill4();
				break;
			}
			skill_time = 0;
			m_useSkill = 0;
		}
	}
	

    if (isqianqian) {
        qianqianNum++;
    }else
    {
        qianqianNum = 0;
    }
    
    if (isBeAttack)
    {
        if (daodiTime > 0)
        {
            daodiTime -- ;
        }else
        {
            if (this->s->getPositionY()<0.001f &&(this->s->getPositionX() < 0.001f && this->s->getPositionX() > -0.001f) )
            {
                isBeAttack = false;
            }
            daodiTime = 20;
        }
    }
    if(this->isCommanAttack || this->isSkill1 || this->isSkill2 || this->isSkill3 || this->getChildByTag(shandianEffectTag) || this->isdaodiqishen)
    {
        this->setZOrder(10001);
    }else
    {
        this->setZOrder(0);
    }
    if(this->getChildByTag(yanmuEffectTag) != NULL)
    {
         Ef* ef = dynamic_cast<Ef*>(this->getChildByTag(yanmuEffectTag));
         CCSize size = this->s->getContentSize();
         ef->setScaleX(this->s->getScaleX());
         ef->setPositionY(this->bottomH);
         ef->setPositionX(-1*this->s->getScaleX()*size.width/3);
    }
    if(this->getChildByTag(juqiEffectTag) == NULL &&this->getChildByTag(shandianEffectTag) == NULL)
    {
        this->effectRect = CCRect(0, 0, 0, 0);
    }
    if(!this->s->getActionByTag(JumpTag) && this->getParent()==gameLayer)
    {
        this->s->setPositionY(0);
        this->setPositionY( SIZE.height/4 + this->bottomH );
    }
    ARPG::update(dt);
    if(this->isCanDirect)
    {
        if (orientation == RIGHT)
        {
            s->setScaleX(1);
        }else if (orientation == LEFT)
        {
            s->setScaleX(-1);
        }
    }
    if(lianjiNum > 0) //连击数逻辑
    {
        lianjiTime--;
        if(lianjiTime <=0)
        {
            lianjiNum = 0;
        }
    }
    if (safe_time > 0)     //安全时间逻辑。
    {
        safe_time--;
    }
    
    if(!isScrolling)
    {
        this->s->setAnchorPoint(ccp(0.45,0));
    }
    if(shadow2!=NULL)
    {
        shadow2->setPositionX(this->getPositionX() + this->s->getPositionX() );
        shadow2->setAnchorPoint(ccp(0.5 ,0.5));
        shadow2->setPositionY(this->getPositionY() + 1.2*this->bottomH);
    }
    
}

Hero::~Hero()
{
  //  Game::instance()->setHero(NULL);

    CCLOG("~Hero");
}

void Hero::qianqian(int dir)
{
    if(this->isBeAttack)
    {
        return;
    }
    
    
    if(this->isDie)
    {
        return;
    }
    if(Role->isSkill2 || Role->isSkill1 || Role->isSkill3 || Role->isSkill4)
    {
        return;
    }
    if (orientation == HOLDER)
    {
        return;
    }

    
    float time = 0.5f;
    setAction(1);
    m_state = s_move;
    CCMoveBy* act = CCMoveBy::create(time, ccp( dir*200, 0));
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::qianqianCallback));
    CCArmature* s2  =addMotion(act,2*time);
    moveTo(s2, 2*time, 300*this->s->getScaleX());
    CCSequence* seq = CCSequence::create(act,call,NULL);
    seq->setTag(5555);
    this->runAction(seq);
}

void Hero::qianqianCallback()
{
    isqianqian = false;
}

void Hero::move()
{
    if (isqianqian)
    {
      return;
    }
    
    if(this->isBeAttack || this->isdaodiqishen)
    {
        return;
    }else if(m_state==s_attack)
    {
        return;
    }
    if(this->isSkill2 || this->isSkill1 || this->isSkill3 || this->isSkill4)
    {
        this->stopActionByTag(999);
        return;
    }
    
    if (gameLayer !=NULL &&   gameLayer->isGameOver)
    {
        this->wudi = true;
    }else
    {
         this->wudi = false;
    }
    m_state = s_move;
    this->s->getAnimation()->setSpeedScale(0.8);
    setAction(1);
    flipDir();
}

void Hero::setAction(int actionID)
{
    ARPG::setAction(actionID);
}

void Hero::commanAttack()
{
    if(this->isBeAttack || isdaodiqishen)
    {
        return;
    }
    if (isSkill1)
    {
        isJiXuSkill1 = true;
        return;
    }
    if (isSkill2)
    {
        isJiXuSkill2 = true;
        return;
    }

    if( this->m_state == s_skill)
    {
        return;
    }
    if(this->isSkill2 || this->isSkill1)
    {
        return;
    }
  
    isCommanAttack = true;
    m_state = s_attack;
    this->setAttackType(1);
    this->attackPP = 3*this->attackP;
    if(commanAttackIndex == 0)
    {
         if(actionID!=19)
         {
             PersonalAudioEngine::sharedEngine()->playEffect("music/zhugongji1.mp3");
         }
         animation->setSpeedScale(1.5);
         setAction(19,1);
    }else if (commanAttackIndex == 1)
    {
        if(actionID!=5)
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/zhugongji1.mp3");
        }
        animation->setSpeedScale(1.5);
        setAction(5,1);
    }
    else if (commanAttackIndex ==2 )
    {
        if(actionID!=22)
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/zhugongji1.mp3");
        }
        animation->setSpeedScale(1.5);
        setAction(22,1);
    }else if (commanAttackIndex ==3)
    {
        if(actionID!=7)
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/zhugongji2.mp3");
        }
        this->wudi = true;
        animation->setSpeedScale(1.5);
        this->setAttackType(6);
        setAction(7,1);
    }else if(commanAttackIndex == 4)
    {
        if(actionID!=25)
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/titui.mp3");
        }
        animation->setSpeedScale(2);
        this->setAttackType(4);
        setAction(25,1);
        if(this->getChildByTag(tituiEffectTag) == NULL)
        {
            Ef* ef = Ef::create("tx_ti");
            this->setZOrder(100000);
            this->addChild(ef,this->getZOrder()+1000,tituiEffectTag);
            CCSize size = this->s->getContentSize();
            int direction = this->s->getScaleX();
            ef->setPosition(ccp(direction*size.width*5/10,size.height/2));
            ef->setScaleX(direction);
        }
    }
    
    
    if(delegate)
    {
        delegate->actionDidAttack(this);
    }
}

void Hero::jumpRise(int height,float time,CCPoint p,int jumpTimes)  //跳起
{
    CCCallFunc* jumpCallback = CCCallFunc::create(this, callfunc_selector(Hero::jumpCallback));
    CCSequence* seq =  CCSequence::create(CCJumpBy::create(time, ccp(0,0),height , jumpTimes),jumpCallback,NULL);
    this->s->runAction(seq);
    this->runAction(CCMoveBy::create(time, p));
    seq->setTag(JumpTag);
}

void Hero::jumpCallback()
{
    this->s->stopAllActions();
}

void Hero::qianxiaqian(const char* name)
{
    Ef* effect = Ef::create(name);
    this->addChild(effect,10000,qianxiaqianEffectTag);
    CCSize size = this->s->getContentSize();
    effect->setScaleX(0.8*this->s->getScaleX());
    effect->setPositionY(-size.height/3);
    effect->setPositionX(size.width*0.1*this->s->getScaleX());
}

void Hero::actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID)
{
    if (eventType == START) {
        
        this->setZOrder(10000);
        
        if(actionID == 19)
        {
            commanAttackResumeNum  = 14;
            
        }else if (actionID == 5)
        {
            commanAttackResumeNum  = 14;
            
        }else if (actionID == 22)
        {
            commanAttackResumeNum  = 18;
        }
        else if(actionID == 7)
        {
            this->qianxiaqian("tx_qianxiaqian");
            commanAttackResumeNum  = 24;
            jumpRise(100,0.032*24,ccp(0,0),1);
            
        }else if(actionID == 25)
        {
            commanAttackResumeNum=25;
        }
        
    }
    if (eventType == COMPLETE)
    {
        
        if(actionID == 19)
        {
            this->attackEffect(ccp(0,0));
            
        }else if (actionID == 5){
            
            this->attackEffect(ccp(-10,15));
            
        }else if (actionID == 22){
  
            this->attackEffect(ccp(0,0));
        }
        else if(actionID == 7)
        {
            this->wudi = false;
        }
        if(isCommanAttack)
        {
            commanAttackIndex++;
            orientation = HOLDER;
        }

        if(commanAttackIndex == 5 && m_state == s_attack )
        {
            gameLayer->screenShake(5, 10);
            commanAttackIndex = 0;
        }
        this->setZOrder(0);
        if(delegate)
        {
            delegate->actionDidAttack(this);
        }
        if(this->type!= 1)
        {
            if(this->actionID !=1)
            {
                this->setAction(1);
            }
        }else
        {
            if(this->actionID !=0 && !this->isSkill1 && !this->isSkill2 && !this->isSkill3)
            {
                if(this->actionID!=7)
                {
                      this->setAction(0);
                }

                m_state = s_stand;
                isBeAttack =false;
            }
        }
    }
    if (eventType == LOOP_COMPLETE)
    {
        
    }
}

void Hero::commanAttackResume(float dt)
{
    commanAttackResumeNum--;
    if(commanAttackResumeNum < 0)
    {
        if(this->actionID == 7)
        {
            this->setAction(0);
        }
        isCommanAttack = false;
        commanAttackIndex = 0;
    }
}

void Hero::setAction(int actionID,int times)
{
    int animationNum =  animation->getMovementCount(); //动画数

    if (animation == NULL ||animationNum ==0 )
        return;
    if (actionID <0 || actionID > animationNum)
    {
        actionID = 0;
    }
    if (this->actionID!=actionID)
    {
        this->actionID = actionID;
        this->animation->setMovementEventCallFunc(this, SEL_MovementEventCallFunc(&Hero::actionCallback));    //动画完成后的回调
        animation->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&Hero::collison));
        if(times == 1 ||times == 0)
        {
            animation->playWithIndex(actionID,-1,-1,0);    //攻击一次不循环
        }
        else
        {
            animation->playWithIndex(actionID,-1,-1,times);    //攻击一次不循环
        }
    }
}

void Hero::autoNormalAttact() //当前攻击时间  － 上次攻击的时间 > 安全时间    coding
{
    if (startNormalAttact)
    {
        if ( millisecondNow() - lastNormalAttactTime > NA_SLEEP_TIME)
        {
            downCount = 0;  //方向键第几次按下了
            downAtk = 1;  //功能键第几次按下
            lastNormalAttactTime = millisecondNow();
        }
    }
}

void Hero::setIsARPG_Acion(int ARPG_Acion) 	/** 设置功能键 改变当前的功能键状态 设置为-1取消功能键 */
{
    if (isFly)
        return;
    if(isActionEnding!=ARPG_Acion)
    {
        doubleHit_Save = ARPG_Acion;
    }else
    {
        if (doubleHit_Type == HERO_FISTN)
        {
            if(atkCount < 2)
            {
                atkCount++;
            }
        }else if (doubleHit_Type == HERO_Leg)
        {
            if (atkCount < 2)
            {
                atkCount++;
            }
        }
    }
}

void Hero::daodiqishen()
{
	//如果没有学受身的技能 并且没有死亡的情况下 站起来
    if (!KingData->getShoushen() && !this->isDie)
    {
        this->stand();
        return;
    }
    //如果学习了受身技能 或者 死亡的情况下
    isBeAttack = false;
    isdaodiqishen = true;
    switch (daodiqishenID) {
        case 0:
        {
            this->stopAllActions();
            this->s->stopAllActions();
            
            if (this->isDie)//
            {
                if (gameLayer!=NULL && gameLayer->modeID == 1)
                {
                    gameLayer->setRemainTime(gameLayer->getRemainTime() + 60);
                }
            }
            gameLayer->screenShake(10, 20);
            daodiqishenID++;
            CCSize size = this->s->getContentSize();
            this->s->getAnimation()->playWithIndex(12);
            CCDelayTime* delay = CCDelayTime::create(0.5);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::daodiqishen));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->wudi = true;
            this->runAction(seq);
            PersonalAudioEngine::sharedEngine()->playEffect("music/dazhao.mp3");
            skill1end("tx_juqi",CCPoint(0.3*this->s->getScaleX()*size.width,size.height*0.7));
            break;
        }
        case 1:
        {
				  //倒地
				  HUB->shoushenAction();

            daodiqishenID++;
            isdaodiqishen = true;
            CCSize size = this->s->getContentSize();
            float randx = CCRANDOM_0_1();
            Ef* ef;
            Ef* ef2;
            if (randx<0.33) {
                ef = Ef::create("tx_shandian");
                ef2 = Ef::create("tx_shandian");
            }else if (randx>0.33 && randx<0.66)
            {
                ef = Ef::create("tx_shandian2");
                ef2 = Ef::create("tx_shandian2");
            }else
            {
                ef = Ef::create("tx_shandian2",1);
                ef2 = Ef::create("tx_shandian2",1);
            }
            this->setAttackType(3);
            this->addChild(ef, 1000, shandianEffectTag);
            this->addChild(ef2, 1000, shandianEffectTag);
            ef->setPositionX(-100);
            ef2->setPositionX(100);
            CCRect rect ;
            rect.origin = gameLayer->convertToNodeSpace(ccp(0, 0));
            rect.size =SIZE;
            this->effectRect = rect;
            this->delegate->actionDidAttack(this);
            PersonalAudioEngine::sharedEngine()->playEffect("music/baoqi.mp3");
            skill1end("tx_juqibao",CCPoint(0.3*this->s->getScaleX()*size.width,size.height*0.7));
            zadi2();
            CCDelayTime* delay = CCDelayTime::create(0.8);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::daodiqishenCallback));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            break;
            
        }
        default:
			int i = 0;
            break;
    }
}

void Hero::daodiqishenCallback(CCObject* pSender)
{
    daodiqishenID = 0;
    setAction(0);
    if (gameLayer !=NULL &&   gameLayer->isGameOver)
    {
          this->wudi = true;
    }else
    {
          this->wudi = false;
    }

    isdaodiqishen = false;
    if (this->isDie)
    {
        this->setHP(this->getMaxHp());
        this->isDie = false;
        
        this->stand();
        this->s->getAnimation()->playWithIndex(0);

    }
}

void Hero::showInfo(int id)
{
	CCLOG("ShopBuy::showInfo");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	jobject jobj;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, ANDROID_CLASS_NAME1,
		ANDROID_FUNCTION_NAME1,
		"(I)V");
	if (isHave)
	{
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id);

	}
	else
	{

	}
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	SHOP->C_backAction(id);
#endif

}

void Hero::skill1()
{
    if (!HUB->canTouch)
    {
        return;
    }
    
    if (!HUB->isTeach)
    {
        if (gameLayer!=NULL && !gameLayer->isGameStart)
        {
            return;
        }
        
        if(this->isBeAttack || isdaodiqishen)
        {
            return;
        }
        if (Role->isDie)
        {
            return;
        }
    }else
    {
        if (HUB->teachID != 4)
        {
            return;
        }
    }
    
    if (gameLayer->getIsPause())
    {
        return;
    }
    if (isSkill1 || isSkill2 || isSkill3)
    {
        return;
    }
    
    
    if (HUB->isTeach) {
        if (HUB->teachID == 4)
        {
            isSkill1 = true;
            skillAnimationId = 0;
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            this->runAction(call);
			CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill1TimerTag));
            timer1->setPercentage(0);
            CCProgressTo* progress = CCProgressTo::create(10, 100);
            timer1->runAction(progress);
            HUB->teachID  = 5;
        }
    }else
    {
		CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill1TimerTag));
		//第一个技能 消耗1点怒气
		int nuqi = 100;
		if (timer1->getPercentage() == nuqi)
		{
			if ((this->nuqi + KingData->getExtraNuqi()) >= nuqi)
			{
				if (this->nuqi >= nuqi)
				{
					Role->nuqi = Role->nuqi - nuqi;
				}
				else
				{
					KingData->setExtraNuqi(KingData->getExtraNuqi() - nuqi);
				}
				isSkill1 = true;
				skillAnimationId = 0;
				CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
				this->runAction(call);
				timer1->setPercentage(0);
				CCProgressTo* progress = CCProgressTo::create(10, 100);
				timer1->runAction(progress);
			}
			else
			{
				if (KingData->getMoney() >= 10000)
				{
					KingData->setMoney(KingData->getMoney() - 10000);
					KingData->setExtraNuqi(KingData->getExtraNuqi() + 1000);
					//计费点
					//SHOP->showNuqi(10);
					Game::instance()->getShopLayer()->showInfo(11);
				}
				else
				{
					//关闭跳转到金币界面
					//qiehuanCallback(2);   ///////////////
					//计费点
					m_useSkill = 1;
					Game::instance()->getShopLayer()->showInfo(15);

				}
				//gameLayer->shop(30);
			}
		}
    }
}

void Hero::skill1(CCObject* pSender)
{
	skill1();
}

void Hero::skill2()
{
   
    if (!KingData->getBazhinv())
    {
		//if no this skill
		Game::instance()->getShopLayer()->showInfo(8);//
        //timer1->setPercentage(0);
        return;
    }
    
    if (!HUB->canTouch)
    {
        return;
    }
    
    if (!gameLayer->isGameStart || isdaodiqishen)
    {
        return;
    }
    if (Role->isDie)
    {
        return;
    }
    if(this->isBeAttack || isdaodiqishen)
    {
        return;
    }
    if (gameLayer->getIsPause())
    {
        return;
    }
    if (isSkill1 || isSkill2 || isSkill3 || isSkill4)
    {
        return;
    }
   
	//第2个技能 消耗2点怒气
	CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill2TimerTag));
	int nuqi = 200;
	if (timer1->getPercentage() == 100)
	{
		if ((this->nuqi + KingData->getExtraNuqi()) >= nuqi)
		{
			if (this->nuqi >= nuqi)
			{
				Role->nuqi = Role->nuqi - nuqi;
			}
			else
			{
				KingData->setExtraNuqi(KingData->getExtraNuqi() - nuqi);
			}
			isSkill2 = true;
			skill2AnimationId = 0;
			CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
			this->runAction(call);
			timer1->setPercentage(0);
			CCProgressTo* progress = CCProgressTo::create(10, 100);
			timer1->runAction(progress);
		}
		else
		{
			if (KingData->getMoney() >= 10000)
			{
				KingData->setMoney(KingData->getMoney() - 10000);
				KingData->setExtraNuqi(KingData->getExtraNuqi() + 1000);
				//计费点
				//SHOP->showNuqi(10);
				Game::instance()->getShopLayer()->showInfo(11);
			}
			else
			{
				//关闭跳转到金币界面
				//qiehuanCallback(2);   ///////////////
				//计费点
				m_useSkill = 2;
				Game::instance()->getShopLayer()->showInfo(15);

			}
			//gameLayer->shop(30);
		}
	}
}

void Hero::skill2(CCObject* pSender)
{
	skill2();
}

void Hero::skill3()
{
   
    if (!KingData->getBajiubei())
    {
		//if no this skill
		Game::instance()->getShopLayer()->showInfo(9);//
        //timer1->setPercentage(0);
        return;
    }
    
    if (!HUB->canTouch)
    {
        return;
    }
    
    if (!gameLayer->isGameStart)
    {
        return;
    }
    
    if(this->isBeAttack || isdaodiqishen)
    {
        return;
    }
    
    if (Role->isDie)
    {
        return;
    }
    if (gameLayer->getIsPause())
    {
        return;
    }
    if (isSkill1 || isSkill2 || isSkill3 || isSkill4)
    {
        return;
    }
   
	//第3个技能 消耗1点怒气
	CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill3TimerTag));
	int nuqi = 300;
	if (timer1->getPercentage() == 100)
	{
		if ((this->nuqi + KingData->getExtraNuqi()) >= nuqi)
		{
			if (this->nuqi >= nuqi)
			{
				Role->nuqi = Role->nuqi - nuqi;
			}
			else
			{
				KingData->setExtraNuqi(KingData->getExtraNuqi() - nuqi);
			}
			isSkill3 = true;
			skill3AnimationId = 0;
			CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill3Action));
			this->runAction(call);
			timer1->setPercentage(0);
			CCProgressTo* progress = CCProgressTo::create(2.5, 100);
			timer1->runAction(progress);
		}
		else
		{
			if (KingData->getMoney() >= 10000)
			{
				KingData->setMoney(KingData->getMoney() - 10000);
				KingData->setExtraNuqi(KingData->getExtraNuqi() + 1000);
				//计费点
				//SHOP->showNuqi(10);
				Game::instance()->getShopLayer()->showInfo(11);
			}
			else
			{
				//关闭跳转到金币界面
				//qiehuanCallback(2);   ///////////////
				//计费点
				m_useSkill = 3;
				Game::instance()->getShopLayer()->showInfo(15);

			}
			//gameLayer->shop(30);
		}
	}
}

void Hero::skill3(CCObject* pSender)
{
	skill3();
}

void Hero::skill4()
{
	if (!KingData->getJinjiDuobi())
	{
		Game::instance()->getShopLayer()->showInfo(23);//
		return;
	}


    if (!HUB->canTouch)
    {
        return;
    }
    
    if (HUB->isTeach)
    {
        return;
    }
   
    if (Role->isDie)
    {
        return;
    }
    if (gameLayer->getIsPause())
    {
        return;
    }
    if (isSkill1 || isSkill2 || isSkill3 || isSkill4)
    {
        return;
    }
    if (this->isdaodiqishen) {
        return;
    }
    
	//第4个技能 消耗1点怒气
	CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill4TimerTag));

	//第4个技能 消耗1点怒气
	if (timer1->getPercentage() == 100)
	{
		if ((this->nuqi + KingData->getExtraNuqi()) >= 100)
		{
			if (this->nuqi >= 100)
			{
				Role->nuqi = Role->nuqi - 100;
			}
			else
			{
				KingData->setExtraNuqi(KingData->getExtraNuqi() - 100);
			}
			PersonalAudioEngine::sharedEngine()->playEffect("music/shanbi.mp3");
			this->wudi = true;
			this->isJinjiDuobi = true;
			isSkill4 = true;
			skill4AnimationId = 0;
			CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill4Action));
			this->runAction(call);
			timer1->setPercentage(0);
			CCProgressTo* progress = CCProgressTo::create(2, 100);
			timer1->runAction(progress);
		}
		else
		{
			if (KingData->getMoney() >= 10000)
			{
				KingData->setMoney(KingData->getMoney() - 10000);
				KingData->setExtraNuqi(KingData->getExtraNuqi() + 1000);
				//计费点
				//SHOP->showNuqi(10);
				Game::instance()->getShopLayer()->showInfo(11);
			}
			else
			{
				//关闭跳转到金币界面
				//qiehuanCallback(2);   ///////////////
				//计费点
				m_useSkill = 4;
				Game::instance()->getShopLayer()->showInfo(15);

			}
			//gameLayer->shop(30);
		}
	}
}

void Hero::skill4(CCObject* pSender)
{
	skill4();
}

void Hero::skill_ss(CCObject* pSender)
{
	if (!KingData->getShoushen())
	{
		Game::instance()->getShopLayer()->showInfo(24);//
		return;
	}
}



void Hero::skill4Action(CCObject* pSender)
{
    switch (skill4AnimationId) {
        case 0:
        {
            gameLayer->screenShake(20, 5);
            skill4AnimationId++;
            this->wudi = true;
            this->isCollision = false;
            setAction(23, 1);
            float time = 10* 0.032f;
            moveTo(this, time, SIZE.width*this->s->getScaleX()/2);
            CCDelayTime* delay = CCDelayTime::create(3*time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill4Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            moveTo(s2, 2*time, SIZE.width*this->s->getScaleX()/2);
            CCArmature* s3  =addMotion(seq,2*time);
            moveTo(s3, 3*time, SIZE.width*this->s->getScaleX()/2);
            shanbi();
            this->runAction(seq);
            break;
        }
        case 1:
        {
            this->wudi = true;
            skill4AnimationId++;
            float time = 10* 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill4Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
        }
        case 2:
        {
            isSkill4 = false;
            this->s->getAnimation()->setSpeedScale(1.0f);
            offMove = false;
            this->wudi = false;
            this->isJinjiDuobi = false;
            setAction(0);
            m_state = s_stand;
            this->stopAllActions();
            skill4AnimationId = 0;
        }
        default:
            break;
    }
}




void Hero::shanbi()
{
    Ef* ef = Ef::create("tx_duobi");
    this->addChild(ef,10000,duobiEffectTag);
    CCSize size = this->s->getContentSize();
    ef->setPositionY(this->bottomH);
    ef->setScaleX(this->s->getScaleX());
    ef->setPositionX(this->s->getScaleX()*(-200));
    CCRect rect ;
    rect.origin = gameLayer->convertToNodeSpace(ccp(0, 0));
    rect.size = SIZE;
    this->effectRect = rect;
    if (delegate && (skillAnimationId == 202) )
    {
        this->delegate->actionDidAttack(this);
    }
}

void Hero::skill1Action()
{
    orientation = HOLDER;
    this->setZOrder(60000);
    skillAnimationId = skillAnimationId+1;
    this->wudi = true;
    m_state = s_skill;
    switch (skillAnimationId) {
        case 1:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/dazhao.mp3");
            isCanDirect = false;
            offMove = true;
            setAction(13, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time = 13* 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            addMotion(seq,2*time);
            this->runAction(seq);
            CCSize size = this->s->getContentSize();
            skill1end("tx_juqi",CCPoint(0.3*this->s->getScaleX()*size.width,size.height*0.7));
            this->setAttackType(7);
            break;
        }
        case 2:
        {
            offMove = true;
            setAction(13, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time = 13* 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            CCSize size = this->s->getContentSize();
            PersonalAudioEngine::sharedEngine()->playEffect("music/baoqi.mp3");
            skill1end("tx_juqibao",CCPoint(0.3*this->s->getScaleX()*size.width,size.height*0.7));
            this->setAttackType(7);
            break;
        }
        case 3:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie1.mp3");
            offMove = false;
            yanmu();
            setAction(23, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time = 20* 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 100*this->s->getScaleX());
            moveTo(s2, 5*time, 100*this->s->getScaleX());
            this->setAttackType(8);
            break;
        }
        case 4:
        {
        
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie2.mp3"/*.wav*/);
            isCanDirect = true;
            this->skillEffect(ccp(0,0),0);
            setAction(20, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time = 20 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 5:
        {
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie1.mp3");
            this->skillEffect(ccp(0,0),2);
            setAction(16, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time = 15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 6:
        {
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie2.mp3"/*.wav*/);
            this->skillEffect(ccp(0,0),1);
            setAction(24, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 7:
        {
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie1.mp3");
            this->skillEffect(ccp(0,0),0);
            setAction(20,1);
            this->s->getAnimation()->setSpeedScale(2);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 8:
        {
            
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie2.mp3"/*.wav*/);
            setAction(14, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 9:
        {
            
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie2.mp3"/*.wav*/);
            this->skillEffect(ccp(0,0),2);
            setAction(16, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 10:
        {
            
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie1.mp3");
            this->skillEffect(ccp(0,0),1);
            setAction(24, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 11:
        {
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie2.mp3"/*.wav*/);
            this->skillEffect(ccp(0,0),0);
            setAction(20, 1);
            this->s->getAnimation()->setSpeedScale(2);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 12:
        {
            if (isJiXuSkill1)
            {
				isJiXuSkill1 = true;
            }
            else
            {
                skillAnimationId = 202;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie1.mp3");
            skillAnimationId = 100;
            setAction(15, 1);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            this->s->getAnimation()->setSpeedScale(1);
            break;
        }
        case 101:
        {
            offMove = true;
            this->orientation = HOLDER;
            setAction(17, 1);
            this->s->getAnimation()->pause();
            float time =8 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->stopAllActions();
            this->runAction(seq);
            this->setAttackType(7);
            CCSize size = this->s->getContentSize();
            skill1end("tx_juqi",CCPoint(0.2*this->s->getScaleX()*size.width,size.height));
            skillAnimationId = 200;
            break;
        }
        case 201:
        {

            this->s->getAnimation()->pause();
            offMove = true;
            this->orientation = HOLDER;
            float time =8 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->stopAllActions();
            this->runAction(seq);
            this->setAttackType(7);
            CCSize size = this->s->getContentSize();
            skill1end("tx_juqibao",CCPoint(0.2*this->s->getScaleX()*size.width,size.height));
            break;
        }
        case 202:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/dazhao1.mp3");
            this->setZOrder(100000);
            offMove = true;
            this->orientation = HOLDER;
            setAction(26, 1);
            this->s->getAnimation()->resume();
            this->s->getAnimation()->setSpeedScale(0.5f);
            float time =15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill1Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(3);
            CCSize size = this->s->getContentSize();
            Ef*  ef =  this->skill1end("tx_bao1",CCPoint(1*this->s->getScaleX()*size.width,size.height/2));
            ef->setSpeed(0.8);
            gameLayer->screenShake(6, 20);
           
            break;
        }
        case 203:
        {
            if (HUB->isTeach)
            {
                HUB->teachID = 8;
            }
            this->s->getAnimation()->setSpeedScale(1.0f);
            offMove = false;
            isSkill1 = false;
            this->wudi = false;
            setAction(0);
            m_state = s_stand;
            this->stopAllActions();
            skillAnimationId = 0;
        }
    }
}

void Hero::moveTo(CCNode* node,float dt ,float x)
{
    CCMoveBy* moveBy =  CCMoveBy::create(dt, ccp(x,0));
    node->runAction(moveBy);
    moveBy->setTag(999);
}

CCArmature* Hero::addMotion(CCAction* act,float time)
{
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("res/role1/role1.ExportJson");
    CCArmature*  s2 = CCArmature::create("role1");
    s2->setAnchorPoint(ccp(0.4,0));
    gameLayer->addChild(s2,1000,1000);
    s2->runAction(act);
    s2->setOpacity(255*0.5);
    s2->setColor(ccc3(65,0,255));
    s2->setPosition(this->getPosition());
    s2->runAction(CCSequence::create(CCFadeOut::create(time),CCCallFuncN::create(s2, callfuncN_selector(Hero::removeMotion)),NULL) );
    if(s2!=NULL)
    s2->getAnimation()->play(s->getAnimation()->getCurrentMovementID().c_str());
    s2->setScaleX(s->getScaleX());
    return s2;
}

void Hero::removeMotion(CCObject* pSender)
{
    if (pSender!=NULL)
    {
        CCArmature* s2 =  dynamic_cast<CCArmature*>(pSender);
        s2->removeFromParentAndCleanup(true);
    }
}

void Hero::skill1Animation(float dt)
{
   setZOrder(60000);
}

void Hero::skill2Animation(float dt)
{
    setZOrder(60000);
}

void Hero::skill2Action(CCObject* pSender)
{
    orientation = HOLDER;
    this->setZOrder(60000);
    m_state = s_skill;
    isSkill2 = true;
    skill2AnimationId = skill2AnimationId+1;
    this->wudi = true;
    switch (skill2AnimationId) {
        case 1:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/dazhao.mp3");
            isCanDirect = false;
            setAction(11, 1);
            float time = 10 * 0.032f;
            this->s->getAnimation()->setSpeedScale(2);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(7);
            CCSize size = this->s->getContentSize();
            skill1end("tx_juqi",CCPoint(0.2*this->s->getScaleX()*size.width,size.height*0.9));
            break;
        }
        case 2:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/baoqi.mp3");
            setAction(11, 1);
            float time = 10 * 0.032f;
            this->s->getAnimation()->setSpeedScale(2);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(7);
            CCSize size = this->s->getContentSize();
            skill1end("tx_juqibao",CCPoint(0.2*this->s->getScaleX()*size.width,size.height*0.9));
            break;
        }
        case 3:
        {
            yanmu();
            setAction(23, 1);
            float time = 15 * 0.032f;
            this->s->getAnimation()->setSpeedScale(2);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 150*this->s->getScaleX());
            moveTo(s2, 5*time, 150*this->s->getScaleX());
            this->setAttackType(8);
            break;
        }
        case 4:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            isCanDirect = true;
            setAction(19, 1);
            float time =15 * 0.032f;
            this->s->getAnimation()->setSpeedScale(2);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 5:
        {
            if (isJiXuSkill2)
            {
				isJiXuSkill2 = true;
            }
            else
            {
                skill2AnimationId = 17;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            setAction(5, 1);
            float time = 15 * 0.032f;
            this->s->getAnimation()->setSpeedScale(2);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 6:
        {
            if (isJiXuSkill2)
            {
				isJiXuSkill2 = true;
            }
            else
            {
                skill2AnimationId = 17;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            setAction(20, 1);
            float time = 15 * 0.032f;
            this->s->getAnimation()->setSpeedScale(3);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 7:
        {
            if (isJiXuSkill2)
            {
				isJiXuSkill2 = true;
            }
            else
            {
                skill2AnimationId = 17;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            setAction(14, 1);
            float time = 25* 0.032f;
            this->s->getAnimation()->setSpeedScale(2);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 40*this->s->getScaleX());
            moveTo(s2, 5*time, 40*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 8:
        {
            if (isJiXuSkill2)
            {
				isJiXuSkill2 = true;
            }
            else
            {
                skill2AnimationId = 17;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            setAction(6, 1);
            float time =25 * 0.032f;
            this->s->getAnimation()->setSpeedScale(2);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 80*this->s->getScaleX());
            moveTo(s2, 5*time, 80*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 9:
        {
            if (isJiXuSkill2)
            {
				isJiXuSkill2 = true;
            }
            else
            {
                skill2AnimationId = 17;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            setAction(8, 1);
            float time = 2*animation->m_pMovementData->duration * 0.032f;
            this->s->getAnimation()->setSpeedScale(1);
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 80*this->s->getScaleX());
            moveTo(s2, 5*time, 80*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 10:
        {
            if (isJiXuSkill2)
            {
				isJiXuSkill2 = true;
            }
            else
            {
                skill2AnimationId = 17;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            setAction(9, 1);
            float time = 2*animation->m_pMovementData->duration * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 80*this->s->getScaleX());
            moveTo(s2, 5*time, 80*this->s->getScaleX());
            this->setAttackType(7);
            break;
        }
        case 11:
        {
            if (isJiXuSkill2)
            {
				isJiXuSkill2 = true;
            }
            else
            {
                skill2AnimationId = 17;
            }
            PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqing.mp3"/*.wav*/);
            setAction(10, 1);
            this->s->getAnimation()->setSpeedScale(0.5);
            float time = 2*animation->m_pMovementData->duration * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(1.5*time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            CCArmature* s2  =addMotion(seq,2*time);
            this->runAction(seq);
            moveTo(this, time, 80*this->s->getScaleX());
            moveTo(s2, 5*time, 80*this->s->getScaleX());
            jumpRise(100,0.5*time,ccp(0,0),1);
            this->setAttackType(9);
            break;
        }
        case 12:
        {
            this->attackPP = 2*this->attackP;
            isCanDirect = false;
            shandianqiou();
            zadi();
            stopActionByTag(999);
            setAction(0,1);
            setAction(18, 3);
            this->s->getAnimation()->setSpeedScale(1);
            float time = 25* 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(9);
            break;
        }
        case 13:
        {
            zadi();
            stopActionByTag(999);
            setAction(18, 1);
            this->s->getAnimation()->pause();
            float time = 2* 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(9);
            break;
        }
        case 14:
        {
            stopActionByTag(999);
            setAction(18, 1);
            this->s->getAnimation()->pause();
            float time = 10 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(9);
            CCSize size = this->s->getContentSize();
            skill1end("tx_juqi",CCPoint(0.1*this->s->getScaleX()*size.width,size.height*0.9));
            break;
        }
        case 15:
        {
            stopActionByTag(999);
            setAction(18, 1);
           
            float time = 5 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(9);
            CCSize size = this->s->getContentSize();
            skill1end("tx_juqibao",CCPoint(0.1*this->s->getScaleX()*size.width,size.height*0.9));
            break;
        }
        case 16:
        {
           
            this->s->getAnimation()->resume();
            float time = 15 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(9);
            break;
        }
        case 17:
        {
            
            zadi2();
            this->s->getAnimation()->pause();
            float time = 20 * 0.032f;
            CCDelayTime* delay = CCDelayTime::create(time);
            CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill2Action));
            CCSequence* seq = CCSequence::create(delay,call,NULL);
            this->runAction(seq);
            this->setAttackType(9);
            break;
        }
        case 18:
        {
            this->attackPP = this->attackP;
            isCanDirect = true;
            if(this->getChildByTag(shandianqiuEffectTag) != NULL)
            {
                this->removeChildByTag(shandianqiuEffectTag);
            }
            this->s->getAnimation()->resume();
            isSkill1 = false;
            this->setAttackType(1);
            this->wudi = false;
            setAction(0);
            m_state = s_stand;
            isSkill2 = false;
            break;
        }
    }
}

void Hero::zadi()
{
    
    this->scheduleOnce(schedule_selector(Hero::zadiShengyin), 0.2f);
    this->setZOrder(1000000);
    Effect* effect = Effect::create("zadi", 0.2, 1);
    this->addChild(effect,1,zadiEffectTag);
    effect->setRotation(90);
    CCSize size = this->s->getContentSize();
    effect->setPositionY(size.height/3);
}

void Hero::zadiShengyin(float dt)
{
     PersonalAudioEngine::sharedEngine()->playEffect("music/zadi.mp3");
     gameLayer->screenShake(6, 26);
}

void Hero::zadi2()
{
    this->scheduleOnce(schedule_selector(Hero::zadiShengyin), 0.2f);
  //  PersonalAudioEngine::sharedEngine()->playEffect("music/zadi.mp3");
    Ef* ef = Ef::create("tx_baozha");
    this->addChild(ef,10000,zadiEffectTag);
    CCSize size = this->s->getContentSize();
    ef->setPositionY(this->bottomH);
}

void Hero::die()
{
    HUB->TouchEnded();
    this->stopAllActions();
    this->s->stopAllActions();
    this->isDie = true;
    this->orientation = HOLDER;
    if(this->s->getScaleX()==-1)
    {
        BeatEffect::create(this, 3, -1);
    }else
    {
        BeatEffect::create(this, 3, 1);
    }
    this->setAction(4);
    int time = 2;
    if(gameLayer->mapThreeJuqing)
    {
         time = 3.5;
    }
    CCDelayTime* delay = CCDelayTime::create(time);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::shop));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    this->runAction(seq);
}

void Hero::shop(CCObject* pSender)
{
    this->stopAllActions();
    this->s->stopAllActions();
    this->setAction(4);
    this->s->setPosition(0, 0);
    if (KingData->getFuhuo() && !gameLayer->mapThreeJuqing)
    {
        this->fuhuo();
        if (!gameLayer->mapThreeJuqing)
        {
            Game::instance()->getShopLayer()->showInfo(18);
        }
        return;
    }
    
    /*if (gameLayer->mapThreeJuqing)
    {
        gameLayer->jihuo();
    }else*/
    {
        gameLayer->shop(5);
    }
}

void Hero::yanmu()
{
    if(this->getChildByTag(yanmuEffectTag) == NULL)
    {
        Ef* ef = Ef::create("tx_chongyanwu");
        this->addChild(ef, 1000, yanmuEffectTag);
        CCSize size = this->s->getContentSize();
        ef->setScaleX(this->s->getScaleX());
        ef->setPositionY(this->bottomH);
        ef->setPositionX(-1*this->s->getScaleX()*size.width/3);
    }
}

void Hero::shandianqiou()
{
    if(this->getChildByTag(shandianqiuEffectTag) == NULL)
    {
        Ef* ef = Ef::create("tx_shandianqiu");
        this->addChild(ef, 1000, shandianqiuEffectTag);
        CCSize size = this->s->getContentSize();
        ef->setScaleX(this->s->getScaleX());
        ef->setPositionY(this->bottomH);
        ef->isRemove = false;
    }
}

void Hero::skill3Action(CCObject* pSender)
{
    orientation = HOLDER;
    this->setZOrder(60000);

    skill3AnimationId = skill3AnimationId+1;
    if(skill3AnimationId==1)
    {
        PersonalAudioEngine::sharedEngine()->playEffect("music/dazhao.mp3");
        isCanDirect = false;
        m_state = s_skill;
        isSkill3 = true;
        this->wudi = true;
        float time = 10 * 0.032f;
        setAction(21, 1);
        CCSize size = this->s->getContentSize();
        skill1end("tx_juqi",CCPoint(-0.1*this->s->getScaleX()*size.width,size.height*0.8));
        CCDelayTime* delay = CCDelayTime::create(time);
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill3Action));
        CCSequence* seq = CCSequence::create(delay,call,NULL);
        this->runAction(seq);
        this->setAttackType(10);
        skill3Scale = this->s->getScaleX();
    } else if (skill3AnimationId ==2)
    {
        PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie1.mp3");
        float time = 10 * 0.032f;
        setAction(21, 1);
        CCSize size = this->s->getContentSize();
        skill1end("tx_juqibao",CCPoint(0.3*this->s->getScaleX()*size.width,size.height*0.7));
        CCDelayTime* delay = CCDelayTime::create(time);
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill3Action));
        CCSequence* seq = CCSequence::create(delay,call,NULL);
        this->runAction(seq);

    }else if (skill3AnimationId ==3) {
        PersonalAudioEngine::sharedEngine()->playEffect("music/dajiqie2.mp3"/*.wav*/);
        float time = 3 * 0.032f;
        CCDelayTime* delay = CCDelayTime::create(time);
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill3Action));
        CCSequence* seq = CCSequence::create(delay,call,NULL);
        gameLayer->runAction(seq);
        this->setAttackType(10);
        CCSize size = this->s->getContentSize();
        shandian(skill3AnimationId);
    }
    else if (skill3AnimationId>=4 && skill3AnimationId<=10)
    {
        if(skill3AnimationId%2==1)
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/shandian.mp3");
        }else
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/shandian.mp3");
        }
        isCanDirect = true;
        if(skill3AnimationId>4)
        {
            this->wudi = false;
        }
        isSkill3 = false;
        float time = 3 * 0.032f;
        CCDelayTime* delay = CCDelayTime::create(time);
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::skill3Action));
        CCSequence* seq = CCSequence::create(delay,call,NULL);
        gameLayer->runAction(seq);
        this->setAttackType(10);
        CCSize size = this->s->getContentSize();
        shandian(skill3AnimationId);
        m_state = s_stand;
    }else
    {
        skill3AnimationId = 0;
    }
    if(skill3AnimationId == 4)
    {
        setAction(0);
    }
}

void Hero::shandian(int skill3AnimationId)
{
    if (delegate)
    {
       this->delegate->actionDidAttack(this);
    }
    
    float randx = CCRANDOM_0_1();
    Ef* ef;
    if (randx<0.33) {
         ef = Ef::create("tx_shandian");
    }else if (randx>0.33 && randx<0.66)
    {
         ef = Ef::create("tx_shandian2");
    }else
    {
         ef = Ef::create("tx_shandian2",1);
    }
    this->addChild(ef, 1000, shandianEffectTag);
    CCSize size = this->s->getContentSize();
    float randX = 1.5+CCRANDOM_MINUS1_1();
 
    ef->setScaleX(skill3Scale*randX);
    ef->setPositionY(this->bottomH);
    ef->setSpeed(2);
    ef->setPositionX(1*skill3Scale*size.width/5*skill3AnimationId);
    CCRect rect ;
    rect.origin =ccpSub(ccpAdd(this->getPosition(),ef->getPosition()),ccp(ef->getSize().width/2,ef->getSize().height/2));
    rect.size = ef->getSize();
    this->effectRect = rect;
}

Ef* Hero::skill1end(const char* name,CCPoint p)
{
    Ef* effect = Ef::create(name);
    this->addChild(effect,10000,juqiEffectTag);
    CCSize size = this->s->getContentSize();
    effect->setPosition(p);
    effect->setScaleX(this->s->getScaleX());
    CCRect rect ;
    rect.origin =ccpSub(ccpAdd(this->getPosition(),effect->getPosition()),ccp(effect->getSize().width/2,effect->getSize().height/2));
    rect.size = effect->getSize();
    this->effectRect = rect;
    if (delegate && (skillAnimationId == 202) )
    {
        this->delegate->actionDidAttack(this);
    }
    return effect;
}

void Hero::fuhuo()
{
    if (!gameLayer->mapThreeJuqing)
    {
         KingData->setFuhuo(false);
    }
    this->stopAllActions();
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(Hero::daodiqishen));
    this->runAction(call);
}
