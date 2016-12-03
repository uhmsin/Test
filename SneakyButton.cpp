#include "SneakyButton.h"
#include "GameScene.h"
#include "Hero.h"
#include "Define.h"
#include "HubShop.h"
using namespace cocos2d;

void SneakyButton::onEnterTransitionDidFinish()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -130, true);
}

void SneakyButton::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool SneakyButton::initWithRect(CCRect rect)
{
	bool pRet = false;
        isTouched = false;
        m_delegate = NULL;
		bounds = CCRectMake(0, 0, rect.size.width, rect.size.height);
		center = CCPointMake(rect.size.width/2, rect.size.height/2);
		status = 1; //defaults to enabled
		active = false;
		value = 0;
		isHoldable = 0;
		isToggleable = 0;
		radius = 32.0f;
		rateLimit = 1.0f/120.0f;
		
		setPosition(rect.origin); //not sure about this
        scheduleUpdate();
		pRet = true;
	return pRet;
}

void SneakyButton::limiter(float delta)
{
	value = 0;
	this->unschedule(schedule_selector(SneakyButton::limiter));
	active = false;
}

void SneakyButton::setRadius(float r)
{
	radius = r;
	radiusSq = r*r;
}

bool SneakyButton::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
   
    if(HUB->type == 0)
    {
  
        if (!HUB->canTouch)
        {
            return false;
        }
        if (Role->isDie)
        {
            return false;
        }
        if (!HUB->isTeach)
        {
            if (Role->isDie || (gameLayer->isGameStart ==false)  )
            {
                return false;
            }
        }else
        {
            if (HUB->teachID != 2 && HUB->teachID < 5)
            {
                return false;
            }
        }
    }else
    {
      
    }

    
	CCPoint location = touch->getLocation();
	location = this->convertToNodeSpace(location);
		//Do a fast rect check before doing a circle hit check:
	if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius)
    {
		return false;
	}else
    {
		float dSq = location.x*location.x + location.y*location.y;
		if(radiusSq > dSq){
			active = true;
			if (!isHoldable && !isToggleable){
				value = 1;
				this->schedule(schedule_selector(SneakyButton::limiter), rateLimit);
			}
			if (isHoldable)
                value = 1;
			if (isToggleable)
                value = !value;
            
            isTouched = true;
            
            if (m_delegate)
            {
                if (HUB->type == 0)
                {
                    if (HUB->isTeach)
                    {
                        if (HUB->teachID == 2)
                        {
                            HUB->teachID = 3;
                        }
                        if (HUB->teachID == 6)
                        {
                            HUB->teachID = 7;
                        }
                    }
                    GameScene* layer = (GameScene*)m_delegate;
                    layer->commanAttack();
                }
            }
            
         
			return true;
		}
	}
    return false;
}

void SneakyButton::update(float dt)
{
    if (Role!=NULL &&  Role->isDie)
    {
        return;
    }
    if (m_delegate && this->isTouched)
    {
        if (HUB->type == 0)
        {
           GameScene* layer = (GameScene*)m_delegate;
           layer->commanAttack();
        }
    }
}

void SneakyButton::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    if (Role!=NULL &&  Role->isDie)
    {
        return;
    }
	if (!active) return;
	CCPoint location =  touch->getLocation();
	location = this->convertToNodeSpace(location);
		//Do a fast rect check before doing a circle hit check:
	if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius){
        isTouched = false;
		return;
	}else{
		float dSq = location.x*location.x + location.y*location.y;
		if(radiusSq > dSq){
			if (isHoldable) value = 1;
		}
		else {
			if (isHoldable) value = 0; active = false;
		}
        isTouched = true;
	}
}

void SneakyButton::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	ccTouchEnded();
}

void SneakyButton::ccTouchEnded()
{
	this->isTouched = false;
	if (Role != NULL &&  Role->isDie)
	{
		return;
	}
	if (!active) return;
	if (isHoldable) value = 0;
	if (isHoldable || isToggleable) active = false;
	isTouched = false;
}

void SneakyButton::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
	this->ccTouchEnded(touch, event);
}

void SneakyButton::touchDelegateRelease()
{
	this->release();
}

void SneakyButton::touchDelegateRetain()
{
	this->retain();
}
