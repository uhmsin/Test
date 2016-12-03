//
//  Bullet.cpp
//  king04
//
//  Created by mac on 14-5-7.
//
//

#include "Bullet.h"
#include "Define.h"
#include "Hero.h"
#include "Define.h"
Bullet* Bullet::create( ARPG* owner)
{
    Bullet* bullet = new Bullet();
    bullet->init(owner);
    bullet->autorelease();
    return bullet;
}

bool Bullet::init( ARPG* owner)
{
    this->owner = owner;
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"wuqifeidao","wuqifeidao");
    CCArmatureDataManager::sharedArmatureDataManager()->purge();
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    s = CCArmature::create("wuqifeidao");
    this->addChild(s);
    s->getAnimation()->playWithIndex(0);
    gameLayer->bullets->addObject(this);
    this->scheduleUpdate();
    return true;
}

void Bullet::removeBullet()
{
    gameLayer->bullets->removeObject(this);
    this->removeFromParentAndCleanup(true);
}

void Bullet::update(float dt)
{

    if (this->getBondingBox().intersectsRect(Role->getBondingBox()))
    {
        if (!Role->wudi && !Role->isDie)
        {
            Role->suffer(this->owner, 11);
        }
        this->remove();
    }
   
}

CCRect Bullet::getBondingBox()
{
    CCRect rect;
    rect.origin = ccpSub(this->getPosition(), ccp(this->s->getContentSize().width/2,this->s->getContentSize().height/2));
    rect.size = this->s->getContentSize();
    return rect;
}

void Bullet::remove()
{
     gameLayer->bullets->removeObject(this);
     this->removeFromParentAndCleanup(true);
}




