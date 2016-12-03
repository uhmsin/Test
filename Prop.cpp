//
//  Prop.cpp
//  King
//
//  Created by mac on 14-3-27.
//
//

#include "Prop.h"
Prop::Prop()
{
    is_hold = false;
}
Prop* Prop::create(int type,int num)
{
    Prop* prop = new Prop();
    prop->init(type,num);
    prop->autorelease();
    return prop;
}
bool Prop::init(int type,int num)
{
    if(type==1)
    {
		innerSprite = CCSprite::createWithSpriteFrameName("qtsz_x.png");
    }else if(type == 2)
    {
		innerSprite = CCSprite::createWithSpriteFrameName("qtsz_nq.png");
    }else
    {
		innerSprite = CCSprite::createWithSpriteFrameName("qtsz_jb.png");
    }
    CCSequence* SEQ = CCSequence::create(CCMoveBy::create(0.5, ccp(0,10)),CCMoveBy::create(0.5, ccp(0,-10)),NULL);
    innerSprite->runAction(CCRepeatForever::create(SEQ));
    this->setType(type);
    this->setNum(num);
    this->addChild(innerSprite);
    this->setZOrder(989898998);
    return true;
}

CCRect Prop::getBondingBox()
{
    CCSize innerSize = innerSprite->getContentSize();
    CCRect rect;
    rect.origin = ccpSub(this->getPosition() ,ccp(innerSize.width/2,innerSize.height/2));
    rect.size = innerSize;
    return rect;
}

