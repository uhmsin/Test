//
//  Effect.cpp
//  King
//
//  Created by mac on 14-4-11.
//
//

#include "Effect.h"
#include "Define.h"
#include "Hero.h"
Effect* Effect::create(const char* name,float delay,unsigned int isLoop)
{
    Effect* effect = new Effect();
    effect->init(name,delay,isLoop);
    effect->autorelease();
    return effect;
}

bool Effect::init(const char* name,float delay,unsigned int isLoop)
{
    const char* spriteFileName = CCString::createWithFormat("%s%d.png",name,0)->getCString();
    m_sprite = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFileName));
    this->addChild(m_sprite,Role->getZOrder()+1000);
    CCAnimation* animation = createAnimation(name, delay, isLoop);
    CCAnimate* animate = CCAnimate::create(animation);
    CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Effect::remove));
    CCSequence* seq = CCSequence::create(animate,callfunc,NULL);
    m_sprite->runAction(seq);
    return true;
}

void Effect::remove()
{
    this->removeFromParentAndCleanup(true);
}

CCAnimation* Effect::createAnimation(const char* name,float delay, unsigned int isLoop)
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray* framesArray = CCArray::create();
    CCSpriteFrame* frame = NULL;
    int index = 0;
    do
    {
        frame = cache->spriteFrameByName(CCString::createWithFormat("%s%d.png",name,index++)->getCString());
        if (frame == NULL)
        {
            break;
        }
        framesArray->addObject(frame);
    } while (true);
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesArray);
    animation->setDelayPerUnit(delay);
    animation->setLoops(isLoop);
    animation->setRestoreOriginalFrame(true);
    return animation;
}
